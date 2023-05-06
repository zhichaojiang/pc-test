#ifndef __READ_KEY_H
#define	__READ_KEY_H

#include "stm32f10x.h"
//#define  LONGPRESSTIEMS     150
#define  LONGPRESSTIEMS     100


//������
#define KEY1      0x01
#define KEY2      0x02


#define KEY_TOTAL   2
extern uint8_t KeyPressDown;//������
extern uint8_t KeyRelease;//���ͷ�
extern uint8_t LastKey;//��״̬,����״̬�����ͷ�״̬
extern uint8_t KeyShortPress;//�̰�,���𴥷�һ��
extern uint8_t KeyLongPress;//������ֻ����һ��
extern uint8_t KeyLongPressHold;//�������֣���������
extern uint16_t KeyDownTime[KEY_TOTAL];//�����¼�����

void KEY_INPUT_GPIO_Config(void);
void KeyScan(void);



#endif /* __READ_KEY_H */

