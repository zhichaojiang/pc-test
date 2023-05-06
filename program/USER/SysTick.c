#include "SysTick.h"
#include "read_key.h"
#include "iwdg.h"
#include "led.h"


extern uint8_t  flag_en_500us;
extern uint8_t  flag_en_1ms;            //1ms ��־��
extern uint8_t  flag_en_10ms;            //10ms ��־��
extern uint8_t  flag_en_20ms;            //20ms ��־��
extern uint8_t  flag_en_50ms;
extern uint8_t  flag_en_1s;
extern uint8_t  flag_en_1500ms;

uint16_t cnt_1ms=0;
uint16_t cnt_10ms=0;
uint16_t cnt_20ms=0;
uint16_t cnt_50ms=0;
uint16_t cnt_1s=0;
uint16_t cnt_1500ms=0;

/*
 * ��������SysTick_Init
 * ����  ������ϵͳ�δ�ʱ�� SysTick
 * ����  ����
 * ���  ����
 * ����  ���ⲿ���� 
 */
void SysTick_Init(void)
{
	/* SystemFrequency / 1000    1ms�ж�һ��
	 * SystemFrequency / 100000	 10us�ж�һ��
	 * SystemFrequency / 1000000 1us�ж�һ��
	 */
	if(SysTick_Config(SystemCoreClock / 1000))	// ST3.5.0��汾
	{ 
		/* Capture error */ 
		while (1);
	}
		// �����δ�ʱ��  
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
}




void SysTick_Time(void)
{
	

	flag_en_1ms=1;
	if(cnt_10ms<COUNTS_10MS){
			cnt_10ms+=1;
	}
	else
	{
			cnt_10ms=0;
			flag_en_10ms=1;
	}
	
	if(cnt_20ms<COUNTS_20MS){
			cnt_20ms+=1;
	}
	else
	{
			cnt_20ms=0;
			flag_en_20ms=1;
		  KeyScan();  //ɨ�谴��	

	}
	
	if(cnt_50ms<COUNTS_50MS){
			cnt_50ms+=1;
	}
	else
	{
			cnt_50ms=0;
			flag_en_50ms=1;
	}
	
	if(cnt_1s<COUNTS_1S){
			cnt_1s+=1;
	}
	else
	{
			cnt_1s=0;
			flag_en_1s=1;
			
	}
	
	
	if(cnt_1500ms<COUNTS_1500MS){
			cnt_1500ms+=1;
	}
	else
	{
			cnt_1500ms=0;
			flag_en_1500ms=1;
			
	}
		
}

