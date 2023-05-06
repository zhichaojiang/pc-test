#include "iwdg.h"

void IWDG_Init(uint8_t prer,uint16_t rlr)  
{  
	 IWDG->KR=0x5555; //允许访问PR和RLR寄存器
   IWDG->PR=prer;  //设置分频
   IWDG->RLR=rlr; //设定计数器初值
   IWDG->KR=0xaaaa; //初次装初值
   IWDG->KR=0xcccc;  //启动看门狗定时器

}  


void IWDG_Feed(void) 
{  
 IWDG->KR=0XAAAA;//
}  
