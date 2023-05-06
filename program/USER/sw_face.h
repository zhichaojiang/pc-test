#ifndef __SW_FACE_H
#define	__SW_FACE_H
#include "stm32f10x.h"



extern uint8_t current_sw;
//波段位置
#define NONE     0x00
#define SW1      0x01
#define SW2      0x02
#define SW3      0x04
#define SW4      0x08
#define SW5      0x10


/********************************************************************************
//波段开关端口初始化 
//SW1:PB7
//SW2:PB6
//SW3:PB3
//SW4:PB2
//SW5:PB4

*********************************************************************************/
void SW_GPIO_Config(void);
	
void read_SW(void);
#endif /* __SW_FACE_H*/
