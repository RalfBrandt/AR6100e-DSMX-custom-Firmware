#include "PSoCAPI.h"    // PSoC API definitions for all User Modules
#include "CYRF6936.h"
#include "delay.h"
#include "timer.h"

volatile BOOL CY_irq;

//called on a GPIO interrupt
#pragma interrupt_handler GPIO_ISR
void GPIO_ISR(void )
{
	if (PRT0DR&CY_IRQPin_MASK) //Check if  pin went high
	{
		CY_irq=TRUE;
	}
}


//initialize cyrf chip
void CYRF_Init(void )
{
	RST_Start();
	CS_PIN_Start();
	SPIM_1_Start(SPIM_1_SPIM_MODE_0 | SPIM_1_SPIM_MSB_FIRST);
	//manua inline
	//CYRF_Reset();
	//reset cyrf chip
	//void CYRF_Reset(void)
	{
	    RS_HI();
		CS_HI();
	    Timer_Wait_ms(2);
	    RS_LO();
	    Timer_Wait_ms(10);
	}
    CYRF_WriteRegister(CYRF_XACT_CFG, (CYRF_ACK_TO_12x));
    Delay50uTimes(100);
	M8C_EnableIntMask(INT_MSK0,INT_MSK0_GPIO); 
	CY_irq=FALSE;
}


//write a singel register
void CYRF_WriteRegister(BYTE reg, BYTE val)
{
CYRF_WriteRegisterMultiD(reg,&val,1);
}


//write a single register cnt times
void CYRF_WriteRegisterMulti(BYTE reg,BYTE const data[] , BYTE cnt)
{
	BYTE n;
    CS_LO();
	//wait for buffer empty
	while( ! (SPIM_1_bReadStatus() & SPIM_1_SPIM_TX_BUFFER_EMPTY ) );
	//write address
	SPIM_1_SendTxData(CYRF_WRITE_BIT|reg);
    for(n = 0; n < cnt; n++)
    {
		//wait for buffer empty
		while( ! (SPIM_1_bReadStatus() & SPIM_1_SPIM_TX_BUFFER_EMPTY ) );
	    //write data
		SPIM_1_SendTxData(data[n]);
    }
	while( ! (SPIM_1_bReadStatus() & SPIM_1_SPIM_SPI_COMPLETE ) );
	CS_HI();
}
void CYRF_WriteRegisterMultiD(BYTE reg, BYTE data[], BYTE cnt)
{
	BYTE n;
    CS_LO();
	//wait for buffer empty
	while( ! (SPIM_1_bReadStatus() & SPIM_1_SPIM_TX_BUFFER_EMPTY ) );
	//write address
	SPIM_1_SendTxData(CYRF_WRITE_BIT|reg);
    for(n = 0; n < cnt; n++)
    {
		//wait for buffer empty
		while( ! (SPIM_1_bReadStatus() & SPIM_1_SPIM_TX_BUFFER_EMPTY ) );
	    //write data
		SPIM_1_SendTxData(data[n]);
    }
	while( ! (SPIM_1_bReadStatus() & SPIM_1_SPIM_SPI_COMPLETE ) );
	CS_HI();
}


void CYRF_WriteRegisterInc(BYTE reg,BYTE  data[] , BYTE cnt)
{
CYRF_WriteRegisterMultiD(CYRF_INCR_BIT| reg,data,cnt);
}

//read a singele register 
BYTE CYRF_ReadRegister(BYTE reg)
{
BYTE data;
	CYRF_ReadRegisterMulti(reg,&data,1);
	return data;
}

//read a singel register cnt times
void CYRF_ReadRegisterMulti(BYTE reg, BYTE data[], BYTE cnt)
{
	BYTE n;
	BYTE status;
    CS_LO();
	//wait for buffer empty
	while( ! (SPIM_1_bReadStatus() & SPIM_1_SPIM_TX_BUFFER_EMPTY ) );
	//write address
	SPIM_1_SendTxData(reg);
	//wait for buffer empty
	while( ! (status=SPIM_1_bReadStatus() & SPIM_1_SPIM_TX_BUFFER_EMPTY ) );
    //dummy write
	SPIM_1_SendTxData(0x00);
	//wait for gabage byte read
	while( ! (status=SPIM_1_bReadStatus() & SPIM_1_SPIM_RX_BUFFER_FULL ) );
	SPIM_1_bReadRxData();
	
    
    for(n=0;(n<cnt);)
	{
		//if buffer empty
		status=SPIM_1_bReadStatus();
		if(  (status & SPIM_1_SPIM_TX_BUFFER_EMPTY ) );
			{
		    //dummy write
			SPIM_1_SendTxData(0x00);
			}
		//if data		
		if(  (status & SPIM_1_SPIM_RX_BUFFER_FULL ) );
		{
			data[n]=SPIM_1_bReadRxData();
			n++;
		}
    };
	CS_HI();
}
void CYRF_ReadRegisterInc(BYTE reg, BYTE data[], BYTE cnt)
{
	CYRF_ReadRegisterMulti(reg|CYRF_INCR_BIT,data,cnt);
}


//get Mfg ID
void CYRF_GetMfgData(BYTE data[])
{
    /* Fuses power on */
    CYRF_WriteRegister(CYRF_MFG_ID, 0xFF);

    CYRF_ReadRegisterMulti(CYRF_MFG_ID, data, 6);

    /* Fuses power off */
    CYRF_WriteRegister(CYRF_MFG_ID, 0x00); 
}

void CYRF_SetCRCSeed(WORD crc)
{
    CYRF_WriteRegister(CYRF_CRC_SEED_LSB,crc & 0xff);
    CYRF_WriteRegister(CYRF_CRC_SEED_MSB,crc >> 8);
}
