//*****************************************************************************
//*****************************************************************************
//  FILENAME: delay.h
//
//  DESCRIPTION: C Language interface file for delay functions
//-----------------------------------------------------------------------------
//  Copyright (c) Cypress MicroSystems 2000-2006. All Rights Reserved.
//*****************************************************************************
//*****************************************************************************

// Create pragmas to support proper argument and return value passing
#pragma fastcall16  Delay50uTimes
#pragma fastcall16  Delay50u
#pragma fastcall16  Delay10msTimes
//-------------------------------------------------
// Prototypes of the delay API.
//-------------------------------------------------
void Delay50u(void);
void Delay50uTimes(BYTE Multiple);
void Delay10msTimes(BYTE TenMstimes);