#include "read_key.h"
		
uint8_t KeyPressDown=0;//������
uint8_t KeyRelease=0;//���ͷ�
uint8_t LastKey=0;//��״̬,����״̬�����ͷ�״̬
uint8_t KeyShortPress=0;//�̰�,���𴥷�һ��
uint8_t KeyLongPress=0;
uint8_t KeyLongPressHold=0;//�������֣���������
uint16_t KeyDownTime[KEY_TOTAL];


/********************************************************************************
//KEY�˿ڳ�ʼ��
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
//KEYɨ��
//20ms����һ��
*********************************************************************************/
void KeyScan(void)
{
	static unsigned char LasetReadKey=0;//��¼�ϴ�KeyScan()��ȡ�ļ�ֵ
	uint8_t CurrReadKey;//��¼����KeyScan()��ȡ�ļ�ֵ
	uint8_t CurrKey;//��¼����������������Ч����ֵ
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
		//�̰����������ж�
		if((KeyRelease&(1<<i))&&(KeyDownTime[i]<LONGPRESSTIEMS)){
			KeyShortPress|=(1<<i);

		}else{
			KeyShortPress&=~(1<<i);
		}	
    
		//����,ʱ�䵽�ж�
		if(KeyDownTime[i]==LONGPRESSTIEMS){
			KeyLongPress|=(1<<i);
		}else{
			KeyLongPress&=~(1<<i);
		}	
		
		//��������,ʱ�䵽�ж�
		if(KeyDownTime[i]>LONGPRESSTIEMS){
			KeyLongPressHold|=(1<<i);
		}else{
			KeyLongPressHold&=~(1<<i);
		}	
		//������ʱ���ۼӼ�����
		if(LastKey&(1<<i)){
			KeyDownTime[i]++;			
		}else{
			KeyDownTime[i]=0;
		}
		
	}	
}
