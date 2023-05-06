#ifndef __ADC_H
#define	__ADC_H


#include "stm32f10x.h"
void ADC1_Init(void);
void ADC_average(void);
extern uint16_t  ADC_1s_Value_res[4];
extern __IO uint16_t ADC_ConvertedValue[4];

#endif /* __ADC_H */

