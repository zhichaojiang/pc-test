#include "sw_face.h"
uint8_t current_sw;

/********************************************************************************
//波段开关端口初始化 
//SW1:PB7
//SW2:PB6
//SW3:PB3
//SW4:PB2
//SW5:PB4

*********************************************************************************/
void SW_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_7 | GPIO_Pin_6 | GPIO_Pin_3 | GPIO_Pin_2 | GPIO_Pin_4 ;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	GPIO_SetBits(GPIOB,  GPIO_Pin_7 | GPIO_Pin_6 | GPIO_Pin_3 | GPIO_Pin_2 | GPIO_Pin_4 );	  
}

void read_SW(void)
{
	current_sw=0;
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7)==0)current_sw=0x01;
    if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6)==0)current_sw=0x02;
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3)==0)current_sw=0x04;
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_2)==0)current_sw=0x08;
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4)==0)current_sw=0x10;

	
}


				


