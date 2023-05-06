#ifndef __MEMORY_H
#define	__MEMORY_H
#include "stm32f10x.h"



extern uint16_t  sys_set_memory[10];
#define run_type           sys_set_memory[0]
#define light_day_value    sys_set_memory[1]
#define power_const        sys_set_memory[2]
#define output_const       sys_set_memory[3]
#define lcd_on_time        sys_set_memory[4]


#define OFF           0X0001
#define FULL_OUT      0X0002
#define NIGHT_OUT     0X0003
#define DAY_OUT       0X0004
#define SET_LIGHT     0X0005
#define SET_POWER     0X0006
#define SET_OUT_VOL   0X0007


extern uint16_t light_value; 
extern uint8_t flag_pwn_on;
extern uint8_t fang_status;
extern uint8_t pwm_status;

#endif
