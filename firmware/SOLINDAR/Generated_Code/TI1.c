/* ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : TI1.c
**     Project     : SOLINDAR
**     Processor   : MC9S08QE128CLK
**     Component   : TimerInt
**     Version     : Component 02.161, Driver 01.23, CPU db: 3.00.067
**     Compiler    : CodeWarrior HCS08 C Compiler
**     Date/Time   : 2019-10-04, 20:37, # CodeGen: 19
**     Abstract    :
**         This component "TimerInt" implements a periodic interrupt.
**         When the component and its events are enabled, the "OnInterrupt"
**         event is called periodically with the period that you specify.
**         TimerInt supports also changing the period in runtime.
**         The source of periodic interrupt can be timer compare or reload
**         register or timer-overflow interrupt (of free running counter).
**     Settings    :
**         Timer name                  : RTC (8-bit)
**         Compare name                : RTCmod
**         Counter shared              : No
**
**         High speed mode
**             Prescaler               : divide-by-1
**             Clock                   : 4096 Hz
**           Initial period/frequency
**             Xtal ticks              : 784
**             microseconds            : 23926
**             milliseconds            : 24
**             seconds (real)          : 0.02392578125
**             Hz                      : 42
**
**         Runtime setting             : period/frequency interval (continual setting)
**             ticks                   : 160 to 1640 ticks
**             microseconds            : 4883 to 50048 microseconds
**             milliseconds            : 5 to 50 milliseconds
**             seconds (real)          : 0.0048828125 to 0.050048828125 seconds
**             Hz                      : 20 to 204 Hz
**
**         Initialization:
**              Timer                  : Enabled
**              Events                 : Enabled
**
**         Timer registers
**              Counter                : RTCCNT    [$1831]
**              Mode                   : RTCSC     [$1830]
**              Run                    : RTCSC     [$1830]
**              Prescaler              : RTCSC     [$1830]
**
**         Compare registers
**              Compare                : RTCMOD    [$1832]
**
**         Flip-flop registers
**     Contents    :
**         SetPeriodTicks16 - byte TI1_SetPeriodTicks16(word Ticks);
**         SetPeriodTicks32 - byte TI1_SetPeriodTicks32(dword Ticks);
**         SetPeriodUS      - byte TI1_SetPeriodUS(word Time);
**         SetPeriodMS      - byte TI1_SetPeriodMS(word Time);
**
**     Copyright : 1997 - 2014 Freescale Semiconductor, Inc. 
**     All Rights Reserved.
**     
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**     
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**     
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**     
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**     
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**     
**     http: www.freescale.com
**     mail: support@freescale.com
** ###################################################################*/
/*!
** @file TI1.c
** @version 01.23
** @brief
**         This component "TimerInt" implements a periodic interrupt.
**         When the component and its events are enabled, the "OnInterrupt"
**         event is called periodically with the period that you specify.
**         TimerInt supports also changing the period in runtime.
**         The source of periodic interrupt can be timer compare or reload
**         register or timer-overflow interrupt (of free running counter).
*/         
/*!
**  @addtogroup TI1_module TI1 module documentation
**  @{
*/         

/* MODULE TI1. */

#include "Events.h"
#include "PE_Error.h"
#include "TI1.h"
#pragma MESSAGE DISABLE C2705          /* WARNING C2705: Possible loss of data */
#pragma MESSAGE DISABLE C5919          /* WARNING C5919: Conversion of floating to unsigned integral */
#pragma MESSAGE DISABLE C5703          /* WARNING C5703: Parameter X declared in function F but not referenced */

static word CmpHighVal;                /* Compare register value for high speed CPU mode */
/*** Internal macros and method prototypes ***/

/*
** ===================================================================
**     Method      :  SetCV (component TimerInt)
**
**     Description :
**         The method computes and sets compare eventually modulo value 
**         for time measuring.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
#define TI1_SetCV(_Val) \
  (RTCMOD = (byte)(_Val))


/*** End of internal method prototypes ***/

/*
** ===================================================================
**     Method      :  TI1_SetPeriodTicks16 (component TimerInt)
**     Description :
**         This method sets the new period of the generated events.
**         The period is expressed in main oscillator (usualy External
**         osc., internal osc. if exits and external osc. is disabled)
**         ticks as a 16-bit unsigned integer number.
**         This method is available only if the runtime setting type
**         'from interval' is selected in the Timing dialog box in
**         the Runtime setting area.
**     Parameters  :
**         NAME            - DESCRIPTION
**         Ticks           - Period to set [in Xtal ticks]
**                      (160 to 1640 ticks)
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_MATH - Overflow during evaluation
**                           ERR_RANGE - Parameter out of range
** ===================================================================
*/
byte TI1_SetPeriodTicks16(word Ticks)
{
  dlong rtval;                         /* Result of two 32-bit numbers multiplication */
  word rtword;                         /* Result of 64-bit number division */

  if ((Ticks > 0x0668U) || (Ticks < 0xA0U)) { /* Is the given value out of range? */
    return ERR_RANGE;                  /* If yes then error */
  }
  PE_Timer_LngMul((dword)Ticks, 0x20000000LU, &rtval); /* Multiply given value and High speed CPU mode coefficient */
  if (PE_Timer_LngHi4(rtval[0], rtval[1], &rtword)) { /* Is the result greater or equal than 65536 ? */
    rtword = 0xFFFFU;                  /* If yes then use maximal possible value */
  }
  CmpHighVal = (word)(rtword - 1U);    /* Store result (compare register value for high speed CPU mode) to the variable CmpHighVal */
  TI1_SetCV((byte)CmpHighVal);         /* Store appropriate value to the compare register according to the selected high speed CPU mode */
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  TI1_SetPeriodTicks32 (component TimerInt)
**     Description :
**         This method sets the new period of the generated events.
**         The period is expressed in main oscillator (usualy External
**         osc., internal osc. if exits and external osc. is disabled)
**         ticks as a 32-bit unsigned integer number.
**         This method is available only if the runtime setting type
**         'from interval' is selected in the Timing dialog box in
**         the Runtime setting area.
**     Parameters  :
**         NAME            - DESCRIPTION
**         Ticks           - Period to set [in Xtal ticks]
**                      (160 to 1640 ticks)
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_MATH - Overflow during evaluation
**                           ERR_RANGE - Parameter out of range
** ===================================================================
*/
byte TI1_SetPeriodTicks32(dword Ticks)
{
  dlong rtval;                         /* Result of two 32-bit numbers multiplication */
  word rtword;                         /* Result of 64-bit number division */

  if ((Ticks > 0x0668UL) || (Ticks < 0xA0UL)) { /* Is the given value out of range? */
    return ERR_RANGE;                  /* Range error */
  }
  PE_Timer_LngMul(Ticks, 0x20000000LU, &rtval); /* Multiply given value and high speed CPU mode coefficient */
  if (PE_Timer_LngHi4(rtval[0], rtval[1], &rtword)){ /* Is the result greater or equal than 65536 ? */
    rtword = 0xFFFFU;                  /* If yes then use maximal possible value */
  }
  CmpHighVal = (word)(rtword - 1U);    /* Store result (compare register value for high speed CPU mode) to the variable CmpHighVal */
  TI1_SetCV((byte)CmpHighVal);         /* Store appropriate value to the compare register according to the selected high speed CPU mode */
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  TI1_SetPeriodUS (component TimerInt)
**     Description :
**         This method sets the new period of the generated events.
**         The period is expressed in microseconds as a 16-bit
**         unsigned integer number.
**         This method is available only if the runtime setting type
**         'from interval' is selected in the Timing dialog box in
**         the Runtime setting area.
**     Parameters  :
**         NAME            - DESCRIPTION
**         Time            - Period to set [in microseconds]
**                      (4883 to 50048 microseconds)
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_MATH - Overflow during evaluation
**                           ERR_RANGE - Parameter out of range
** ===================================================================
*/
byte TI1_SetPeriodUS(word Time)
{
  dlong rtval;                         /* Result of two 32-bit numbers multiplication */
  word rtword;                         /* Result of 64-bit number division */

  if ((Time > 0xC380U) || (Time < 0x1313U)) { /* Is the given value out of range? */
    return ERR_RANGE;                  /* If yes then error */
  }
  PE_Timer_LngMul((dword)Time, 0x010C6F7ALU, &rtval); /* Multiply given value and high speed CPU mode coefficient */
  if (PE_Timer_LngHi4(rtval[0], rtval[1], &rtword)) { /* Is the result greater or equal than 65536 ? */
    rtword = 0xFFFFU;                  /* If yes then use maximal possible value */
  }
  CmpHighVal = (word)(rtword - 1U);    /* Store result (compare register value for high speed CPU mode) to the variable CmpHighVal */
  TI1_SetCV((byte)CmpHighVal);         /* Store appropriate value to the compare register according to the selected high speed CPU mode */
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  TI1_SetPeriodMS (component TimerInt)
**     Description :
**         This method sets the new period of the generated events.
**         The period is expressed in miliseconds as a 16-bit
**         unsigned integer number.
**         This method is available only if the runtime setting type
**         'from interval' is selected in the Timing dialog box in
**         the Runtime setting area.
**     Parameters  :
**         NAME            - DESCRIPTION
**         Time            - Period to set [in miliseconds]
**                      (5 to 50 milliseconds)
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_MATH - Overflow during evaluation
**                           ERR_RANGE - Parameter out of range
** ===================================================================
*/
byte TI1_SetPeriodMS(word Time)
{
  dlong rtval;                         /* Result of two 32-bit numbers multiplication */
  word rtword;                         /* Result of 64-bit number division */

  if ((Time > 0x32U) || (Time < 0x05U)) { /* Is the given value out of range? */
    return ERR_RANGE;                  /* If yes then error */
  }
  PE_Timer_LngMul((dword)Time, 0x04189375LU, &rtval); /* Multiply given value and high speed CPU mode coefficient */
  if (PE_Timer_LngHi3(rtval[0], rtval[1], &rtword)) { /* Is the result greater or equal than 65536 ? */
    rtword = 0xFFFFU;                  /* If yes then use maximal possible value */
  }
  CmpHighVal = (word)(rtword - 1U);    /* Store result (compare register value for high speed CPU mode) to the variable CmpHighVal */
  TI1_SetCV((byte)CmpHighVal);         /* Store appropriate value to the compare register according to the selected high speed CPU mode */
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  TI1_Init (component TimerInt)
**
**     Description :
**         Initializes the associated peripheral(s) and the component 
**         internal variables. The method is called automatically as a 
**         part of the application initialization code.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void TI1_Init(void)
{
  CmpHighVal = 0x61U;                  /* Remember appropriate value of compare register for high speed CPU mode */
  /* RTCSC: RTIF=0,RTCLKS=0,RTIE=0,RTCPS=0 */
  setReg8(RTCSC, 0x00U);               /* Stop HW */ 
  TI1_SetCV(0x61U);                    /* Initialize appropriate value to the compare/modulo/reload register */
  TI1_SetCV((byte)CmpHighVal);         /* Store appropriate value to the compare/modulo/reload register according to High speed CPU mode */
  RTCMOD = RTCMOD;                     /* Reset HW counter */
  /* RTCSC: RTIF=1,RTCLKS=2,RTIE=1,RTCPS=1 */
  setReg8(RTCSC, 0xD1U);               /* Run RTC (select clock source, set frequency and enable interrupt) */ 
}


/*
** ===================================================================
**     Method      :  TI1_Interrupt (component TimerInt)
**
**     Description :
**         The method services the interrupt of the selected peripheral(s)
**         and eventually invokes the component event(s).
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
ISR(TI1_Interrupt)
{
  /* RTCSC: RTIF=1 */
  setReg8Bits(RTCSC, 0x80U);           /* Reset real-time counter request flag */ 
  TI1_OnInterrupt();                   /* Invoke user event */
}



/* END TI1. */

/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.09]
**     for the Freescale HCS08 series of microcontrollers.
**
** ###################################################################
*/
