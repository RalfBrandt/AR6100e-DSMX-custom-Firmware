;;*****************************************************************************
;;*****************************************************************************
;;  FILENAME: delay.asm
;;
;;  DESCRIPTION: Delay functions implementation file
;;
;;-----------------------------------------------------------------------------
;;  Copyright (c) Cypress MicroSystems 2002-2006. All Rights Reserved.
;;*****************************************************************************
;;*****************************************************************************

;-----------------------------------------------------------------------------
;  Include Files
;-----------------------------------------------------------------------------
include "m8c.inc"
include "memory.inc"

;-----------------------------------------------------------------------------
;  Global Symbols
;-----------------------------------------------------------------------------
export  Delay50uTimes
export _Delay50uTimes

export  Delay50u
export _Delay50u

area text(rom)


.SECTION
;-----------------------------------------------------------------------------
;  FUNCTION NAME: Delay50uTimes
;
;  DESCRIPTION:
;     Delay increments of 50uSeconds
;
;-----------------------------------------------------------------------------
;
;  ARGUMENTS:
;     A contains the delay multiplier
;
;  RETURNS:
;
;  SIDE EFFECTS:
;    The A and X registers may be modified by this or future implementations
;    of this function.  The same is true for all RAM page pointer registers in
;    the Large Memory Model.  When necessary, it is the calling function's
;    responsibility to perserve their values across calls to fastcall16 
;    functions.
;
;

 Delay50uTimes:
_Delay50uTimes:
    RAM_PROLOGUE RAM_USE_CLASS_1

    call  Delay50u
	dec A
    jnz   Delay50uTimes

	
    RAM_EPILOGUE RAM_USE_CLASS_1
    ret

.ENDSECTION

;-----------------------------------------------------------------------------
;  FUNCTION NAME: Delay50u
;
;  DESCRIPTION:
;     Delay 50uSec for any clock frequency from 1.5MHz to 24MHz
;     Slower clock frequencies the delay will be;
;           1.5
;        -------------- * 50uSec
;        clock_freq(MHz)
;
;
;-----------------------------------------------------------------------------
;
;  ARGUMENTS: none
;
;  RETURNS: none
;
;  SIDE EFFECTS:
;    The A and X registers may be modified by this or future implementations
;    of this function.  The same is true for all RAM page pointer registers in
;    the Large Memory Model.  When necessary, it is the calling function's
;    responsibility to perserve their values across calls to fastcall16 
;    functions.
;
;  THEORY of OPERATION or PROCEDURE:
;
.LITERAL
 Delay50u_Table::
     DB    08h,  19h,   3Ah,   7Ch,   01h,    01h,    01h,   01h
;         3MHz, 6MHz, 12MHz, 24MHz, 1.5MHz, 750kHz, 188kHz, 94kHz
.ENDLITERAL
.SECTION

  Delay50u:
 _Delay50u:                      ; [11]  Call
    RAM_PROLOGUE RAM_USE_CLASS_1
    push  A
    M8C_SetBank1                       ; [4]
    mov   A, reg[OSC_CR0]              ; [6] Get delay value
    M8C_SetBank0                       ; [4]
    and   A,07h                        ; [4] Mask off only the clock bits
    cmp   A,05h
    jnc   Delay50u_End
    index Delay50u_Table               ; [13] Get delay value
Delay50u_Loop:                         ;
    dec   A                            ; [4]
    jnz   Delay50u_Loop                ; [5]
Delay50u_End:
    pop   A
    RAM_EPILOGUE RAM_USE_CLASS_1
    ret
.ENDSECTION
