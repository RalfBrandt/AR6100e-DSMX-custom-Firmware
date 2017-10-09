#ifndef TIMER_H
#define TIMER_H

#include "SleepTimer_1.h"

//variables

typedef void (*tmr_callback_t)(void);

#define Timer_Stop() Timer8_1_Stop()
#define Timer_Start() Timer8_1_Start()
#define Timer_SetCompare(value) Timer8_1_WriteCompareValue(value) 
#define Timer_SetPeriod(value) Timer8_1_WritePeriod(value)

//prototypes
void Timer_init (void);
void Timer_Wait_ms(BYTE ms);
void Timer_SetCallback(tmr_callback_t cb_fn);
WORD Timer_GetTime(void);

#endif //TIMER_H