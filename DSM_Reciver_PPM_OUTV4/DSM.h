#ifndef DSM_H
#define DSM_H
#include "cyrf6936.h"
#include "config.h"
/*
* 0x1 DSM2 less that 8 chanal 1024 Bit 
* 0x2 DSM2 8 or more chanal 1024 Bit
* 0x11/0x12 like 0x1/0x2 but 2048 Bit
*next is the chanal data, one chanal per WORD
*BITS: the lowes 10/11 bit is the chanal value, right above (4 Bit) is the chanal Number
* xxCCCCVVVVVVVVVV (10 bit) or xCCCCVVVVVVVVVVV (11Bit)*/

#define VC3_CLK_DIV 256u

//reciver response
#define PROTOC_IS_DSMX(x)			((x&0xA0)==0xA0)
#define PROTOC_IS_DSM_11MS(x)	((x&0xB2)==0x2 ||(x&0xB2)==0xB2) 
#define PROTOC_IS_DSM_11BIT(x) (((x & 0x30)>>4)?1:0)

#define DSM_BIND_POWER 0x07

#define DSM_STATE_BIND 0
#define DSM_STATE_BIND_RCV 1
#define DSM_STATE_BIND_RCV_WAIT 2
#define DSM_STATE_BIND_RCV_START_ACK 3
#define DSM_STATE_BIND_ACK 4
#define DSM_STATE_BIND_DONE 5
#define DSM_STATE_SYNC_AB 6
#define DSM_STATE_SYNC_X 10
#define DSM_STATE_LOCKED 11

#define DSM_BIND_ACK_NUM   100         // number of bin ACK packets to send

#define DSM_MAX_CH 0x4F
#define DSM_CH_CNT 23

#define DSM_FULL_SEQUENCE_TIME (22000u/VC3_CLK_DIV)
#define DSM_SCAN_TIME (22000u/VC3_CLK_DIV)
#define DSM_TIME_BIND_RCV (12000u/VC3_CLK_DIV)
#define DSM_TIME_BIND_ACK (10000u/VC3_CLK_DIV)
#define DSM_TIME_CHA_CHB (4000u/VC3_CLK_DIV)
#define DSM_TIME11MS ((DSM_SCAN_TIME/2)-DSM_TIME_CHA_CHB)
#define DSM_TIME22MS (DSM_SCAN_TIME-DSM_TIME_CHA_CHB)
#define DSM_TIME_EXTRA (500u/VC3_CLK_DIV)


extern BOOL DSM_Is_DSMX;		//true for DSMX false for DSM2
extern BOOL DSM_Is_11ms;		//true for 11ms update
extern BOOL DSM_Is_11Bit;		//true for 11bit resolution
extern WORD DSM_Perriode;		//cycle time - 4000

extern BYTE State;	
extern volatile BOOL new_data;
extern volatile BOOL Rcv_Timeout;


#define DSM_BIND_DONE() (State>=DSM_STATE_LOCKED) 
#define DSM_BIND_WAIT() (State<DSM_STATE_BIND_RCV_WAIT)
#define DSM_BIND_ACK() (State>=DSM_STATE_BIND_RCV_START_ACK)

#define DSM_INSYNC()  (State>=DSM_STATE_LOCKED) 

void DSM_Init(void);
void DSM_Cyclic(void);
void DSM_initialize_bind(void);
void DSM_initialize_Recive(void);
void DSM_Set_SyncX_State(void );
void DSM_Save_Failsafe_Presets(void);
void DSM_Load_FS_Data(void);

typedef struct  config_s{
BYTE mfg_id[4];	//manufacturer ID of cyrf6936
BOOL Is_DSMX;		//true for DSMX false for DSM2
BOOL Is_11ms;		//true for 11ms update
BOOL Is_11Bit;		//true for 11bit resolution
BOOL Preste_Failsafe; //true if preset failsave is requested
WORD ppm_fs_Data[DSM_OUT_CH_CNT];	//the pulse len valune for the chanales
}config_s;

#define cyrfmfg_id config.mfg_id
#define DSM_Is_DSMX config.Is_DSMX
#define DSM_Is_11ms config.Is_11ms
#define DSM_Is_11Bit config.Is_11Bit
#define Preste_Failsafe config.Preste_Failsafe
#define ppm_fs_Data config.ppm_fs_Data

extern config_s config;
#endif //DSM_H