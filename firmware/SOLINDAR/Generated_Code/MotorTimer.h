/* ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : MotorTimer.h
**     Project     : SOLINDAR
**     Processor   : MC9S08QE128CLK
**     Component   : TimerInt
**     Version     : Component 02.161, Driver 01.23, CPU db: 3.00.067
**     Compiler    : CodeWarrior HCS08 C Compiler
**     Date/Time   : 2019-11-16, 13:09, # CodeGen: 93
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
** @file MotorTimer.h
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

#ifndef __MotorTimer
#define __MotorTimer

/* MODULE MotorTimer. */

/*Include shared modules, which are used for whole project*/
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "PE_Timer.h"
#include "Cpu.h"

/* PUBLISHED CONSTANTS */
#define MotorTimer_SPT16_MIN 0xA4U     /* Lower bound of interval for method SetPeriodTicks16 */
#define MotorTimer_SPT16Min MotorTimer_SPT16_MIN /* Deprecated */
#define MotorTimer_SPT16_MAX 0x2666U   /* Upper bound of interval for method SetPeriodTicks16 */
#define MotorTimer_SPT16Max MotorTimer_SPT16_MAX /* Deprecated */
#define MotorTimer_SPT32_MIN 0xA4UL    /* Lower bound of interval for method SetPeriodTicks32 */
#define MotorTimer_SPT32Min MotorTimer_SPT32_MIN /* Deprecated */
#define MotorTimer_SPT32_MAX 0x2666UL  /* Upper bound of interval for method SetPeriodTicks32 */
#define MotorTimer_SPT32Max MotorTimer_SPT32_MAX /* Deprecated */
#define MotorTimer_SPUS_MIN 0x1388U    /* Lower bound of interval for method SetPeriodUS */
#define MotorTimer_SPUSMin MotorTimer_SPUS_MIN /* Deprecated */
#define MotorTimer_SPUS_MAX 0xFFFFU    /* Upper bound of interval for method SetPeriodUS */
#define MotorTimer_SPUSMax MotorTimer_SPUS_MAX /* Deprecated */
#define MotorTimer_SPMS_MIN 0x05U      /* Lower bound of interval for method SetPeriodMS */
#define MotorTimer_SPMSMin MotorTimer_SPMS_MIN /* Deprecated */
#define MotorTimer_SPMS_MAX 0x012BU    /* Upper bound of interval for method SetPeriodMS */
#define MotorTimer_SPMSMax MotorTimer_SPMS_MAX /* Deprecated */

byte MotorTimer_SetPeriodTicks16(word Ticks);
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

byte MotorTimer_SetPeriodTicks32(dword Ticks);
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

byte MotorTimer_SetPeriodUS(word Time);
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

byte MotorTimer_SetPeriodMS(word Time);
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

__interrupt void MotorTimer_Interrupt(void);
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

void MotorTimer_Init(void);
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


/* END MotorTimer. */

#endif /* ifndef __MotorTimer */
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
