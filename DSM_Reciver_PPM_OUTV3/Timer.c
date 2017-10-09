#include "PSoCAPI.h"    // PSoC API definitions for all User Modules
#include "timer.h"

//WORD systic=0;   //will be incremented once per 1,953125 ms
WORD cnt_last;
tmr_callback_t timer_cb=0;

//a delay
void Timer_Wait_ms(BYTE ms)
{
SleepTimer_1_TickWait(ms>>2);
}



void Timer_init (void)
{
timer_cb=0;
SleepTimer_1_EnableInt();
SleepTimer_1_Start();
Timer8_1_EnableInt();
}




void Timer_SetCallback(tmr_callback_t cb_fn)
{
	timer_cb=cb_fn;
}

//#pragma interrupt_handler Sleep_Timer_Interrupt

/*/interrupt handler on TC of LSB
/void Sleep_Timer_Interrupt(void )
{
	systic++;
}*/

#pragma interrupt_handler Timer8_1_Interrupt

void Timer8_1_Interrupt(void)
{
	if(timer_cb!=0)
		timer_cb();
}