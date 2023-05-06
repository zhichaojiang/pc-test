#include "read_key.h"
		
uint8_t KeyPressDown=0;//键按下
uint8_t KeyRelease=0;//键释放
uint8_t LastKey=0;//键状态,按下状态或者释放状态
uint8_t KeyShortPress=0;//短按,弹起触发一次
uint8_t KeyLongPress=0;
uint8_t KeyLongPressHold=0;//长按保持，持续触发
uint16_t KeyDownTime[KEY_TOTAL];


/********************************************************************************
//KEY端口初始化
//KEY1:PB0
//KEY2:PA7
*********************************************************************************/
void KEY_INPUT_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
    GPIO_SetBits(GPIOB,  GPIO_Pin_0);	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_7;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
    GPIO_SetBits(GPIOA,  GPIO_Pin_7);	

}






/********************************************************************************
//KEY扫描
//20ms调用一次
*********************************************************************************/
void KeyScan(void)
{
	static unsigned char LasetReadKey=0;//记录上次KeyScan()读取的键值
	uint8_t CurrReadKey;//记录本次KeyScan()读取的键值
	uint8_t CurrKey;//记录本次消抖处理后的有效按键值
	uint8_t i;
	
	CurrReadKey=(CurrReadKey<<1)|(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7)&0X01);
	CurrReadKey=(CurrReadKey<<1)|(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)&0X01);
	CurrReadKey=~CurrReadKey;

	CurrKey=(CurrReadKey&LasetReadKey)|(LastKey&(CurrReadKey^LasetReadKey));
	KeyPressDown=(~LastKey)&CurrKey;
	KeyRelease=LastKey&(~CurrKey);
	LasetReadKey=CurrReadKey; 
	LastKey=CurrKey;
	
	for(i=0;i<KEY_TOTAL;i++){		
		//短按，弹起来判断
		if((KeyRelease&(1<<i))&&(KeyDownTime[i]<LONGPRESSTIEMS)){
			KeyShortPress|=(1<<i);

		}else{
			KeyShortPress&=~(1<<i);
		}	
    
		//长按,时间到判断
		if(KeyDownTime[i]==LONGPRESSTIEMS){
			KeyLongPress|=(1<<i);
		}else{
			KeyLongPress&=~(1<<i);
		}	
		
		//长按保持,时间到判断
		if(KeyDownTime[i]>LONGPRESSTIEMS){
			KeyLongPressHold|=(1<<i);
		}else{
			KeyLongPressHold&=~(1<<i);
		}	
		//键按下时，累加计数器
		if(LastKey&(1<<i)){
			KeyDownTime[i]++;			
		}else{
			KeyDownTime[i]=0;
		}
		
	}	
}
