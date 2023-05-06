#include "led.h"






/********************************************************************************
//LED端口初始化
// LED1:PB1
// LED2:PB12
// LED3:PB15
// LED4:PA10
// LED5:PA11
// LED6:PA12
// LED7:PA15
*********************************************************************************/
void LED_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1 | GPIO_Pin_12 | GPIO_Pin_15;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	GPIO_SetBits(GPIOB, GPIO_Pin_1 | GPIO_Pin_12 | GPIO_Pin_15 );	

	  //PA15 重新映射,做变通IO使用
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE); 
	
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);	    
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_15;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	GPIO_SetBits(GPIOA, GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_15 );	  
}


//2023    dddd   2024









					
	




