#ifndef __SYSTICK_H
#define __SYSTICK_H

#include "stm32f10x.h"

#define COUNTS_10MS   10
#define COUNTS_20MS   20
#define COUNTS_50MS   50
#define COUNTS_1S     1000
#define COUNTS_1500MS     1500
#define COUNTS_1MS    1

void SysTick_Init(void);
void Delay_us(__IO u32 nTime);

#endif /* __SYSTICK_H */

