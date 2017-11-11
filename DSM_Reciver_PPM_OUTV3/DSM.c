#include "PSoCAPI.h"    // PSoC API definitions for all User Modules
#include "m8c.h"
#include "dsm.h"
#include "timer.h"
#include "ppm.h"

//#define DEBUG

//share memory with flash buffer
extern RAM_D mem;
#define tx_buf mem.b.buf0
//BYTE tx_buf[16];	//transmit buffer
#define rx_buf mem.b.buf1
//BYTE rx_buf[16];	//recive buffer
//BYTE rx_data[16]; //recived data
#define rx_data mem.rx_d 


//global data
BYTE channels[DSM_CH_CNT]; 	//list of channels
BYTE chidx;			//current channel index	
BOOL Ch_A;			//true for channel A false for channel B
BYTE sop_col;		
BYTE data_col;		
BYTE State;		
BYTE num_channels;	//number fo transmit channels
config_s config;
WORD DSM_Perriode;		//cycle time - 4000
BYTE lost_cnt;
BOOL New_RCV_Data;
volatile BOOL new_data;
volatile BOOL Rcv_Timeout;

//prototypes
void DSM_initialize_bind_ack(void);
void calc_dsmx_channel(void);
void DSM_StartBindAck(void);
void DSM_StartRcv(void);
void Bind_TimeOut_cb(void);
void Process_BindRcvIrq(void);
void ProcessNewData(void );
BYTE DSM_DeterminBitCount(void);
BOOL DSM_process_Data(void);

volatile WORD ppm_Data[PPM_PULSE_COUNT];	//the pulse len value for the chanales


static const BYTE pn_bind[] = {0x98, 0x88, 0x1B, 0xE4, 0x30, 0x79, 0x03, 0x84}; //used for sending bind response

static const BYTE pncodes[5][9][8] = {
    /* Note these are in order transmitted (LSB 1st) */
{ /* Row 0 */
  /* Col 0 */ {0x03, 0xBC, 0x6E, 0x8A, 0xEF, 0xBD, 0xFE, 0xF8},
  /* Col 1 */ {0x88, 0x17, 0x13, 0x3B, 0x2D, 0xBF, 0x06, 0xD6},
  /* Col 2 */ {0xF1, 0x94, 0x30, 0x21, 0xA1, 0x1C, 0x88, 0xA9},
  /* Col 3 */ {0xD0, 0xD2, 0x8E, 0xBC, 0x82, 0x2F, 0xE3, 0xB4},
  /* Col 4 */ {0x8C, 0xFA, 0x47, 0x9B, 0x83, 0xA5, 0x66, 0xD0},
  /* Col 5 */ {0x07, 0xBD, 0x9F, 0x26, 0xC8, 0x31, 0x0F, 0xB8},
  /* Col 6 */ {0xEF, 0x03, 0x95, 0x89, 0xB4, 0x71, 0x61, 0x9D},
  /* Col 7 */ {0x40, 0xBA, 0x97, 0xD5, 0x86, 0x4F, 0xCC, 0xD1},
  /* Col 8 */ {0xD7, 0xA1, 0x54, 0xB1, 0x5E, 0x89, 0xAE, 0x86}
},
{ /* Row 1 */
  /* Col 0 */ {0x83, 0xF7, 0xA8, 0x2D, 0x7A, 0x44, 0x64, 0xD3},
  /* Col 1 */ {0x3F, 0x2C, 0x4E, 0xAA, 0x71, 0x48, 0x7A, 0xC9},
  /* Col 2 */ {0x17, 0xFF, 0x9E, 0x21, 0x36, 0x90, 0xC7, 0x82},
  /* Col 3 */ {0xBC, 0x5D, 0x9A, 0x5B, 0xEE, 0x7F, 0x42, 0xEB},
  /* Col 4 */ {0x24, 0xF5, 0xDD, 0xF8, 0x7A, 0x77, 0x74, 0xE7},
  /* Col 5 */ {0x3D, 0x70, 0x7C, 0x94, 0xDC, 0x84, 0xAD, 0x95},
  /* Col 6 */ {0x1E, 0x6A, 0xF0, 0x37, 0x52, 0x7B, 0x11, 0xD4},
  /* Col 7 */ {0x62, 0xF5, 0x2B, 0xAA, 0xFC, 0x33, 0xBF, 0xAF},
  /* Col 8 */ {0x40, 0x56, 0x32, 0xD9, 0x0F, 0xD9, 0x5D, 0x97}
},
{ /* Row 2 */
  /* Col 0 */ {0x40, 0x56, 0x32, 0xD9, 0x0F, 0xD9, 0x5D, 0x97},
  /* Col 1 */ {0x8E, 0x4A, 0xD0, 0xA9, 0xA7, 0xFF, 0x20, 0xCA},
  /* Col 2 */ {0x4C, 0x97, 0x9D, 0xBF, 0xB8, 0x3D, 0xB5, 0xBE},
  /* Col 3 */ {0x0C, 0x5D, 0x24, 0x30, 0x9F, 0xCA, 0x6D, 0xBD},
  /* Col 4 */ {0x50, 0x14, 0x33, 0xDE, 0xF1, 0x78, 0x95, 0xAD},
  /* Col 5 */ {0x0C, 0x3C, 0xFA, 0xF9, 0xF0, 0xF2, 0x10, 0xC9},
  /* Col 6 */ {0xF4, 0xDA, 0x06, 0xDB, 0xBF, 0x4E, 0x6F, 0xB3},
  /* Col 7 */ {0x9E, 0x08, 0xD1, 0xAE, 0x59, 0x5E, 0xE8, 0xF0},
  /* Col 8 */ {0xC0, 0x90, 0x8F, 0xBB, 0x7C, 0x8E, 0x2B, 0x8E}
},
{ /* Row 3 */
  /* Col 0 */ {0xC0, 0x90, 0x8F, 0xBB, 0x7C, 0x8E, 0x2B, 0x8E},
  /* Col 1 */ {0x80, 0x69, 0x26, 0x80, 0x08, 0xF8, 0x49, 0xE7},
  /* Col 2 */ {0x7D, 0x2D, 0x49, 0x54, 0xD0, 0x80, 0x40, 0xC1},
  /* Col 3 */ {0xB6, 0xF2, 0xE6, 0x1B, 0x80, 0x5A, 0x36, 0xB4},
  /* Col 4 */ {0x42, 0xAE, 0x9C, 0x1C, 0xDA, 0x67, 0x05, 0xF6},
  /* Col 5 */ {0x9B, 0x75, 0xF7, 0xE0, 0x14, 0x8D, 0xB5, 0x80},
  /* Col 6 */ {0xBF, 0x54, 0x98, 0xB9, 0xB7, 0x30, 0x5A, 0x88},
  /* Col 7 */ {0x35, 0xD1, 0xFC, 0x97, 0x23, 0xD4, 0xC9, 0x88},
  /* Col 8 */ {0xE1, 0xD6, 0x31, 0x26, 0x5F, 0xBD, 0x40, 0x93}
},
{ /* Row 4 */
  /* Col 0 */ {0xE1, 0xD6, 0x31, 0x26, 0x5F, 0xBD, 0x40, 0x93},
  /* Col 1 */ {0xDC, 0x68, 0x08, 0x99, 0x97, 0xAE, 0xAF, 0x8C},
  /* Col 2 */ {0xC3, 0x0E, 0x01, 0x16, 0x0E, 0x32, 0x06, 0xBA},
  /* Col 3 */ {0xE0, 0x83, 0x01, 0xFA, 0xAB, 0x3E, 0x8F, 0xAC},
  /* Col 4 */ {0x5C, 0xD5, 0x9C, 0xB8, 0x46, 0x9C, 0x7D, 0x84},
  /* Col 5 */ {0xF1, 0xC6, 0xFE, 0x5C, 0x9D, 0xA5, 0x4F, 0xB7},
  /* Col 6 */ {0x58, 0xB5, 0xB3, 0xDD, 0x0E, 0x28, 0xF1, 0xB0},
  /* Col 7 */ {0x5F, 0x30, 0x3B, 0x56, 0x96, 0x45, 0xF4, 0xA1},
  /* Col 8 */ {0x03, 0xBC, 0x6E, 0x8A, 0xEF, 0xBD, 0xFE, 0xF8}
},};


static const BYTE init_vals[][2] = {
//	{CYRF_MODE_OVERRIDE, 0x01},
    {CYRF_CLK_EN, CLK_EN_RXF},  //0x02
    {CYRF_AUTO_CAL_TIME, 0x3c}, //see cyrf manual
    {CYRF_AUTO_CAL_OFFSET, 0x14}, //see cyrf manual
	{CYRF_IO_CFG,IO_CFG_IRQ_POL}, //0x40 IRQ active High 
    {CYRF_RX_CFG, RX_LNA|FAST_TURN_EN}, //0x48 Fast Turn Mode Enable, Low Noise Amplifier ON
    {CYRF_TX_OFFSET_LSB, 0x55},//see cyrf manual
    {CYRF_TX_OFFSET_MSB, 0x05},//see cyrf manual
    {CYRF_XACT_CFG,CYRF_XACT_END_STATE(CYRF_MODE_IDLE)|CYRF_FRC_END}, //0x24 Force  Idle Mode
    {CYRF_DATA64_THOLD, 0x0a},//see cyrf manual
    {CYRF_XACT_CFG,CYRF_XACT_END_STATE(CYRF_MODE_IDLE)}, //0x04 Transaction End State Idle Mode
	{CYRF_ANALOG_CTRL, ALL_SLOW}, //0x01 all slow
    {CYRF_XACT_CFG,CYRF_XACT_END_STATE(CYRF_MODE_IDLE)| CYRF_FRC_END}, //0x24 Force IDLE
	{CYRF_RX_ABORT, 0x00}, //Clear RX abort
    {CYRF_DATA64_THOLD, 0x0a}, //set pn correlation threshold
    {CYRF_FRAMING_CFG, SOP_LEN|0xa}, //set sop len and threshold
    {CYRF_RX_ABORT, 0x0f}, //Clear RX abort?
};


static const BYTE rcv_vals[][2] = {
    {CYRF_TX_CFG,TX_DM(TX_DM_8DR)|DSM_BIND_POWER}, //0xD DDR Mode  32 chip codes
	{CYRF_FRAMING_CFG,LEN_EN|SOP_LEN|SOP_EN|0xE},  //0xEE SOP Enable SOP code length is 64 chips Packet Length Enable  SOP Correlator Threshold=0xE
    {CYRF_TX_OVERRIDE, 0x00},
    {CYRF_RX_OVERRIDE, 0x00},
};

static const BYTE preamble[]={0x04,0x33,0x33};
static  BYTE tx_cmd[]={0xA,TXE_IRQEN|TXC_IRQEN|TX_GO|TX_CLR}; //0xC3

void SetChannel(void)
{
	BYTE channel=channels[chidx];
	BYTE pn_row = DSM_Is_DSMX ? (channel - 2)%5 : channel%5;
	WORD CRCSeed=Ch_A?~((WORD)(cyrfmfg_id[0] << 8) + (WORD)cyrfmfg_id[1]):((WORD)(cyrfmfg_id[0] << 8) + (WORD)cyrfmfg_id[1]);
	CYRF_SetRFChannel(channel);
	CYRF_SetCRCSeed(CRCSeed);
    CYRF_SetSOPCode(pncodes[pn_row][sop_col]);
    CYRF_SetDataCode(pncodes[pn_row][data_col], 16);
}

//calculate and set channel CRC , SOP and data code 
void SetCH_INC(void)
{
	Ch_A=!Ch_A;	
#ifdef DEBUG
	LED_1_6_Switch(Ch_A?1:0);
#endif
    if(DSM_Is_DSMX)
        chidx = (chidx + 1) % 23;
    else
        chidx = Ch_A?0:1;
	SetChannel();
}

//load the given config into cyfr6936
void DSM_Load_Config(const BYTE vals[][2],BYTE cnt)
{
BYTE n;

for(n=0;n<cnt;n++)
	{
	CYRF_WriteRegister(vals[n][0],vals[n][1]);
	}
}


//clear recive error and pending interupt flags
void DSM_ClearRxError(void)
{
	BYTE i=100;
	CYRF_ReadRegister(CYRF_RX_IRQ_STATUS);
	CYRF_ReadRegister(CYRF_RX_IRQ_STATUS);
	CYRF_WriteRegister(CYRF_RX_ABORT,ABORT_EN); //abort
	//force end state
	CYRF_WriteRegister(CYRF_XACT_CFG,CYRF_XACT_END_STATE(CYRF_MODE_IDLE)|CYRF_FRC_END);
    while (! (CYRF_ReadRegister(CYRF_XACT_CFG) & CYRF_XACT_END_STATE(CYRF_MODE_IDLE))) 
	{
        if(!--i)
            break;
	}
	//clear abort
	CYRF_WriteRegister(CYRF_RX_ABORT,0);
}
void SYNC_AB_TimeOut_cb(void)
{
	DSM_ClearRxError();
#ifdef DEBUG
	LED_1_5_Invert();
#endif
	channels[chidx]++;
	if(channels[chidx]>DSM_MAX_CH)
		channels[chidx]=0;	
	SetChannel();
	DSM_StartRcv();	
}

static cnt=0;
void SYNC_X_TimeOut_cb(void)
{
	if (cnt==0)
	{
		DSM_ClearRxError();
		SetCH_INC();
		DSM_StartRcv();	
	}
	Rcv_Timeout=TRUE;
	cnt=(cnt+1)%4;
#ifdef DEBUG
	LED_1_5_Invert();
#endif
}

void DSM_Set_SyncX_State(void )
{
		State=DSM_STATE_SYNC_X;
#ifdef DEBUG
		LED_1_7_Off();
#endif
		lost_cnt=0;
		Rcv_Timeout=FALSE;
		if (DSM_Is_DSMX)
			Timer_SetPeriod(DSM_FULL_SEQUENCE_TIME);
		else
			Timer_SetPeriod(DSM_SCAN_TIME+DSM_TIME_EXTRA);
		Timer_SetCallback(SYNC_X_TimeOut_cb);
}

void Rcv_X_TimeOut_cb(void)
{
	Timer_Stop();
	if(Ch_A)
		{
		Timer_SetPeriod(DSM_TIME_CHA_CHB);
		}
	else
		{
		Timer_SetPeriod(DSM_Perriode);
		}
		
	if(lost_cnt++>DSM_CH_CNT/2 && !Ch_A)
		{
		DSM_Set_SyncX_State();
		}
	Timer_Start();
	DSM_ClearRxError();
	SetCH_INC();
	DSM_StartRcv();	
	New_RCV_Data=TRUE;
#ifdef DEBUG
	LED_1_5_Invert();
#endif
}

void DSM_initialize_Recive(void)
{
	chidx=0;
	Ch_A=TRUE;
	Rcv_Timeout=FALSE;
	New_RCV_Data=FALSE;
	lost_cnt=0;
	sop_col = (cyrfmfg_id[0] + cyrfmfg_id[1] + cyrfmfg_id[2] + 2) & 0x07;
    data_col = 7 - sop_col;
	DSM_Load_Config(rcv_vals,sizeof(rcv_vals)/(sizeof(BYTE)*2));
	if(DSM_Is_DSMX)
		{
		calc_dsmx_channel();	
		State=DSM_STATE_SYNC_X;
		}
	else
		{
		channels[0]=channels[1]=1;	
		State=DSM_STATE_SYNC_AB;
		}	
	//set periode to be 11ms or 22ms	
	DSM_Perriode=DSM_Is_11ms?DSM_TIME11MS:DSM_TIME22MS;

	//calculate channel CRC SOP and data code for first channel to transmitt
	Timer_Stop();
	if(DSM_Is_DSMX)
		{	
			Timer_SetPeriod(DSM_FULL_SEQUENCE_TIME);
			Timer_SetCallback(SYNC_X_TimeOut_cb);
		}
	else 
		{
			Timer_SetPeriod(DSM_SCAN_TIME+DSM_TIME_EXTRA);
			Timer_SetCallback(SYNC_AB_TimeOut_cb);
		}
	SetChannel();
	Timer_Start();
	DSM_StartRcv();	
}

void Process_Rvc_Irq(void)
{
	BYTE n;
	if ((( DSM_Is_DSMX) && (rx_buf[0] !=  cyrfmfg_id[2] || rx_buf[1] !=  cyrfmfg_id[3]))
	  ||((!DSM_Is_DSMX) && (rx_buf[0] != ~cyrfmfg_id[2] || rx_buf[1] != ~cyrfmfg_id[3]))) 
	{
		goto Rvc_Error;
	}
#ifdef DEBUG
	LED_1_4_Invert();
#endif
	Timer_Stop();
	if(Ch_A)
		{
		Timer_SetPeriod(DSM_TIME_CHA_CHB+DSM_TIME_EXTRA);
		}
	else
		{
		Timer_SetPeriod(DSM_Perriode+DSM_TIME_EXTRA);
		}

	if (State==DSM_STATE_SYNC_AB)
	{
		if (chidx==1  && channels[0]!=channels[1])
		{
			State =DSM_STATE_SYNC_X;
		}
	Timer_SetPeriod(DSM_SCAN_TIME+DSM_TIME_EXTRA);	
	}

	Timer_Start();

	if (DSM_STATE_SYNC_X==State)
	{
		State=DSM_STATE_LOCKED;
#ifdef DEBUG
		LED_1_7_On(); 
#endif
		Timer_SetCallback(Rcv_X_TimeOut_cb);
	}

	SetCH_INC();
		
	//process data
	for (n=2;n<0x10;n++)
		rx_data[n]=rx_buf[n];
	//rx_data[0]=DSM_Is_DSMX?(DSM_Is_11ms?0xB2:0xA2):DSM_Is_11Bit?(DSM_Is_11ms?0x12:0x11):(DSM_Is_11ms?0x02:0x01);
	//rx_data[1]=0;
	New_RCV_Data=TRUE;
	lost_cnt=0;
	
Rvc_Error:
	DSM_StartRcv();
}


	
BOOL ProcessRxIrqStatus(void)
{
		BYTE Irq_Status[2];
		//read IRQ status
		CYRF_ReadRegisterMulti(CYRF_RX_IRQ_STATUS,Irq_Status,2);
		Irq_Status[0]|=Irq_Status[1]&RXE_IRQ;
		if(Irq_Status[0]&RXC_IRQ)
		{
			BYTE rx_cnt=CYRF_Rx_cnt();
			CYRF_ReadRx_data(rx_buf,rx_cnt);
			if(rx_cnt!=0x10)
			{
				return FALSE;
			}
		}
		if (Irq_Status[0]&RXE_IRQ)
		{
			BYTE Est=CYRF_ReadRegister(CYRF_RX_STATUS);
			return FALSE;
		}
return TRUE;
}

void ProcessNewData(void )
{
		new_data= DSM_process_Data();
}


void DSM_Cyclic(void)
{
	switch(State)
	{
		case DSM_STATE_BIND:
			{
			DSM_ClearRxError();
			DSM_StartRcv();
			State=DSM_STATE_BIND_RCV;
			}
		break;
		case DSM_STATE_BIND_DONE:
			{
				DSM_initialize_Recive();
			}
		break;
		case DSM_STATE_BIND_RCV_START_ACK:
			{
			DSM_initialize_bind_ack();
			DSM_StartBindAck();
			}
	}

	//process interrupt
	if(CY_irq) //we got an IRQ from CYRF6936
	{
		BYTE Irq_Status[2];
		CY_irq=FALSE;
		switch(State)
		{
			case DSM_STATE_BIND_ACK:
				{
				//read IRQ status
				CYRF_ReadRegisterMulti(CYRF_TX_IRQ_STATUS,Irq_Status,2);
				Irq_Status[0]|=Irq_Status[1]&TXE_IRQ;
				//TX done
				if(Irq_Status[0]&TXC_IRQ)
					{
					}
				}
				break;
			case DSM_STATE_BIND_RCV:
			case DSM_STATE_BIND_RCV_WAIT:
				{
					
					if (ProcessRxIrqStatus())
						{
						//we got some thing
						Process_BindRcvIrq();	
						}
				}
				break;
			case DSM_STATE_SYNC_AB:
			case DSM_STATE_SYNC_X:
			case DSM_STATE_LOCKED:	
				{
					if(ProcessRxIrqStatus())
						{
						//we got some thing
						Process_Rvc_Irq();
						}
				}
				break;
			default :
				CYRF_ReadRegisterMulti(CYRF_TX_IRQ_STATUS,Irq_Status,2);
				CYRF_ReadRegisterMulti(CYRF_RX_IRQ_STATUS,Irq_Status,2);
		}
	}
	else //no IRQ to process
	{
		if (New_RCV_Data&& Ch_A)
		{
			New_RCV_Data=FALSE;
			Rcv_Timeout=FALSE;
			ProcessNewData();
		}
	}
}


//calculate dsmX channels 
//found on deviation-tx source
// math by Alexandr Alexandrov code by Sergey Gimaev
//pseudo random gennerator /Linear congruential generator based on "Numerical Recipes" Chapter 7.1
void calc_dsmx_channel(void)
{
    BYTE idx; 
	DWORD id_tmp;
    DWORD id = ~(((DWORD)cyrfmfg_id[0] << 24) | ((DWORD)cyrfmfg_id[1] << 16) | ((DWORD)cyrfmfg_id[2] << 8) | (((DWORD)cyrfmfg_id[3]) << 0));
	idx = 0;
    id_tmp = id;
    while(idx < 23) {
        int i;
        BYTE next_ch;
		int count_3_27 = 0, count_28_51 = 0, count_52_76 = 0;
        id_tmp = id_tmp * 0x0019660D + 0x3C6EF35F; // Randomization
        next_ch = ((id_tmp >> 8) % 0x49) + 3;       // Use least-significant byte and must be larger than 3
        if (((next_ch ^ id) & 0x01 )== 0)
            continue;
        for (i = 0; i < idx; i++) {
            if(channels[i] == next_ch)
                break;
            if(channels[i] <= 27)
                count_3_27++;
            else if (channels[i] <= 51)
                count_28_51++;
            else
                count_52_76++;
        }
        if (i != idx)
            continue;
        if ((next_ch < 28 && count_3_27 < 8)
          ||(next_ch >= 28 && next_ch < 52 && count_28_51 < 7)
          ||(next_ch >= 52 && count_52_76 < 8))
        {
            channels[idx++] = next_ch;
        }
    }
}


//initialise system
void DSM_Init(void)
{
	BYTE n;
	new_data=FALSE;
	//init CYRF6936
	CYRF_Init();
	//set defalut values
	DSM_Is_DSMX=FALSE;
	DSM_Is_11ms=FALSE;
	DSM_Is_11Bit=FALSE;
	Ch_A=TRUE;
	chidx=0;
	Preste_Failsafe=FALSE;
	DSM_Load_Config(init_vals,sizeof(init_vals)/(sizeof(BYTE)*2));

	CYRF_WritePreamble(preamble);
}

/*++++++++++BIND STUFF****************/
static const BYTE bind_vals[][2] = {
    {CYRF_TX_CFG,TX_DC_LEN|TX_DM(TX_DM_SDR)|DSM_BIND_POWER}, //0x38 Set 64 chip, SDR mode
    {CYRF_FRAMING_CFG,SOP_LEN|0xA}, //0x4A set sop len  32 chip and threshold =0xA 
    {CYRF_TX_OVERRIDE, DIS_TXCRC}, //0x4 disable tx CRC
    {CYRF_RX_OVERRIDE, DIS_RXCRC}, //0x4 disable rx CRC
    {CYRF_EOP_CTRL, 0x02}, //set EOP sync == 2
};
BYTE Bind_cnt;		//bind ack pulse counter
BYTE bind_channal;	//channel used to send bind packes


//initialize bind state
void DSM_initialize_bind(void)
{	
	State=DSM_STATE_BIND;
	DSM_Load_Config(bind_vals,sizeof(bind_vals)/(sizeof(BYTE)*2));
	bind_channal=1;
	Bind_cnt=0;
	CYRF_SetRFChannel(bind_channal);
	CYRF_SetDataCode(pncodes[0][8], 16);
	Timer_SetPeriod(DSM_TIME_BIND_RCV);
	Timer_SetCallback(Bind_TimeOut_cb);
	Timer_Start();
}


void DSM_Build_Ack_package(void)
{
	BYTE i;
    WORD ckSum = 0x170;
	tx_buf[0]=rx_buf[0];
	tx_buf[1]=rx_buf[1];
	tx_buf[2]=rx_buf[2];
	tx_buf[3]=rx_buf[3];
    tx_buf[4]=rx_buf[10];
    tx_buf[5]=num_channels;
    tx_buf[6]=DSM_Is_DSMX?(DSM_Is_11ms?0xB2:0xA2):DSM_Is_11Bit?(DSM_Is_11ms?0x12:0x11):(DSM_Is_11ms?0x02:0x01); //rx_buf[12]; //protocoll
    tx_buf[7]=rx_buf[13];//???

	for (i = 0; i < 8; i++)
         ckSum += tx_buf[i];
	tx_buf[8]=(ckSum >> 8);
	tx_buf[9]=(ckSum & 0xff);
}


//start waiting for the bind recive signal
void DSM_StartRcv(void)
{
		CYRF_StartReceive();
		CYRF_ReadRSSI();
}

void DSM_StartBindAck(void)
{
	CYRF_WriteRegisterInc(CYRF_TX_LENGTH,tx_cmd,sizeof(tx_cmd)/sizeof(BYTE));
	CYRF_WriteTx_Data(tx_buf);
}


void Bind_xfer_cb(void)
{
	BYTE i;

	if (Bind_cnt)
	{
		Bind_cnt--;
		DSM_StartBindAck();
	}
	else 
	{
		State=DSM_STATE_BIND_DONE;
#ifdef DEBUG
		LED_1_7_Off();
#endif
		//save Mfg ID of transmitter
		cyrfmfg_id[0]=~tx_buf[0];
		cyrfmfg_id[1]=~tx_buf[1];
		cyrfmfg_id[2]=~tx_buf[2];
		cyrfmfg_id[3]=~tx_buf[3];
		Timer_Stop();
		Timer_SetCallback(0);
	}
}

void DSM_initialize_bind_ack(void)
{
 	DSM_Build_Ack_package();
	State=DSM_STATE_BIND_ACK;
    CYRF_SetDataCode(pn_bind, 16);
	Timer_Stop();
	Timer_SetPeriod(DSM_TIME_BIND_ACK);
	Timer_SetCallback(Bind_xfer_cb);
	Timer_Start();
}

void Bind_TimeOut_cb(void)
{
		DSM_ClearRxError();
#ifdef DEBUG
		LED_1_5_Invert();
#endif
		if (State==DSM_STATE_BIND_RCV_WAIT) //wait for done
		{ 
			Bind_cnt=DSM_BIND_ACK_NUM;
			State=DSM_STATE_BIND_RCV_START_ACK;
		}
		else 
		{
		bind_channal=bind_channal+2;
		if (bind_channal>DSM_MAX_CH)
			bind_channal=1;
		CYRF_SetRFChannel(bind_channal);
		DSM_StartRcv();
		}
}

void Process_BindRcvIrq(void)
{
	BYTE n;
    WORD ckSum= 384 - 0x10;
	Timer_Stop();
	Timer_SetPeriod(DSM_TIME_BIND_RCV);
	Timer_Start();
#ifdef DEBUG
	LED_1_4_Invert();
#endif
	//check recived data
	if(rx_buf[0]!=rx_buf[4] || rx_buf[1]!=rx_buf[5] ||rx_buf[2]!=rx_buf[6] || rx_buf[3]!=rx_buf[7])
	{
		goto Bind_rcv_error;
	}
	//gennerate first checksum
    for(n = 0; n < 8; n++)
        ckSum += rx_buf[n];
	if(rx_buf[8] != (ckSum >> 8) || rx_buf[9] !=(ckSum & 0xff))
	{
		goto Bind_rcv_error;
	}
    //gennerate second checksum 
	for(n = 8; n < 14; n++)
        ckSum += rx_buf[n];
	if(rx_buf[14] != (ckSum >> 8) || rx_buf[15] !=(ckSum & 0xff))
	{
		goto Bind_rcv_error;
	}
	if (rx_buf[10] != 0x01)
	{
		goto Bind_rcv_error;
	}
	num_channels=rx_buf[11];
	if (num_channels>PPM_PULSE_COUNT)
		num_channels=PPM_PULSE_COUNT;
	DSM_Is_DSMX=PROTOC_IS_DSMX(rx_buf[12]);
	DSM_Is_11ms=FALSE; //PROTOC_IS_DSM_11MS(rx_buf[12]);
	DSM_Is_11Bit=PROTOC_IS_DSM_11BIT(rx_buf[12]);
	State=DSM_STATE_BIND_RCV_WAIT; 	

	Bind_rcv_error:
	DSM_StartRcv();
}
//determin if we got 10 or 11 Bit data
// tryout
BYTE DSM_DeterminBitCount(void)
{
	//tryout
	BYTE min=0xff;
	BYTE max=0;
	BYTE chanal;
	BYTE n;
	//try 10 Bits
	for (n=0;n<7;n++)
	{
		chanal=(rx_data[n*2+2]>>2)&0xF;
		if (chanal && chanal<min)
			min=chanal;
		if(rx_data[n*2+2]!=0xFF  && chanal>max)
			max=chanal;
	}		
	if (min==1 &&  max && max <7)
		return 10;
	else 
		return 11;
}

#define PPM_OFFSET (PPM_OUT_CENTER_LEN-1024)
//Extract chanal data from serial data
BOOL DSM_process_Data(void)
{
static BYTE bits;	
	if (!bits) //check if we have 10 or 11 Bit data
		bits=DSM_DeterminBitCount();
	if (bits)
	{
	BYTE n;
	//static to safe stack space		
	static BYTE chanal; 
	static WORD value;	
		//loop thru the words 
		for (n=0;n<7;n++)
		{	//extract chanal number
			if (bits==10)
				chanal=(rx_data[n*2+2]>>2)&0xF;
			else 
				chanal=(rx_data[n*2+2]>>3)&0xF;
			//check if chanal numer is in range
			if (chanal<PPM_PULSE_COUNT && rx_data[n*2+2]!=0xFF)
				//extract chanal value
			{
				if (bits==10)
				{
					value=(((WORD)rx_data[n*2+2]<<8)+rx_data[n*2+3])&0x3FF;
				}
				else
				{
					value=(((WORD)rx_data[n*2+2]<<8)+rx_data[n*2+3])&0x7FF;
				}
				//PPM has resulution of 2000/1ms so 10 Bit datta (0 to 1024) needs to be multipleid by 2
				//best would be a linear scale like "Value=PPM_MIN + (value*(PPM_MAX-PPM_MIN))/(1<<Bits)" but that takes to mutch time.
				if (bits==10) 
					ppm_Data[chanal]=PPM_OFFSET+ value*2;
				else 
					ppm_Data[chanal]=PPM_OFFSET+ value;
				//limit to MIN / MAX
				if (PPM_OUT_MAX_LEN<ppm_Data[chanal])
					ppm_Data[chanal]=PPM_OUT_MAX_LEN;
				if (PPM_OUT_MIN_LEN>ppm_Data[chanal])
					ppm_Data[chanal]=PPM_OUT_MIN_LEN;
			}
		}
		return 1;
	}
	return 0;
}

void DSM_Save_Failsafe_Presets(void)
{
BYTE n;
#ifdef DEBUG
	LED_1_6_Invert();
	LED_1_6_Invert();
#endif
	for(n=0;n<PPM_PULSE_COUNT;n++)
	{	
		ppm_fs_Data[n]=ppm_Data[n];
	}
Preste_Failsafe=TRUE;
}

void DSM_Load_FS_Data(void)
{
BYTE n;
#ifdef DEBUG
	LED_1_6_Invert();
	LED_1_6_Invert();
#endif
	if (Preste_Failsafe)
	{
		for(n=0;n<PPM_PULSE_COUNT;n++)
		{	
			ppm_Data[n]=ppm_fs_Data[n];
		}
	}
	else 
	{
		ppm_Data[0]=PPM_OUT_MIN_LEN;
	}
}