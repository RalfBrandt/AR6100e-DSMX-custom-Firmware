/*
*PPM.C
*A 16 Bit PWM module  is used to gennerate the PPM train
*The PWM actually gennerates an inverted CPPM __|_|_|_|_|_|_|_|_|___|_|_|_|_|_|_|_|_|___|_
*this has the advantage that the pulse width can stay constant, only the periode has to be changed
*on everey compare match interrupt the periode value for the next chanel is loaded
*the last chanal value has an extra large value and is used to gennerate the sync gap
*/

#include <m8c.h>        // part specific constants and macros
#include "PSoCAPI.h"    // PSoC API definitions for all User Modules
#include "config.h"
#include "ppm.h"

//#define DEBUG

volatile BYTE ppm_Nr=0;//the chanal counter
volatile BOOL ppm_Run=0;//start one pulse train
BOOL TC_IRQ;

#define PWM_TC_IRQ 0x31;
#define PWM_CM_IRQ 0x39;
//initialize PPM output
void ppm_Init(void )
{
	
int n;
	//Init PPM_DATA array
	for (n=0;n<PPM_PULSE_COUNT;n++)
	{	//set to center
		ppm_Data[n]=PPM_OUT_CENTER_LEN;
	}
	//enable compare match interrupt of the PWM
	PWM16_1_EnableInt();
	//pulse widht is actually the small gap between the PPM pulses
	PWM16_1_WritePulseWidth(PPM_OUT_PULSE_GAP_LEN_US);
	//disconnect the PIN from the PWM and  set the pin to High
	PPM_DISCON_SET_OUT_PIN_HIGH;
	//init pulse counter, will loop thru the cannels
	ppm_Nr=0;		
	TC_IRQ=TRUE;
	PWM16_1_FUNC_MSB_REG=PWM_TC_IRQ;
	//set a initial pulse len, just to have somthing in ther will be change in the interrupt service
	PWM16_1_WritePeriod(PPM_OUT_SYNC_PULSE_LEN);
}//END OFF ppm_Init

void Switch_LED(BYTE val)
{
#ifndef DEBUG	
	switch (ppm_Nr)
	{
		case 2:
		{
			LED_1_7_Switch(val);
		}
		break;
		case 3:
		{
			LED_1_1_Switch(val);
		}
		break;
		case 4:
		{
			LED_1_5_Switch(val);
		}
		break;
		case 5:
		{
			LED_1_0_Switch(val);
		}
		break;
		case 6:
		{
			LED_1_4_Switch(val);
		}
		break;
		case 7:
		{
			LED_1_6_Switch(val);
		}
		break;
	}
#endif
}

void PPM_Start_One_PPM_Train(void )
{
	ppm_Run=TRUE;
	PPM_RECON_OUT_PIN;	//reconect i/O PIN to PWM
	ppm_Nr=1;//reset counter
	PWM16_1_WritePeriod(ppm_Data[0]+PPM_OUT_PULSE_GAP_LEN_US);//load pulse len of first channel
	//start the PWM Module
	PWM16_1_Start();
}

/*inerrupt service routine for the PWM module
*will be called on TC
*-load pulse len of the next PPM pulse
*- increase pulse counter
*/
#pragma interrupt_handler PWM16_1_CMP_ISR
void PWM16_1_CMP_ISR(void )
{
	if (TC_IRQ)
	{
		//Sync is send out we are done 
		if (ppm_Nr==PPM_PULSE_COUNT+2) 
			{ //we are done 
				ppm_Run=0;		//signal that we are done
				PWM16_1_Stop();
			}
		else if (ppm_Nr==PPM_PULSE_COUNT+1) 
			{ //we are done 
				PPM_DISCON_SET_OUT_PIN_HIGH;	//disconect IO pin from PWM and set to High
			}
		//load pulse len of next chanal
		else 
		{	//check if that is the last chanel is done
			if(ppm_Nr==PPM_PULSE_COUNT)
			{
				PWM16_1_WritePeriod(PPM_OUT_SYNC_PULSE_LEN); 
			}
			else 
			{
				PWM16_1_WritePeriod(ppm_Data[ppm_Nr]+PPM_OUT_PULSE_GAP_LEN_US);//load pulse len of the next pulse
			}
		}
		ppm_Nr++;
		Switch_LED(TRUE);
		TC_IRQ=FALSE;
		PWM16_1_FUNC_MSB_REG=PWM_CM_IRQ;
	}
	else 
	{
		Switch_LED(FALSE);
		TC_IRQ=TRUE;
		PWM16_1_FUNC_MSB_REG=PWM_TC_IRQ;
	}
}//END OFF PWM16_1_CMP_ISR

