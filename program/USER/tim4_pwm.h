#ifndef __TIM4_PWM_H
#define	TIM4_PWM

#include "stm32f10x.h"
#define PWM_OUT_OFF         GPIOB->ODR &=~ GPIO_Pin_9
#define PWM_OUT_ON          GPIOB->ODR |= GPIO_Pin_9

void TIM4_PWM_Init(void);



#endif /* TIM4_PWM */
