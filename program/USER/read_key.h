#ifndef __READ_KEY_H
#define	__READ_KEY_H

#include "stm32f10x.h"
//#define  LONGPRESSTIEMS     150
#define  LONGPRESSTIEMS     100


//按键号
#define KEY1      0x01
#define KEY2      0x02


#define KEY_TOTAL   2
extern uint8_t KeyPressDown;//键按下
extern uint8_t KeyRelease;//键释放
extern uint8_t LastKey;//键状态,按下状态或者释放状态
extern uint8_t KeyShortPress;//短按,弹起触发一次
extern uint8_t KeyLongPress;//长按，只触发一次
extern uint8_t KeyLongPressHold;//长按保持，持续触发
extern uint16_t KeyDownTime[KEY_TOTAL];//键按下计数器

void KEY_INPUT_GPIO_Config(void);
void KeyScan(void);



#endif /* __READ_KEY_H */

