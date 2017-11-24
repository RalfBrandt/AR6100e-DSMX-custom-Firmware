#ifndef CYRF6936_REG_H
#define CYRF6936_REG_H
// registers
enum {
	CYRF_CHANNEL            = 0x00,
	CYRF_TX_LENGTH          = 0x01,
	CYRF_TX_CTRL            = 0x02,
	CYRF_TX_CFG             = 0x03,
	CYRF_TX_IRQ_STATUS      = 0x04,
	CYRF_RX_CTRL            = 0x05,
	CYRF_RX_CFG             = 0x06,
	CYRF_RX_IRQ_STATUS      = 0x07,
	CYRF_RX_STATUS          = 0x08,
	CYRF_RX_COUNT           = 0x09,
	CYRF_RX_LENGTH          = 0x0A,
	CYRF_PWR_CTRL           = 0x0B,
	CYRF_XTAL_CTRL          = 0x0C,
	CYRF_IO_CFG             = 0x0D,
	CYRF_GPIO_CTRL          = 0x0E,
	CYRF_XACT_CFG           = 0x0F,
	CYRF_FRAMING_CFG        = 0x10,
	CYRF_DATA32_THOLD       = 0x11,
	CYRF_DATA64_THOLD       = 0x12,
	CYRF_RSSI               = 0x13,
	CYRF_EOP_CTRL           = 0x14,
	CYRF_CRC_SEED_LSB       = 0x15,
	CYRF_CRC_SEED_MSB       = 0x16,
	CYRF_TX_CRC_LSB         = 0x17,
	CYRF_TX_CRC_MSB         = 0x18,
	CYRF_RX_CRC_LSB         = 0x19,
	CYRF_RX_CRC_MSB         = 0x1A,
	CYRF_TX_OFFSET_LSB      = 0x1B,
	CYRF_TX_OFFSET_MSB      = 0x1C,
	CYRF_MODE_OVERRIDE      = 0x1D,
	CYRF_RX_OVERRIDE        = 0x1E,
	CYRF_TX_OVERRIDE        = 0x1F,
	CYRF_TX_BUFFER          = 0x20,
	CYRF_RX_BUFFER          = 0x21,
	CYRF_SOP_CODE           = 0x22,
	CYRF_DATA_CODE          = 0x23,
	CYRF_PREAMBLE           = 0x24,
	CYRF_MFG_ID             = 0x25,
	CYRF_XTAL_CFG           = 0x26,
	CYRF_CLK_OFFSET         = 0x27,
	CYRF_CLK_EN             = 0x28,
	CYRF_RX_ABORT           = 0x29,
	CYRF_AUTO_CAL_TIME      = 0x32,
	CYRF_AUTO_CAL_OFFSET    = 0x35,
	CYRF_ANALOG_CTRL        = 0x39,
};

//TX_CTRL_ADR
#define TXE_IRQEN 		(1<<0) 	// Transmit Error Interrupt Enable
#define TXC_IRQEN 		(1<<1)	// Transmission Complete Interrupt Enable
#define TXBERR_IRQEN	(1<<2)	// Buffer Error Interrupt Enable
#define TXB0_IRQEN		(1<<3)	// Buffer Empty Interrupt Enable
#define TXB8_IRQEN		(1<<4)	// Buffer Half Empty Interrupt Enable
#define TXB15_IRQEN		(1<<5)	// Buffer Not Full Interrupt Enable
#define TX_CLR			(1<<6)	// Clear TX Buffer
#define TX_GO			(1<<7)	// Start Transmission

//TX_CFG_ADR
enum { // PA Setting
	TX_PA_M35DBM	=	0,	//-35 dBm
	TX_PA_M30DBM	=	1,	//-30 dBm
	TX_PA_M24DBM	=	2,	//-24 dBm
	TX_PA_M18DBM	=	3,	//-18 dBm
	TX_PA_M13DBM	=	4,	//-13 dBm
	TX_PA_M5DBM		=	5,	//-5 dBm
	TX_PA_0DBM		=	6,	//0 dBm
	TX_PA_P4DBM		=	7,	//+7 dBm
};

enum { //Data Mode
	TX_DM_GFSK	=	0, 	// GFSK Mode
	TX_DM_8DR	=	1,	// 8DR Mode
	TX_DM_DDR	=	2,	// DDR Mode
	TX_DM_SDR	=	3,	// SDR Mode	
};
#define TX_DM(x) 	(x<<3) 
#define TX_DC_LEN	(1<<5)	//Data Code Length


//TX_IRQ_STATUS_ADR
#define TXE_IRQ		(1<<0)	// Transmit Error Interrupt Status
#define TXC_IRQ		(1<<1)	// Transmission Complete Interrupt Status
#define TXBERR_IRQ	(1<<2)	// Buffer Error Interrupt Status
#define TXB0_IRQ	(1<<3)	// Buffer Empty Interrupt Status
#define TXB8_IRQ	(1<<4)	// Buffer Half Empty Interrupt Status
#define TXB15_IRQ	(1<<5)	// Buffer Not Full Interrupt Status
#define LV_IRQ		(1<<6)	//  Low Voltage Interrupt Status
#define OS_IRQ		(1<<7)	//  Oscillator Stable IRQ Status

//RX_CTRL_ADR
#define RXE_IRQEN	(1<<0)	// Receive Error Interrupt Enable
#define RXC_IRQEN	(1<<1)	// Packet Reception Complete Interrupt Enable
#define RXBERR_IRQEN (1<<2)	// Buffer Error Interrupt Enable
#define RXB1_IRQEN	(1<<3)	// Buffer Not Empty Interrupt Enable
#define RXB8_IRQEN	(1<<4)	// Buffer Half Empty Interrupt Enable
#define RXB16_IRQEN	(1<<5)	// Buffer Full Interrupt Enable
#define RX_GO		(1<<7)	// Start Receive

//RX_CFG_ADR
#define VLD_EN			(1<<0)	// Valid Flag Enable
#define RXOW EN			(1<<1)	// Overwrite Enable
#define FAST_TURN_EN	(1<<3)	// Fast Turn Mode Enable
#define HILO 			(1<<4)	// HILO
#define ATT				(1<<5)	// Receive Attenuator Enable
#define RX_LNA			(1<<6)	// Low Noise Amplifier (LNA) Manual Control
#define AGC_EN			(1<<7)	// Automatic Gain Control (AGC) Enable

//RX_IRQ_STATUS_ADR
#define RXE_IRQ		(1<<0)	// Receive Error Interrupt Status
#define RXC_IRQ		(1<<1)	// Packet Receive Complete Interrupt Status
#define RXBERR_IRQ	(1<<2)	// Receive Buffer Error Interrupt Status
#define RXB1_IRQ	(1<<3)	// Receive Buffer Not Empty Interrupt Status
#define	RXB8_IRQ	(1<<4)	// Receive Buffer Half Full Interrupt Status
#define RXB16_IRQ	(1<<5)	// Receive Buffer Full Interrupt Status
#define SOPDET_IRQ	(1<<6)	// Start of packet detect
#define RXOW_IRQ	(1<<7)	// Receive Overwrite Interrupt Status



//RX_STATUS_ADR
enum { //Data Mode
	RX_DM_GFSK	=	0,	// 1 Mbps GFSK
	RX_DM_8DR	=	1,	// 8DR
	RX_DM_DDR	=	2,	// DDR
	RX_DM_NV	=	3,	// Not Valid
};

//CYRF_RX_STATUS
#define BAD_CRC		(1<<3)	//  Bad CRC16
#define CRC0		(1<<4)	// Zero-seed CRC16
#define EOP_ERR		(1<<5)	// Unexpected EOP
#define PKT_ERR		(1<<6)	// Receive Packet Type Error
#define RX_ACK		(1<<7)	// RX Packet Type  This bit is set when the received packet is an ACK packet


//PWR_CTRL_ADR
enum {
	PMU_27=0,	// 2.7V
	PMU_26=1,	// 2.6V
	PMU_25=2,	// 2.5V	
	PMU_24=3,	// 2.4V	
};

enum{ //Low Voltage Interrupt Threshold
	LV_TH_PMU	=	0,	// PMU OUTV voltage
	LV_TH_22	=	1,	// 2.2V
	LV_TH_20	=	2,	// 2.0V
	LV_TH_18	=	3,	// 1.8V
};

#define PMU_MODE_FORCE	(1<<5)	// PMU Mode Force
#define LVIRQ_EN		(1<<6)	// Low Voltage Interrupt Enable
#define PMU_EN			(1<<7)	// Power Management Unit (PMU) Enable

//XTAL_CTRL_ADR
enum{ // XOUT Frequency
	XOUT_FREQ12		= 	0,	// 12 MHz
	XOUT_FREQ6		=	1,	// 6 MHz
	XOUT_FREQ3		=	2,	// 3 MHz
	XOUT_FREQ15		=	3,	// 1.5 MHz		
	XOUT_FREQ075	=	4,	// 0.75 MHz
};

//IO_CFG_ADR
#define IO_CFG_IRQ_GPIO	(1<<0)	// IRQ Pin Function
#define IO_CFG_SPI_3PIN	(1<<1)	// SPI Mode  3-Wire Mode
#define IO_CFG_PACTL_GPIO	(1<<2)	// PACTL Pin Function
#define IO_CFG_PACTL_OD		(1<<3)	// PACTL Pin Drive Strength
#define IO_CFG_XOUT_OD		(1<<4)	// XOUT Pin Drive Strength
#define IO_CFG_MISO_OD		(1<<5)	// MISO Pin Drive Strength
#define IO_CFG_IRQ_POL		(1<<6)	// IRQ Polarity
#define IO_CFG_IRQ_OD		(1<<7)	// IRQ Pin Drive Strength


//GPIO_CTRL_ADR
#define IRQ_IP		(1<<0) // IRQ Input
#define PACTL_IP	(1<<1) // PACTL Input
#define MISO_IP		(1<<2) // MISO Input
#define XOUT_IP		(1<<3) // XOUT Input
#define IRQ_OP		(1<<4) // IRQ Output
#define PACTL_OP	(1<<5) // PACTL Output
#define MISO_OP		(1<<6) // MISO Output
#define XOUT_OP		(1<<7) // XOUT Output

// CYRF_XACT_CFG
enum {
	CYRF_MODE_SLEEP     = 0x0,
	CYRF_MODE_IDLE      = 0x1,
	CYRF_MODE_SYNTH_TX  = 0x2,
	CYRF_MODE_SYNTH_RX  = 0x3,
	CYRF_MODE_RX        = 0x4,
};

#define CYRF_XACT_END_STATE(x) (x<<2)

#define CYRF_FRC_END   	(1<<5)
#define CYRF_ACK_EN    	(1<<7)
#define CYRF_ACK_TO_04x  0x0
#define CYRF_ACK_TO_08x  0x1
#define CYRF_ACK_TO_12x  0x2
#define CYRF_ACK_TO_15x  0x3

//FRAMING_CFG_ADR
#define LEN_EN		(1<<5) // Packet Length Enable
#define SOP_LEN		(1<<6) // SOP PN Code Length
#define SOP_EN 		(1<<7) // SOP Enable

//RSSI_ADR
#define RSSI_LNA 	(1<<5) // LNA State
#define RSSI_SOP 	(1<<7) // SOP RSSI Reading

//EOP_CTRL_ADR
#define EOP_HEN		(1<<7) //EOP Hint Enable


//MODE_OVERRIDE_ADR
#define RST			(1<<0) // Reset. Setting 
#define FRC_AWAKE 	((1<<3)|(1<<4)) //Force Awake
#define FRC_SEN		(1<<5) // Manually Initiate Synthesizer

//RX_OVERRIDE_ADR
#define ACE			(1<<1) // Accept Bad CRC16
#define DIS_RXCRC	(1<<2) // The RX CRC16 checker is disabled
#define DIS_CRC0 	(1<<3) // Reject packets with a zero-seed CRC16
#define FRC_RXDR	(1<<4) // Force Receive Data Rate
#define MAN_RXACK	(1<<5) // Force Expected Packet Type
#define RXTX_DLY	(1<<6) // the transmission of the ACK packet is delayed by 20 μs
#define ACK_RX		(1<<7) //When this bit is set, the device uses the transmit synthesizer frequency rather than the receive synthesizer frequency 


//TX_OVERRIDE_ADR
#define TX_INV		(1<<0) // TX Data Invert
#define DIS_TXCRC	(1<<2) // Disable Transmit CRC16
#define OVRD_ACK	(1<<3) // ACK Override
#define MAN_TXACK	(1<<4) // Transmit ACK Packet
#define FRC_PRE		(1<<6) // Force Preamble
#define ACK_TX		(1<<7) // When this bit is set, the device uses the receive synthesizer frequency rather than the transmit synthesizer frequency 

//XTAL_CFG_ADR
#define START_DLY	(1<<3) //Crystal Startup Delay


//CLK_OVERRIDE_ADR
#define CLK_OV_RXF		(1<<1) // Force Receive Clock Enable.
//CLK_EN_ADR
#define CLK_EN_RXF		(1<<1) // Force Receive Clock Enable.

//RX_ABORT_ADR
#define ABORT_EN	(1<<5) // Receive Abort Enable

//ANALOG_CTRL_ADR
#define ALL_SLOW	(1<<0) // All Slow
#define RX_INV		(1<<1) // Receive Invert


#endif //CYRF6936_REG_H