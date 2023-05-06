#ifndef __LED_H
#define	__LED_H
#include "stm32f10x.h"


#define LED1_OFF           GPIOB->ODR |= GPIO_Pin_1
#define LED1_ON          GPIOB->ODR &=~ GPIO_Pin_1
#define LED1_XOR          GPIOB->ODR ^= GPIO_Pin_1

#define LED2_OFF           GPIOB->ODR |= GPIO_Pin_12
#define LED2_ON          GPIOB->ODR &=~ GPIO_Pin_12
#define LED2_XOR          GPIOB->ODR ^= GPIO_Pin_12

#define LED3_OFF           GPIOB->ODR |= GPIO_Pin_15
#define LED3_ON          GPIOB->ODR &=~ GPIO_Pin_15
#define LED3_XOR          GPIOB->ODR ^= GPIO_Pin_15

#define LED4_OFF           GPIOA->ODR |= GPIO_Pin_10
#define LED4_ON          GPIOA->ODR &=~ GPIO_Pin_10
#define LED4_XOR          GPIOA->ODR ^= GPIO_Pin_10

#define LED5_OFF           GPIOA->ODR |= GPIO_Pin_11
#define LED5_ON          GPIOA->ODR &=~ GPIO_Pin_11
#define LED5_XOR          GPIOA->ODR ^= GPIO_Pin_11

#define LED6_OFF           GPIOA->ODR |= GPIO_Pin_12
#define LED6_ON          GPIOA->ODR &=~ GPIO_Pin_12
#define LED6_XOR          GPIOA->ODR ^= GPIO_Pin_12

#define LED7_OFF           GPIOA->ODR |= GPIO_Pin_15
#define LED7_ON          GPIOA->ODR &=~ GPIO_Pin_15
#define LED7_XOR          GPIOA->ODR ^= GPIO_Pin_15



/********************************************************************************
//LED¶Ë¿Ú³õÊ¼»¯
// LED1:PB1
// LED2:PB12
// LED3:PB15
// LED4:PA10
// LED5:PA11
// LED6:PA12
// LED7:PA15
*********************************************************************************/
void LED_GPIO_Config(void);


#endif /* __LED_H */
