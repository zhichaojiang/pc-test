#include "high_control.h"


/********************************************************************************
//PWN LOCK端口初始化 
//LOCK1:PC14
//LOCK2:PC15
*********************************************************************************/
void PWM_LOCK_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_14 | GPIO_Pin_15 ;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	GPIO_ResetBits(GPIOC,  GPIO_Pin_14 | GPIO_Pin_15 );	  
}


/********************************************************************************
//PWN CHECK端口初始化 
//CHECK1:PB8
//CHECK2:PD0
*********************************************************************************/
void PWM_CHECK_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8 ;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	GPIO_SetBits(GPIOB,  GPIO_Pin_8 );	  
	
	

//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
//	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0 ;
//	GPIO_Init(GPIOD,&GPIO_InitStructure);
//	GPIO_SetBits(GPIOD,  GPIO_Pin_0 );	
	
}

/********************************************************************************
//HIGHV_OUT端口初始化 
//OUT1:PA5
*********************************************************************************/
void HIGHV_OUT_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5  ;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	GPIO_ResetBits(GPIOA,  GPIO_Pin_5  );	  
}


