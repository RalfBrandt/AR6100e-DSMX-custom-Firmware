//----------------------------------------------------------------------------
// C main line
//----------------------------------------------------------------------------

//98000BFE295413FE26A81BFE0154 //DSMX

//900005FF14AA09FF13540DFF00AA   //DSM2

#include <m8c.h>        // part specific constants and macros
#include "PSoCAPI.h"    // PSoC API definitions for all User Modules
#include "timer.h"
#include "CYRF6936.h"
#include "DSM.h"
#include "config.h"
#include "ppm.h"



//global data
BOOL LV_Detect=FALSE;
//#define DEBUG

// Declare LVD_ISR as ISR
#pragma interrupt_handler LVD_ISR
void LVD_ISR(void)
{
 	LV_Detect=TRUE;
	M8C_ClearIntFlag(INT_MSK0,INT_MSK0_VOLTAGE_MONITOR);
	M8C_DisableIntMask(INT_MSK0,INT_MSK0_VOLTAGE_MONITOR); 
}


void main(void)
{
	BOOL Bind;
	//initialize everiting

	//enable glogal interrupts
	M8C_EnableGInt;		
	M8C_EnableIntMask(INT_MSK0,INT_MSK0_VOLTAGE_MONITOR); 
	ppm_Init();

	LED_1_Start();
	CH0_OUT_Start();
	CH1_OUT_Start();
	CH2_OUT_Start();
	CH3_OUT_Start();
	CH4_OUT_Start();
	CH5_OUT_Start();
	Timer_init();
	DSM_Init();

#ifndef DEBUG
	E2PROM_1_Start();
#endif


Bind=(Bind_Port_Data_ADDR&Bind_Port_MASK)?FALSE:TRUE;
Bind=Bind||!ReadConfig(&config,sizeof (config_s));	
	

if (Bind)
	{
	BYTE n=0;
	DSM_initialize_bind();
	do
		{
		if (LV_Detect)	
			LED_1_Switch((SleepTimer_1_iGetTickCntr()&0x340)==0x340?1:0);
		else if (DSM_BIND_WAIT())
			LED_1_Switch((SleepTimer_1_iGetTickCntr()&0x100)==0x100?1:0);
		else if (DSM_BIND_ACK())
			LED_1_Switch((SleepTimer_1_iGetTickCntr()&0x40)==0x40?1:0);
		DSM_Cyclic();
		}
	//wait till binding is done
	while(!DSM_BIND_DONE());
	
	do 	//wait for stable
		{
			if (new_data)
				{
				new_data=0;	
				n++;	
				}
		DSM_Cyclic();
		}
	while (n<5);
		
	//save falisave position
	if(Bind_Port_Data_ADDR&Bind_Port_MASK)
	{
			DSM_Save_Failsafe_Presets();
	}
	

	//save configuration to FLASH
	Timer_Stop();
	SaveConfig(&config,sizeof (config_s));
	Timer_Start();
	}
	else 
	{
		DSM_initialize_Recive();	
		do 
		{
			Rcv_Timeout=FALSE;
			new_data=FALSE;	
			DSM_Cyclic();
		}while (!DSM_INSYNC());
	}
		do
			{
			DSM_Cyclic();
			if (LV_Detect)	
				LED_1_Switch((SleepTimer_1_iGetTickCntr()&0x340)==0x340?1:0);
			else	
				LED_1_Switch(DSM_INSYNC());
			if (Rcv_Timeout)
			{
				DSM_Load_FS_Data();
				Rcv_Timeout=FALSE;
				new_data=TRUE;
			}
			if (PPM_IS_PPM_DONE())
				{
				if (new_data)
					{
					new_data=FALSE;	
					PPM_START_ONE_PPM_TRAIN();
					}
				}
			}
		while (1);	
}
