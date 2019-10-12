/* ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : TI1.h
**     Project     : SOLINDAR
**     Processor   : MC9S08QE128CLK
**     Component   : TimerInt
**     Version     : Component 02.161, Driver 01.23, CPU db: 3.00.067
**     Compiler    : CodeWarrior HCS08 C Compiler
**     Date/Time   : 2019-10-11, 21:00, # CodeGen: 41
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
**             Clock                   : 2048 Hz
**           Initial period/frequency
**             Xtal ticks              : 784
**             microseconds            : 23926
**             milliseconds            : 24
**             seconds (real)          : 0.02392578125
**             Hz                      : 42
**
**         Runtime setting             : period/frequency interval (continual setting)
**             ticks                   : 320 to 3280 ticks
**             microseconds            : 9766 to 100097 microseconds
**             milliseconds            : 10 to 100 milliseconds
**             seconds (real)          : 0.009765625 to 0.10009765625 seconds
**             Hz                      : 10 to 102 Hz
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
** @file TI1.h
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

#ifndef __TI1
#define __TI1

/* MODULE TI1. */

/*Include shared modules, which are used for whole project*/
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "PE_Timer.h"
#include "Cpu.h"

/* PUBLISHED CONSTANTS */
#define TI1_SPT16_MIN      0x0140U     /* Lower bound of interval for method SetPeriodTicks16 */
#define TI1_SPT16Min       TI1_SPT16_MIN /* Deprecated */
#define TI1_SPT16_MAX      0x0CD0U     /* Upper bound of interval for method SetPeriodTicks16 */
#define TI1_SPT16Max       TI1_SPT16_MAX /* Deprecated */
#define TI1_SPT32_MIN      0x0140UL    /* Lower bound of interval for method SetPeriodTicks32 */
#define TI1_SPT32Min       TI1_SPT32_MIN /* Deprecated */
#define TI1_SPT32_MAX      0x0CD0UL    /* Upper bound of interval for method SetPeriodTicks32 */
#define TI1_SPT32Max       TI1_SPT32_MAX /* Deprecated */
#define TI1_SPUS_MIN       0x2626U     /* Lower bound of interval for method SetPeriodUS */
#define TI1_SPUSMin        TI1_SPUS_MIN /* Deprecated */
#define TI1_SPUS_MAX       0xFFFFU     /* Upper bound of interval for method SetPeriodUS */
#define TI1_SPUSMax        TI1_SPUS_MAX /* Deprecated */
#define TI1_SPMS_MIN       0x0AU       /* Lower bound of interval for method SetPeriodMS */
#define TI1_SPMSMin        TI1_SPMS_MIN /* Deprecated */
#define TI1_SPMS_MAX       0x64U       /* Upper bound of interval for method SetPeriodMS */
#define TI1_SPMSMax        TI1_SPMS_MAX /* Deprecated */

byte TI1_SetPeriodTicks16(word Ticks);
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
**                      (320 to 3280 ticks)
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_MATH - Overflow during evaluation
**                           ERR_RANGE - Parameter out of range
** ===================================================================
*/

byte TI1_SetPeriodTicks32(dword Ticks);
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
**                      (320 to 3280 ticks)
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_MATH - Overflow during evaluation
**                           ERR_RANGE - Parameter out of range
** ===================================================================
*/

byte TI1_SetPeriodUS(word Time);
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
**                      (9766 to 65535 microseconds)
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_MATH - Overflow during evaluation
**                           ERR_RANGE - Parameter out of range
** ===================================================================
*/

byte TI1_SetPeriodMS(word Time);
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
**                      (10 to 100 milliseconds)
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_MATH - Overflow during evaluation
**                           ERR_RANGE - Parameter out of range
** ===================================================================
*/

__interrupt void TI1_Interrupt(void);
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

void TI1_Init(void);
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


/* END TI1. */

#endif /* ifndef __TI1 */
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
