#include "iwdg.h"

void IWDG_Init(uint8_t prer,uint16_t rlr)  
{  
	 IWDG->KR=0x5555; //�������PR��RLR�Ĵ���
   IWDG->PR=prer;  //���÷�Ƶ
   IWDG->RLR=rlr; //�趨��������ֵ
   IWDG->KR=0xaaaa; //����װ��ֵ
   IWDG->KR=0xcccc;  //�������Ź���ʱ��

}  


void IWDG_Feed(void) 
{  
 IWDG->KR=0XAAAA;//
}  
