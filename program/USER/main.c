/******************** (C) COPYRIGHT 2012 WildFire Team **************************
 * 文件名  ： main.c
 * 描述    ： 开关量采集点       
 * 硬件版本:  P20141121001
 * 库版本  ： ST3.5.0
 *
 * 作者    ： 支朝蒋
**********************************************************************************/


#include "stm32f10x.h"
#include "memory.c"
#include "led.h"
#include "sw_face.h"
#include "SysTick.h"  
#include "eeprom.h"	
#include "iwdg.h"
#include "read_key.h"
#include "key_press.h"
#include "adc.h"
#include "tim4_pwm.h"
#include "high_control.h"
#include "JLX12864G.h"

/******************************************************/
//定义全局变量
uint8_t  flag_en_500us;
uint8_t  flag_en_1ms=0;            //1ms 标志数
uint8_t  flag_en_10ms=0;            //10ms 标志数
uint8_t  flag_en_20ms=0;            //20ms 标志数
uint8_t  flag_en_50ms=0;
uint8_t  flag_en_1s=0;
uint8_t  flag_en_1500ms=0;
uint8_t  flag_contect_state=0;     //




uint8_t flag_surge_add=0;
uint16_t surge_alarm_time=0;


uint16_t up_channel1_status;
void delay_ms(uint16_t delay_ms_data)
{
	uint16_t i,j;
	for(;delay_ms_data!=0;delay_ms_data--)
	{
		for(i=0;i<500;i++)
		  for(j=0;j<10;j++);		
	}
}
uint16_t check_channel(uint16_t current_data,uint16_t set_mode_data)
{
	if(set_mode_data==0){
		if(current_data==0){
			return 0xffff;
		}else{
			return 0;
		}
		
	}else{
		if(current_data==0){
			return 0;
		}else{
			return 0xffff;
		}		
	}	
}

void reset_data(void)
{

  STMFLASH_Write(FLASH_SAVE_ADDR,(u16*)sys_set_memory,20);

  	
}



void check_data_ok(void)
{
 	
 flag_writetoflash=0;	
	if(run_type==0||run_type>4){
		run_type=1;
		flag_writetoflash=0xff;
	}
	
	if(light_day_value>58){
		light_day_value=29;
		
	}

  if(power_const>400||power_const<40){
		power_const=158;
		flag_writetoflash=0xff;
	}
	
	if(output_const>4000||output_const<3000){
		output_const=3500;
		flag_writetoflash=0xff;
	}
	
	if(lcd_on_time>120||output_const<10){
		output_const=60;
		flag_writetoflash=0xff;
	}
	
	if(flag_writetoflash==0xff){
		STMFLASH_Write(FLASH_SAVE_ADDR,(u16*)sys_set_memory,10);		
	}
	
	
}



//错误返回０，正常返回１
unsigned char check_pwm(void)
{
  PWM_OUT_ON;
  PWN_LOCK1_OFF;
  PWN_LOCK1_OFF;
  __NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
  if(PWM_CHECK_IN==0){
    PWM_OUT_OFF;   
		return 1; 
  }else{
    PWM_OUT_OFF;
    return 0;  
  }
}


/*
 * 函数名：main
 * 描述  ：主函数
 * 输入  ：无
 * 输出  ：无
 */
int main(void)
{	

	/*配置及初始化程序调用*/
	//定时器初始化
	//时钟节拍初始化  
	SysTick_Init();//1ms	
  //LED端口初始化
	LED_GPIO_Config();
	SW_GPIO_Config();
	//key
	KEY_INPUT_GPIO_Config();
	ADC1_Init();
  TIM4_PWM_Init();
//  TIM_SetCompare4(TIM4,4999-(black_light_brightness)*500);	//	
  PWM_LOCK_GPIO_Config();
	PWM_CHECK_GPIO_Config();
	HIGHV_OUT_GPIO_Config();
	LCD_GPIO_Config();
  
	STMFLASH_Read(FLASH_SAVE_ADDR,(u16*)sys_set_memory,10);
	check_data_ok();
	
	              //上电源，放电
	               LED7_ON;
                 PWN_LOCK1_ON;
                 PWN_LOCK1_ON;
                 TIM_SetCompare4(TIM4,0);
                 flag_pwn_on=0;								 
							   HighV_OUT1_ON;
						     delay_ms(10);
								 HighV_OUT1_OFF;
						     LED7_OFF;
  
	//output_const=3000;
	sub_main();						//
  
	

dis_ico(run_type);
	

	//	开门狗初始化
	IWDG_Init(4,625);
		while(1){
				IWDG_Feed();

			  

			
			  if(flag_en_1ms){
					flag_en_1ms=0;
					if(ADC_ConvertedValue[0]>output_const){		
						     LED7_ON;
                 PWN_LOCK1_ON;
                 PWN_LOCK1_ON;
                 TIM_SetCompare4(TIM4,0);
                 flag_pwn_on=0;								 
							   HighV_OUT1_ON;
						     delay_ms(10);
								 HighV_OUT1_OFF;
						     LED7_OFF;
					 } 
					 switch(run_type)
					 {
						 case 0:
 
						 break;
						 case 1: 

						 break; 
						 case 2:

						 break;
						 case 3:

						 break;
						 case 4:

						 break;
						 case 5:

						 break;
						 case 6:
               		 
						 break;
						 case 7:
							 
						 break;
						 default:
							run_type=1; 
						 break;
					 }			
				}
			
				if(flag_en_1s){
					flag_en_1s=0;

					LED1_XOR;
					if(lcd_on_time!=0){
						lcd_on_time--;
						LCD_LED_ON;
					}else{
						LCD_LED_OFF;
					}
					
					
					light_value=ADC_ConvertedValue[2]*58/2048;
					if(light_value>58)light_value=58;
					dis_light_num(light_value);
					dis_bar(light_value);
					dis_alarm_point(light_day_value);
					if(light_value>light_day_value){
						LED2_ON;
					}else{
						LED2_OFF;
					}
					
          

			  }
				
				if(flag_en_1500ms){
					flag_en_1500ms=0;
					input_voltage=((float)ADC_ConvertedValue[3]/power_const);//input_voltage=((float)ADC_ConvertedValue[3]/4096*3.3/0.1282);
					dis_intput_voltage(input_voltage);
					
          if(flag_pwn_on==1){
						PWN_LOCK1_ON;
						PWN_LOCK2_ON;
						TIM_SetCompare4(TIM4,0);
						flag_pwn_on=0;
						delay_ms(10);
						HighV_OUT1_ON;
						delay_ms(10);
					  HighV_OUT1_OFF;							
					}else{
							 if(flag_pwn_on==0){
								 if(ADC_ConvertedValue[0]>100){						  
									 HighV_OUT1_ON;
									 delay_ms(10);								 
									 if(ADC_ConvertedValue[0]>100){
										 fang_status=1;									 
									 }else{
										 fang_status=0;										 
									 }
								 }else{
									 fang_status=0;											 
								 }
						   }							 
							// pwm_status=check_pwm();						
					}
					
					
					switch(run_type)
					 {
						 case 0:
							
						 break;
						 case 1: 
               
						 break; 
						 case 2:
							 if(fang_status==0){
						      PWN_LOCK1_OFF;
								  PWN_LOCK2_OFF;
								  TIM_SetCompare4(TIM4,74);			
						      flag_pwn_on=1;
					     }
						 break;
						 case 3:
							 if(fang_status==0&&light_value<=light_day_value){
						      PWN_LOCK1_OFF;
								  PWN_LOCK2_OFF;
								  TIM_SetCompare4(TIM4,74);			
						      flag_pwn_on=1;
					     }
						 break;
						 case 4:
							 if(fang_status==0&&light_value>light_day_value){
						      PWN_LOCK1_OFF;
								  PWN_LOCK2_OFF;
								  TIM_SetCompare4(TIM4,74);			
						      flag_pwn_on=1;
					     }
						 break;
						 case 5:
							
						 break;
						 case 6:
              
						 break;
						 case 7:
							  if(fang_status==0){
						      PWN_LOCK1_OFF;
								  PWN_LOCK2_OFF;
								  TIM_SetCompare4(TIM4,74);			
						      flag_pwn_on=1;
					     }
						 break;
						 default:
							run_type=1; 
						 break;
					 }	
					 
					 
					
					
				
					
			  }
				
				
				if(flag_en_20ms){
					flag_en_20ms=0;	
					if(run_type>4){
						LED3_ON;
					}else{
						LED3_OFF;
					}

					
					
					
				 if(KeyLongPress&KEY1)
				 {
					 if(run_type==5||run_type==7){
						 if(run_type==5){
							 light_day_value--; 							 
						 }
						 
						 STMFLASH_Write(FLASH_SAVE_ADDR,(u16*)sys_set_memory,10);	
						 run_type=1;
					 }else{
						 run_type=5;
					 }
					 dis_ico(run_type);
				 }
				 
				 if(KeyLongPress&KEY2)
				 {
					 if(run_type==6||run_type==7){
						 if(run_type==6){
							 power_const++; 							 
						 }
						 STMFLASH_Write(FLASH_SAVE_ADDR,(u16*)sys_set_memory,10);	
						 run_type=1;
					 }else{
						 run_type=6;
					 }
					 dis_ico(run_type);
				 }
				 
				 if(KeyLongPressHold==(KEY1|KEY2))
				 {
					 run_type=7;
					 dis_ico(run_type);
				 }
					
				 if(KeyPressDown&KEY1)
				 {
					 lcd_on_time=60;
					 LED4_ON;
					 switch(run_type)
					 {
						 case 0:
						 case 1: 
						 case 2:
						 case 3:
						 case 4:
							 run_type++;					   
					     if(run_type>=5)
						   {
							   run_type=1;
						   }
							 STMFLASH_Write(FLASH_SAVE_ADDR,(u16*)sys_set_memory,10);	
						 break;
						 case 5:
							 if(light_day_value<58)light_day_value++;
						   dis_alarm_point(light_day_value);
						 break;
						 case 6:
               if(power_const<254)power_const++;
               input_voltage=((float)ADC_ConvertedValue[3]/power_const);
					     dis_intput_voltage(input_voltage);					 
						 break;
						 case 7:
							 if(output_const<4000)output_const=output_const+10;
						 break;
						 default:
							run_type=1; 
						 break;
					 }				   
						 
					 dis_ico(run_type);
           LED4_OFF;
				 }
				 
				 if(KeyPressDown&KEY2)
				 {
					 lcd_on_time=60;
					 LED5_ON;
					 switch(run_type)
					 {
						 case 0:
						 case 1: 
						 case 2:
						 case 3:
						 case 4:
							 run_type--;	
               if(run_type==0)
						   {
							   run_type=4;
						   }						 
						 break;
						 case 5:
							 if(light_day_value>0)light_day_value--;
               dis_alarm_point(light_day_value);
						 break;
						 case 6:	
               if(power_const>10)power_const--;
               input_voltage=((float)ADC_ConvertedValue[3]/power_const);
					     dis_intput_voltage(input_voltage);									 
						 break;
						 case 7:
							 if(output_const>4000)output_const=output_const-10;
						 break;
						 default:
							run_type=1; 
						 break;
					 }					  
					 dis_ico(run_type);
           LED5_OFF;	
				 }
				 

					
					
					
					
				}
				
				
				

		}//end of while
}//end of main



