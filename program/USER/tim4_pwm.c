#include "tim4_pwm.h"



static void TIM4_GPIO_Config(void) 
{
  GPIO_InitTypeDef GPIO_InitStructure;

	/* TIM4 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); 
  /*  GPIOB clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); 


  /*GPIOB Configuration: TIM4 channel 4 as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_9 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		    // 复用推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
}





/*
 * 函数名：TIM4_Mode_Config
 * 描述  ：配置TIM4输出的PWM信号的模式，如周期、极性、占空比
 * 输入  ：无
 * 输出  ：无
 * 调用  ：内部调用
 */
static void TIM4_Mode_Config(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	/* PWM信号电平跳变值 */
	u16 CCR_Val =0;//0;//2499




  /* Time base configuration */		
TIM_TimeBaseStructure.TIM_Period = 150;       //当定时器从0计数到999，即为1000次，为一个定时周期
 // TIM_TimeBaseStructure.TIM_Period = 1490;       //当定时器从0计数到999，即为1000次，为一个定时周期
	//TIM_TimeBaseStructure.TIM_Period = 4000;       //当定时器从0计数到999，即为1000次，为一个定时周期
  TIM_TimeBaseStructure.TIM_Prescaler =0;// 359;	    //设置预分频：不预分频，即为72MHz
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;	//设置时钟分频系数：不分频
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //向上计数模式

  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	
	
	/* PWM1 Mode configuration: Channel 4 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    //配置为PWM模式1
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
  TIM_OCInitStructure.TIM_Pulse = CCR_Val;	   //设置跳变值，当计数器计数到这个值时，电平发生跳变
  TIM_OCInitStructure.TIM_OCPolarity =TIM_OCPolarity_High;// TIM_OCPolarity_Low;  //当定时器计数值小于CCR_Val时为高电平
  TIM_OC4Init(TIM4, &TIM_OCInitStructure);	 //使能通道4
  TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);

	

  TIM_ARRPreloadConfig(TIM4, ENABLE);			 // 使能TIM4重载寄存器ARR
  /* TIM4 enable counter */
  TIM_Cmd(TIM4, ENABLE);                   //使能定时器3	
}

void TIM4_PWM_Init(void)
{
	TIM4_GPIO_Config();
	TIM4_Mode_Config();	
	
}
