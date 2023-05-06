#ifndef __JLX12864G_H
#define	__JLX12864G_H
#include "stm32f10x.h"


//LCD引脚
#define LCD_RST_0     GPIO_ResetBits(GPIOB,GPIO_Pin_11)
#define LCD_RST_1     GPIO_SetBits(GPIOB,GPIO_Pin_11)

#define LCD_CS_0      GPIO_ResetBits(GPIOB,GPIO_Pin_10)
#define LCD_CS_1      GPIO_SetBits(GPIOB,GPIO_Pin_10)

#define LCD_RS_0      GPIO_ResetBits(GPIOB,GPIO_Pin_13)
#define LCD_RS_1      GPIO_SetBits(GPIOB,GPIO_Pin_13) 

#define LCD_SDA_0      GPIO_ResetBits(GPIOB,GPIO_Pin_14)
#define LCD_SDA_1      GPIO_SetBits(GPIOB,GPIO_Pin_14) 

#define LCD_SCLK_0      GPIO_ResetBits(GPIOA,GPIO_Pin_8)
#define LCD_SCLK_1      GPIO_SetBits(GPIOA,GPIO_Pin_8) 

#define LCD_LED_OFF      GPIO_ResetBits(GPIOA,GPIO_Pin_9)
#define LCD_LED_ON      GPIO_SetBits(GPIOA,GPIO_Pin_9) 
#define LCD_LED_XOR    GPIOA->ODR ^= GPIO_Pin_9

/********************************************************************************
//LCD端口初始化
// LCD_CS:PB10
// LCD_RST:PB11
// LCD_RS:PB13
// LCD_SDA:PB14
// LCD_SCLK:PA8
// LCD_LED:PA9  背光灯
*********************************************************************************/
void LCD_GPIO_Config(void);
void sub_main(void);
unsigned char  dis_ico(unsigned char data);
void dis_intput_voltage(float voltage);
void dis_light_num(uint8_t light_data);
void dis_bar(uint8_t bar_data);
void dis_alarm_point(uint8_t alarm_data);
#endif /* __JLX12864G_H */
