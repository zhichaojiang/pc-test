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
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		    // �����������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
}





/*
 * ��������TIM4_Mode_Config
 * ����  ������TIM4�����PWM�źŵ�ģʽ�������ڡ����ԡ�ռ�ձ�
 * ����  ����
 * ���  ����
 * ����  ���ڲ�����
 */
static void TIM4_Mode_Config(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	/* PWM�źŵ�ƽ����ֵ */
	u16 CCR_Val =0;//0;//2499




  /* Time base configuration */		
TIM_TimeBaseStructure.TIM_Period = 150;       //����ʱ����0������999����Ϊ1000�Σ�Ϊһ����ʱ����
 // TIM_TimeBaseStructure.TIM_Period = 1490;       //����ʱ����0������999����Ϊ1000�Σ�Ϊһ����ʱ����
	//TIM_TimeBaseStructure.TIM_Period = 4000;       //����ʱ����0������999����Ϊ1000�Σ�Ϊһ����ʱ����
  TIM_TimeBaseStructure.TIM_Prescaler =0;// 359;	    //����Ԥ��Ƶ����Ԥ��Ƶ����Ϊ72MHz
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;	//����ʱ�ӷ�Ƶϵ��������Ƶ
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //���ϼ���ģʽ

  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	
	
	/* PWM1 Mode configuration: Channel 4 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    //����ΪPWMģʽ1
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
  TIM_OCInitStructure.TIM_Pulse = CCR_Val;	   //��������ֵ�������������������ֵʱ����ƽ��������
  TIM_OCInitStructure.TIM_OCPolarity =TIM_OCPolarity_High;// TIM_OCPolarity_Low;  //����ʱ������ֵС��CCR_ValʱΪ�ߵ�ƽ
  TIM_OC4Init(TIM4, &TIM_OCInitStructure);	 //ʹ��ͨ��4
  TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);

	

  TIM_ARRPreloadConfig(TIM4, ENABLE);			 // ʹ��TIM4���ؼĴ���ARR
  /* TIM4 enable counter */
  TIM_Cmd(TIM4, ENABLE);                   //ʹ�ܶ�ʱ��3	
}

void TIM4_PWM_Init(void)
{
	TIM4_GPIO_Config();
	TIM4_Mode_Config();	
	
}
