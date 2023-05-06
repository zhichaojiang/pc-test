#include "SysTick.h"
#include "read_key.h"
#include "iwdg.h"
#include "led.h"


extern uint8_t  flag_en_500us;
extern uint8_t  flag_en_1ms;            //1ms 标志数
extern uint8_t  flag_en_10ms;            //10ms 标志数
extern uint8_t  flag_en_20ms;            //20ms 标志数
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
 * 函数名：SysTick_Init
 * 描述  ：启动系统滴答定时器 SysTick
 * 输入  ：无
 * 输出  ：无
 * 调用  ：外部调用 
 */
void SysTick_Init(void)
{
	/* SystemFrequency / 1000    1ms中断一次
	 * SystemFrequency / 100000	 10us中断一次
	 * SystemFrequency / 1000000 1us中断一次
	 */
	if(SysTick_Config(SystemCoreClock / 1000))	// ST3.5.0库版本
	{ 
		/* Capture error */ 
		while (1);
	}
		// 开启滴答定时器  
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
		  KeyScan();  //扫描按键	

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

