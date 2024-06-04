#ifndef __canfestival_timer_H
#define __canfestival_timer_H
#include "sys.h"
#include "stdlib.h"
#include "stm32f10x.h"
#include "canfestival.h"


void TIMConfig(TIM_TypeDef* TIMx, uint16_t TIM_Period, uint16_t TIM_Prescaler);
void NVIC_Configuration(void);
void setTimer(TIMEVAL value);
TIMEVAL getElapsedTime(void);

#endif 
