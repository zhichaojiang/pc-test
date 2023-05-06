#ifndef __HIGH_CONTROL_H
#define	__HIGH_CONTROL_H
#include "stm32f10x.h"


#define HighV_OUT1_ON       GPIOA->ODR |= GPIO_Pin_5
#define HighV_OUT1_OFF      GPIOA->ODR &=~ GPIO_Pin_5

#define PWN_LOCK1_ON         GPIOC->ODR |= GPIO_Pin_14  	 
#define PWN_LOCK1_OFF        GPIOC->ODR &=~ GPIO_Pin_14  
#define PWN_LOCK2_ON         GPIOC->ODR |= GPIO_Pin_15  	 
#define PWN_LOCK2_OFF        GPIOC->ODR &=~ GPIO_Pin_15 

#define PWM_CHECK_IN	GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8)

/********************************************************************************
//PWN LOCK端口初始化 
//LOCK1:PC14
//LOCK2:PC15
*********************************************************************************/
void PWM_LOCK_GPIO_Config(void);

/********************************************************************************
//PWN CHECK端口初始化 
//CHECK1:PB8
//CHECK2:PD0
*********************************************************************************/
void PWM_CHECK_GPIO_Config(void);

/********************************************************************************
//HIGHV_OUT端口初始化 
//OUT1:PA5
//OUT2:PA6
*********************************************************************************/
void HIGHV_OUT_GPIO_Config(void);
	

#endif /* __HIGH_CONTROL_H*/


