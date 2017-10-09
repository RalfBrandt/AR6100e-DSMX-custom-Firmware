Project:      output/DSM_Reciver_PPM_OUTV3
Build Number: 0
Date:         Mon Oct 09 23:04:53 2017
Compiler:     ICCM8C
Version:      7.05.00


Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                             lit   0170   01A5 =    421. bytes (rel,con,rom,lit)

       Addr  Global Symbol
      -----  --------------------------------
       0170  dsm.c:pn_bind
       0178  dsm.c:pncodes
       02E0  dsm.c:init_vals
       0300  dsm.c:rcv_vals
       0308  dsm.c:preamble
       030B  dsm.c:bind_vals
       0315  __lit_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                           idata   0315   0009 =      9. bytes (rel,con,rom,lit)

       Addr  Global Symbol
      -----  --------------------------------
       0315  __idata_start
       031E  __idata_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                        func_lit   031E   000E =     14. bytes (rel,con,rom,proclab)

       Addr  Global Symbol
      -----  --------------------------------
       031E  __func_lit_start
       032C  __func_lit_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                     psoc_config   032C   014F =    335. bytes (rel,con,rom,code)

       Addr  Global Symbol
      -----  --------------------------------
       032C  LoadConfigTBL_dsm_reciver
       0468  LoadConfigInit
       0468  _LoadConfigInit
       0475  _LoadConfig_dsm_reciver
       0475  LoadConfig_dsm_reciver
       047B  __psoc_config_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                     UserModules   047B   052C =   1324. bytes (rel,con,rom,code)

       Addr  Global Symbol
      -----  --------------------------------
       047B  _Timer8_1_ISR
       047F  Timer8_1_EnableInt
       047F  _Timer8_1_EnableInt
       0483  Timer8_1_Start
       0483  _Timer8_1_DisableInt
       0483  _Timer8_1_Start
       0487  Timer8_1_Stop
       0487  _Timer8_1_Stop
       048B  _Timer8_1_WritePeriod
       048B  Timer8_1_WritePeriod
       048E  bTimer8_1_CaptureCounter
       048E  SPIM_1_Start
       048E  _bTimer8_1_ReadCompareValue
       048E  _Timer8_1_bReadCompareValue
       048E  _bTimer8_1_ReadCounter
       048E  bTimer8_1_ReadTimerSaveCV
       048E  _Timer8_1_bReadTimer
       048E  bTimer8_1_ReadCounter
       048E  _SPIM_1_EnableInt
       048E  _bTimer8_1_ReadTimer
       048E  _SPIM_1_Start
       048E  bTimer8_1_ReadCompareValue
       048E  bTimer8_1_ReadTimer
       048E  _bTimer8_1_ReadTimerSaveCV
       048E  _SPIM_1_DisableInt
       048E  _Timer8_1_bReadTimerSaveCV
       048E  _Timer8_1_WriteCompareValue
       048E  _bTimer8_1_CaptureCounter
       0493  SPIM_1_SendTxData
       0493  _SPIM_1_SendTxData
       0493  _SPIM_1_Stop
       0496  SPIM_1_bReadRxData
       0496  bSPIM_1_ReadRxData
       0496  _bSPIM_1_ReadRxData
       0496  _SPIM_1_bReadRxData
       0499  _bSPIM_1_ReadStatus
       0499  _SPIM_1_bReadStatus
       0499  SPIM_1_bReadStatus
       0499  bSPIM_1_ReadStatus
       049C  _SleepTimer_1_ISR
       04B4  SleepTimer_1_EnableInt
       04B4  _SleepTimer_1_EnableInt
       04B8  _SleepTimer_1_DisableInt
       04B8  _SleepTimer_1_Start
       04B8  SleepTimer_1_Start
       04C5  _SleepTimer_1_TickWait
       04C5  _SleepTimer_1_Stop
       04C5  SleepTimer_1_TickWait
       04C5  _SleepTimer_1_SetInterval
       04D4  _SleepTimer_1_SyncWait
       04D4  SleepTimer_1_iGetTickCntr
       04D4  _SleepTimer_1_bGetTickCntr
       04D4  _SleepTimer_1_SetTimer
       04D4  _SleepTimer_1_bGetTimer
       04D4  _SleepTimer_1_iGetTickCntr
       04DF  _RST_On
       04DF  RST_On
       04E3  RST_Stop
       04E3  _RST_Start
       04E3  RST_Start
       04E3  _RST_Off
       04E3  RST_Off
       04E3  _RST_Stop
       04E5  _RST_Switch
       04E5  RST_Switch
       04F6  RST_GetState
       04F6  _PWM16_1_ISR
       04F6  RST_Invert
       04FA  _PWM16_1_EnableInt
       04FA  PWM16_1_EnableInt
       04FE  _PWM16_1_Start
       04FE  _PWM16_1_DisableInt
       04FE  PWM16_1_Start
       0502  _PWM16_1_Stop
       0502  PWM16_1_Stop
       0506  _PWM16_1_WritePeriod
       0506  PWM16_1_WritePeriod
       050C  PWM16_1_WritePulseWidth
       050C  _PWM16_1_WritePulseWidth
       0512  _LED_1_7_Start
       0512  _LED_1_7_Off
       0512  _LED_1_7_Stop
       0512  LED_1_7_Stop
       0512  LED_1_7_Switch
       0512  wPWM16_1_ReadPulseWidth
       0512  _wPWM16_1_ReadPulseWidth
       0512  wPWM16_1_ReadCounter
       0512  _PWM16_1_wReadPulseWidth
       0512  _wPWM16_1_ReadCounter
       0512  _LED_1_7_Switch
       0512  _PWM16_1_wReadCounter
       0512  LED_1_7_On
       0512  LED_1_7_Start
       0512  LED_1_7_Off
       0523  LED_1_7_GetState
       0523  LED_1_6_Start
       0523  _LED_1_6_Off
       0523  _LED_1_6_Switch
       0523  LED_1_6_Off
       0523  _LED_1_6_Start
       0523  LED_1_6_Switch
       0523  LED_1_7_Invert
       0523  _LED_1_6_Stop
       0523  LED_1_6_On
       0523  LED_1_6_Stop
       0534  LED_1_5_On
       0534  LED_1_5_Stop
       0534  _LED_1_5_Stop
       0534  LED_1_5_Start
       0534  LED_1_6_GetState
       0534  LED_1_5_Off
       0534  _LED_1_5_Switch
       0534  _LED_1_5_Start
       0534  LED_1_5_Switch
       0534  LED_1_6_Invert
       0534  _LED_1_5_Off
       0545  LED_1_4_Off
       0545  LED_1_4_On
       0545  LED_1_4_Stop
       0545  _LED_1_4_Switch
       0545  _LED_1_4_Start
       0545  _LED_1_4_Stop
       0545  LED_1_4_Switch
       0545  LED_1_5_Invert
       0545  LED_1_5_GetState
       0545  _LED_1_4_Off
       0545  LED_1_4_Start
       0556  _LED_1_1_Switch
       0556  LED_1_4_Invert
       0556  LED_1_1_On
       0556  LED_1_1_Switch
       0556  LED_1_4_GetState
       0556  _LED_1_1_Off
       0556  _LED_1_1_Start
       0556  _LED_1_1_Stop
       0556  LED_1_1_Stop
       0556  LED_1_1_Start
       0556  LED_1_1_Off
       0567  LED_1_0_Off
       0567  _LED_1_0_Off
       0567  LED_1_0_Stop
       0567  _LED_1_0_Stop
       0567  LED_1_1_GetState
       0567  LED_1_0_On
       0567  _LED_1_0_Start
       0567  LED_1_0_Switch
       0567  LED_1_0_Start
       0567  LED_1_1_Invert
       0567  _LED_1_0_Switch
       0578  LED_1_On
       0578  LED_1_Start
       0578  LED_1_Stop
       0578  LED_1_0_Invert
       0578  _LED_1_Start
       0578  LED_1_Off
       0578  _LED_1_Off
       0578  _LED_1_Stop
       0578  LED_1_0_GetState
       057A  LED_1_Switch
       057A  _LED_1_Switch
       058B  _E2PROM_1_Start
       058B  LED_1_Invert
       058B  E2PROM_1_Start
       058B  LED_1_GetState
       058C  _E2PROM_1_Stop
       058C  _E2PROM_1_bE2Write
       058C  E2PROM_1_bE2Write
       0598  _E2PROM_1_E2Read
       0598  E2PROM_1_E2Read
       05A3  CS_PIN_On
       05A3  _CS_PIN_On
       05A7  _CS_PIN_Start
       05A7  _CS_PIN_Off
       05A7  CS_PIN_Off
       05A7  CS_PIN_Start
       05A7  _CS_PIN_Stop
       05A7  CS_PIN_Stop
       05A9  CS_PIN_Switch
       05A9  _CS_PIN_Switch
       05BA  bE2Write
       05BA  CS_PIN_Invert
       05BA  _bE2Write
       05BA  CS_PIN_GetState
       0750  _E2Read
       0750  E2Read
       07B6  bFlashWriteBlock
       07B6  _bFlashWriteBlock
       084A  _FlashBlockLocal1
       0887  _FlashBlockLocal2
       08D7  _FlashBlockLocal3
       09A7  __UserModules_end
       09A7  _FlashReadBlock

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            text   09A7   1616 =   5654. bytes (rel,con,rom,code)

       Addr  Global Symbol
      -----  --------------------------------
       09A7  __text_start
       09A7  _SaveConfig
       0A06  _ReadConfig
       0A53  _GPIO_ISR
       0A68  _CYRF_Init
       0AA6  _CYRF_WriteRegister
       0ABF  _CYRF_WriteRegisterMulti
       0B24  _CYRF_WriteRegisterMultiD
       0B7F  _CYRF_WriteRegisterInc
       0B95  _CYRF_ReadRegister
       0BAD  _CYRF_ReadRegisterMulti
       0C30  _CYRF_ReadRegisterInc
       0C46  _CYRF_GetMfgData
       0C6C  _CYRF_SetCRCSeed
       0C82  Delay50uTimes
       0C82  _Delay50uTimes
       0C88  Delay50u_Table
       0C90  _Delay50u
       0C90  Delay50u
       0CA4  _SetChannel
       0DDB  _SetCH_INC
       0E2E  _DSM_Load_Config
       0E6B  _DSM_ClearRxError
       0EBD  _SYNC_AB_TimeOut_cb
       0EEC  _SYNC_X_TimeOut_cb
       0F23  _DSM_Set_SyncX_State
       0F4D  _Rcv_X_TimeOut_cb
       0F9C  _DSM_initialize_Recive
       1042  _Process_Rvc_Irq
       10F0  _ProcessRxIrqStatus
       1149  _ProcessNewData
       114E  _DSM_Cyclic
       1250  _calc_dsmx_channel
       14AB  _DSM_Init
       14E7  _DSM_initialize_bind
       152F  _DSM_Build_Ack_package
       15E0  _DSM_StartRcv
       15F2  _DSM_StartBindAck
       1613  _Bind_xfer_cb
       164D  _DSM_initialize_bind_ack
       167E  _Bind_TimeOut_cb
       16A8  _Process_BindRcvIrq
       17E1  _DSM_DeterminBitCount
       1845  _DSM_process_Data
       1957  _DSM_Save_Failsafe_Presets
       198D  _DSM_Load_FS_Data
       19CD  _LVD_ISR
       19D9  _main
       1BA9  _ppm_Init
       1BFC  _Switch_LED
       1C7D  _PPM_Start_One_PPM_Train
       1C9D  _PWM16_1_CMP_ISR
       1D62  _Timer_Wait_ms
       1D71  _Timer_init
       1D83  _Timer_SetCallback
       1D8F  _Timer8_1_Interrupt
       1E16  PSoC_GPIO_ISR
       1F7E  __plcall
       1F8B  <created procedures>
       1FBD  __text_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            data   0000   0009 =      9. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0000  __data_start
       0000  dsm.c:tx_cmd
       0002  dsm.c:cnt
       0004  _LV_Detect
       0005  _ppm_Nr
       0006  _ppm_Run
       0007  _timer_cb
       0009  __data_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
               virtual_registers   0009   000F =     15. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0009  __rZ
       000A  __rY
       000B  __rX
       000C  __r11
       000D  __r10
       000E  __r9
       000F  __r8
       0010  __r7
       0011  __r6
       0012  __r5
       0013  __r4
       0014  __r3
       0015  __r2
       0016  __r1
       0017  __r0
       0018  __virtual_registers_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                    InterruptRAM   0018   0008 =      8. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0018  SleepTimer_1_fTick
       0018  _SleepTimer_1_fTick
       0019  SleepTimer_1_bTimerValue
       0019  _SleepTimer_1_bTimerValue
       001A  SleepTimer_1_bCountDown
       001A  _SleepTimer_1_bCountDown
       001B  SleepTimer_1_TickCount
       001B  _SleepTimer_1_TickCount
       001D  _NO_SHADOW
       001D  _Port_0_Data_SHADE
       001D  Port_0_Data_SHADE
       001D  NO_SHADOW
       001E  _Port_1_Data_SHADE
       001E  Port_1_Data_SHADE
       001F  Port_3_Data_SHADE
       001F  _Port_3_Data_SHADE
       0020  __InterruptRAM_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                             bss   0020   0075 =    117. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0020  _mem
       0020  __bss_start
       0040  _CY_irq
       0045  _bind_channal
       0046  _Bind_cnt
       0047  _New_RCV_Data
       0048  _lost_cnt
       0049  _num_channels
       004A  _data_col
       004B  _sop_col
       004C  _Ch_A
       004D  _chidx
       004E  _channels
       0065  _ppm_Data
       0075  _config
       008D  _Rcv_Timeout
       008E  _new_data
       008F  _State
       0090  _DSM_Perriode
       0092  _TC_IRQ
       0093  _cnt_last
       0095  __bss_end
       0095  __ramareas_end

Area                               Start  End    Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                             TOP   0000   00F5 =    245. bytes (abs,ovr,rom,code)

       Addr  Global Symbol
      -----  --------------------------------
       0068  __Start
       00F2  _bGetPowerSetting
       00F2  bGetPowerSetting

Area                               Start  End    Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                   E2PROM_1_AREA   1FC0   2000 =     64. bytes (abs,ovr,rom,code)

       Addr  Global Symbol
      -----  --------------------------------
       1FC0  _E2PROM_1_RESERVED
       1FC0  E2PROM_1_RESERVED

Area                               Start  End    Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                      SSCParmBlk   0000   0100 =    256. bytes (abs,ovr,ram)

Files Linked      [ module(s) ]

./obj/boot.o	[ boot.asm ]
obj/config.o	[ config.c ]
obj/cyrf6936.o	[ cyrf6936.c ]
obj/delay.o	[ delay.asm ]
obj/dsm.o	[ dsm.c ]
obj/main.o	[ main.c ]
obj/ppm.o	[ ppm.c ]
obj/timer.o	[ timer.c ]
<library>	[ timer8_1int.asm, timer8_1.asm, spim_1.asm, sleeptimer_1int.asm, sleeptimer_1.asm, rst.asm, pwm16_1int.asm ]
[ pwm16_1.asm, psocgpioint.asm, psocconfigtbl.asm, psocconfig.asm, led_1_7.asm, led_1_6.asm, led_1_5.asm ]
[ led_1_4.asm, led_1_1.asm, led_1_0.asm, led_1.asm, e2prom_1.asm, cs_pin.asm, E2PROMLIB.asm, flashblock.asm ]
[ rZ.asm, rY.asm, rX.asm, r11.asm, r10.asm, r9.asm, r8.asm, r7.asm, r6.asm, r5.asm, r4.asm, r3.asm, r2.asm ]
[ r1.asm, r0.asm, divmod_16x16_16_util.asm, divmodu_32x32_32_util.asm, divmodu_8x8_8_util.asm ]
[ i_div16_block_util.asm, i_div32_block_util.asm, i_div8_block_util.asm, mul16_util.asm, mul32_util.asm ]
[ plcall.s ]

Area Definitions

-blit:0x170.0x1fff
-bdata:0.0xff
-bSSCParmBlk:0xf7.0xff
-rwh:SSCParmBlk:0xf7.0xff

