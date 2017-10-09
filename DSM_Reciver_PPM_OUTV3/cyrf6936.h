#ifndef CYRF6936_H
#define CYRF6936_H
#include "CYRF6936_REG.h"

#define RS_HI() RST_On()
#define RS_LO()	RST_Off()
#define CS_HI() CS_PIN_On()
#define CS_LO() CS_PIN_Off()

#define CYRF_WRITE_BIT          (0x01<<7)
#define CYRF_INCR_BIT	        (0x01<<6)

#define CYRF_SetRFChannel(ch) CYRF_WriteRegister(CYRF_CHANNEL, ch)
#define CYRF_SetSOPCode(p_sop_code) CYRF_WriteRegisterMulti(CYRF_SOP_CODE,p_sop_code,8)
#define CYRF_SetDataCode(p_datacodes,len) CYRF_WriteRegisterMulti(CYRF_DATA_CODE,p_datacodes,len)
#define CYRF_WritePreamble(p_preamble) CYRF_WriteRegisterMulti(CYRF_PREAMBLE,p_preamble,3)
#define CYRF_StartReceive() CYRF_WriteRegister(CYRF_RX_CTRL, RX_GO|RXC_IRQEN|RXE_IRQEN)
#define CYRF_ReadRSSI() CYRF_ReadRegister(CYRF_RSSI)
#define CYRF_WriteTx_Data(p_data) CYRF_WriteRegisterMultiD(CYRF_TX_BUFFER,p_data,(sizeof(p_data)/sizeof(BYTE)))
#define CYRF_ReadRx_data(p_data,cnt) CYRF_ReadRegisterMulti(CYRF_RX_BUFFER,p_data,cnt)
#define CYRF_Rx_cnt() CYRF_ReadRegister(CYRF_RX_COUNT)

extern volatile BOOL CY_irq;

void CYRF_Init(void );
void CYRF_Reset(void);
void CYRF_WriteRegister(BYTE reg, BYTE val);
BYTE CYRF_ReadRegister(BYTE reg);
void CYRF_ReadRegisterMulti(BYTE reg, BYTE data[], BYTE cnt);
void CYRF_WriteRegisterMulti(BYTE reg, BYTE const data[], BYTE cnt);
void CYRF_WriteRegisterMultiD(BYTE reg, BYTE data[], BYTE cnt);
void CYRF_GetMfgData(BYTE data[]);
void CYRF_ReadRegisterInc(BYTE reg, BYTE data[], BYTE cnt);
void CYRF_WriteRegisterInc(BYTE reg,BYTE data[] , BYTE cnt);
void CYRF_SetCRCSeed(WORD crc);


#endif //CYRF6936_H