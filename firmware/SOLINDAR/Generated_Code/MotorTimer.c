/* ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : MotorTimer.c
**     Project     : SOLINDAR
**     Processor   : MC9S08QE128CLK
**     Component   : TimerInt
**     Version     : Component 02.161, Driver 01.23, CPU db: 3.00.067
**     Compiler    : CodeWarrior HCS08 C Compiler
**     Date/Time   : 2019-10-28, 17:51, # CodeGen: 74
**     Abstract    :
**         This component "TimerInt" implements a periodic interrupt.
**         When the component and its events are enabled, the "OnInterrupt"
**         event is called periodically with the period that you specify.
**         TimerInt supports also changing the period in runtime.
**         The source of periodic interrupt can be timer compare or reload
**         register or timer-overflow interrupt (of free running counter).
**     Settings    :
**         Timer name                  : TPM1 (16-bit)
**         Compare name                : TPM10
**         Counter shared              : No
**
**         High speed mode
**             Prescaler               : divide-by-128
**             Clock                   : 196608 Hz
**           Initial period/frequency
**             Xtal ticks              : 1638
**             microseconds            : 49998
**             milliseconds            : 50
**             seconds (real)          : 0.049997965495
**             Hz                      : 20
**
**         Runtime setting             : period/frequency interval (continual setting)
**             ticks                   : 164 to 9830 ticks
**             microseconds            : 5000 to 299997 microseconds
**             milliseconds            : 5 to 299 milliseconds
**             seconds (real)          : 0.004999796549 to 0.299997965495 seconds
**             Hz                      : 4 to 200 Hz
**
**         Initialization:
**              Timer                  : Enabled
**              Events                 : Enabled
**
**         Timer registers
**              Counter                : TPM1CNT   [$0041]
**              Mode                   : TPM1SC    [$0040]
**              Run                    : TPM1SC    [$0040]
**              Prescaler              : TPM1SC    [$0040]
**
**         Compare registers
**              Compare                : TPM1C0V   [$0046]
**
**         Flip-flop registers
**              Mode                   : TPM1C0SC  [$0045]
**     Contents    :
**         SetPeriodTicks16 - byte MotorTimer_SetPeriodTicks16(word Ticks);
**         SetPeriodTicks32 - byte MotorTimer_SetPeriodTicks32(dword Ticks);
**         SetPeriodUS      - byte MotorTimer_SetPeriodUS(word Time);
**         SetPeriodMS      - byte MotorTimer_SetPeriodMS(word Time);
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
** @file MotorTimer.c
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
**  @addtogroup MotorTimer_module MotorTimer module documentation
**  @{
*/         

/* MODULE MotorTimer. */

#include "Events.h"
#include "PE_Error.h"
#include "MotorTimer.h"
#pragma MESSAGE DISABLE C2705          /* WARNING C2705: Possible loss of data */
#pragma MESSAGE DISABLE C5919          /* WARNING C5919: Conversion of floating to unsigned integral */
#pragma MESSAGE DISABLE C5703          /* WARNING C5703: Parameter X declared in function F but not referenced */
#pragma MESSAGE DISABLE C4002          /* Disable warning C4002 "Result not used" */

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
static void MotorTimer_SetCV(word Val);


/*** End of internal method prototypes ***/

/*
** ===================================================================
**     Method      :  MotorTimer_SetPeriodTicks16 (component TimerInt)
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
**                      (164 to 9830 ticks)
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_MATH - Overflow during evaluation
**                           ERR_RANGE - Parameter out of range
** ===================================================================
*/
byte MotorTimer_SetPeriodTicks16(word Ticks)
{
  dlong rtval;                         /* Result of two 32-bit numbers multiplication */
  word rtword;                         /* Result of 64-bit number division */

  if ((Ticks > 0x2666U) || (Ticks < 0xA4U)) { /* Is the given value out of range? */
    return ERR_RANGE;                  /* If yes then error */
  }
  PE_Timer_LngMul((dword)Ticks, 0x06000000LU, &rtval); /* Multiply given value and High speed CPU mode coefficient */
  if (PE_Timer_LngHi3(rtval[0], rtval[1], &rtword)) { /* Is the result greater or equal than 65536 ? */
    rtword = 0xFFFFU;                  /* If yes then use maximal possible value */
  }
  CmpHighVal = (word)(rtword - 1U);    /* Store result (compare register value for high speed CPU mode) to the variable CmpHighVal */
  MotorTimer_SetCV((word)CmpHighVal);  /* Store appropriate value to the compare register according to the selected high speed CPU mode */
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  MotorTimer_SetPeriodTicks32 (component TimerInt)
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
**                      (164 to 9830 ticks)
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_MATH - Overflow during evaluation
**                           ERR_RANGE - Parameter out of range
** ===================================================================
*/
byte MotorTimer_SetPeriodTicks32(dword Ticks)
{
  dlong rtval;                         /* Result of two 32-bit numbers multiplication */
  word rtword;                         /* Result of 64-bit number division */

  if ((Ticks > 0x2666UL) || (Ticks < 0xA4UL)) { /* Is the given value out of range? */
    return ERR_RANGE;                  /* Range error */
  }
  PE_Timer_LngMul(Ticks, 0x06000000LU, &rtval); /* Multiply given value and high speed CPU mode coefficient */
  if (PE_Timer_LngHi3(rtval[0], rtval[1], &rtword)){ /* Is the result greater or equal than 65536 ? */
    rtword = 0xFFFFU;                  /* If yes then use maximal possible value */
  }
  CmpHighVal = (word)(rtword - 1U);    /* Store result (compare register value for high speed CPU mode) to the variable CmpHighVal */
  MotorTimer_SetCV((word)CmpHighVal);  /* Store appropriate value to the compare register according to the selected high speed CPU mode */
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  MotorTimer_SetPeriodUS (component TimerInt)
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
**                      (5000 to 65535 microseconds)
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_MATH - Overflow during evaluation
**                           ERR_RANGE - Parameter out of range
** ===================================================================
*/
byte MotorTimer_SetPeriodUS(word Time)
{
  dlong rtval;                         /* Result of two 32-bit numbers multiplication */
  word rtword;                         /* Result of 64-bit number division */

  if (Time < 0x1388U) {                /* Is the given value out of range? */
    return ERR_RANGE;                  /* If yes then error */
  }
  PE_Timer_LngMul((dword)Time, 0x3254E6E2LU, &rtval); /* Multiply given value and high speed CPU mode coefficient */
  if (PE_Timer_LngHi4(rtval[0], rtval[1], &rtword)) { /* Is the result greater or equal than 65536 ? */
    rtword = 0xFFFFU;                  /* If yes then use maximal possible value */
  }
  CmpHighVal = (word)(rtword - 1U);    /* Store result (compare register value for high speed CPU mode) to the variable CmpHighVal */
  MotorTimer_SetCV((word)CmpHighVal);  /* Store appropriate value to the compare register according to the selected high speed CPU mode */
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  MotorTimer_SetPeriodMS (component TimerInt)
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
**                      (5 to 299 milliseconds)
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_MATH - Overflow during evaluation
**                           ERR_RANGE - Parameter out of range
** ===================================================================
*/
byte MotorTimer_SetPeriodMS(word Time)
{
  dlong rtval;                         /* Result of two 32-bit numbers multiplication */
  word rtword;                         /* Result of 64-bit number division */

  if ((Time > 0x012BU) || (Time < 0x05U)) { /* Is the given value out of range? */
    return ERR_RANGE;                  /* If yes then error */
  }
  PE_Timer_LngMul((dword)Time, 0xC49BA5E3LU, &rtval); /* Multiply given value and high speed CPU mode coefficient */
  if (PE_Timer_LngHi3(rtval[0], rtval[1], &rtword)) { /* Is the result greater or equal than 65536 ? */
    rtword = 0xFFFFU;                  /* If yes then use maximal possible value */
  }
  CmpHighVal = (word)(rtword - 1U);    /* Store result (compare register value for high speed CPU mode) to the variable CmpHighVal */
  MotorTimer_SetCV((word)CmpHighVal);  /* Store appropriate value to the compare register according to the selected high speed CPU mode */
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  MotorTimer_Init (component TimerInt)
**
**     Description :
**         Initializes the associated peripheral(s) and the component 
**         internal variables. The method is called automatically as a 
**         part of the application initialization code.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void MotorTimer_Init(void)
{
  CmpHighVal = 0x2665U;                /* Remember appropriate value of compare register for high speed CPU mode */
  /* TPM1SC: TOF=0,TOIE=0,CPWMS=0,CLKSB=0,CLKSA=0,PS2=0,PS1=0,PS0=0 */
  setReg8(TPM1SC, 0x00U);              /* Stop HW; disable overflow interrupt and set prescaler to 0 */ 
  /* TPM1C0SC: CH0F=0,CH0IE=1,MS0B=0,MS0A=1,ELS0B=0,ELS0A=0,??=0,??=0 */
  setReg8(TPM1C0SC, 0x50U);            /* Set output compare mode and enable compare interrupt */ 
  MotorTimer_SetCV(0x2665U);           /* Initialize appropriate value to the compare/modulo/reload register */
  MotorTimer_SetCV((word)CmpHighVal);  /* Store appropriate value to the compare/modulo/reload register according to High speed CPU mode */
  /* TPM1CNTH: BIT15=0,BIT14=0,BIT13=0,BIT12=0,BIT11=0,BIT10=0,BIT9=0,BIT8=0 */
  setReg8(TPM1CNTH, 0x00U);            /* Reset HW Counter */ 
  /* TPM1SC: TOF=0,TOIE=0,CPWMS=0,CLKSB=0,CLKSA=1,PS2=1,PS1=1,PS0=1 */
  setReg8(TPM1SC, 0x0FU);              /* Set prescaler and run counter */ 
}


/*
** ===================================================================
**     Method      :  MotorTimer_Interrupt (component TimerInt)
**
**     Description :
**         The method services the interrupt of the selected peripheral(s)
**         and eventually invokes the component event(s).
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
ISR(MotorTimer_Interrupt)
{
  /* TPM1C0SC: CH0F=0 */
  clrReg8Bits(TPM1C0SC, 0x80U);        /* Reset compare interrupt request flag */ 
  MotorTimer_OnInterrupt();            /* Invoke user event */
}


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
static void MotorTimer_SetCV(word Val)
{
  TPM1C0V = Val;                       /* Store given value to the compare register */
  TPM1MOD = Val;                       /* Store given value to the modulo register */
}


/* END MotorTimer. */

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