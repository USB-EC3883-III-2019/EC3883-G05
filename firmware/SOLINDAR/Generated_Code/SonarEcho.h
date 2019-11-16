/* ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : SonarEcho.h
**     Project     : SOLINDAR
**     Processor   : MC9S08QE128CLK
**     Component   : Capture
**     Version     : Component 02.223, Driver 01.30, CPU db: 3.00.067
**     Compiler    : CodeWarrior HCS08 C Compiler
**     Date/Time   : 2019-11-16, 13:09, # CodeGen: 93
**     Abstract    :
**         This component "Capture" simply implements the capture function
**         of timer. The counter counts the same way as in free run mode. On
**         the selected edge of the input signal (on the input pin), the current
**         content of the counter register is written into the capture
**         register and the OnCapture event is called.
**     Settings    :
**             Timer capture encapsulation : Capture
**
**         Timer
**             Timer                   : TPM2
**             Counter shared          : No
**
**         High speed mode
**             Prescaler               : divide-by-2
**           Maximal time for capture register
**             Xtal ticks              : 262144
**             microseconds            : 8000000
**             milliseconds            : 8000
**             seconds                 : 8
**             seconds (real)          : 8.0
**           One tick of timer is
**             microseconds            : 122.070312
**
**         Initialization:
**              Timer                  : Enabled
**              Events                 : Enabled
**
**         Timer registers
**              Capture                : TPM2C2V   [$005C]
**              Counter                : TPM2CNT   [$0051]
**              Mode                   : TPM2SC    [$0050]
**              Run                    : TPM2SC    [$0050]
**              Prescaler              : TPM2SC    [$0050]
**
**         Used input pin              : 
**             ----------------------------------------------------
**                Number (on package)  |    Name
**             ----------------------------------------------------
**                       47            |  PTA7_TPM2CH2_ADP9
**             ----------------------------------------------------
**
**         Port name                   : PTA
**         Bit number (in port)        : 7
**         Bit mask of the port        : $0080
**
**         Signal edge/level           : both
**         Priority                    : 
**         Pull option                 : off
**
**     Contents    :
**         Reset           - byte SonarEcho_Reset(void);
**         GetCaptureValue - byte SonarEcho_GetCaptureValue(SonarEcho_TCapturedValue *Value);
**         GetPinValue     - bool SonarEcho_GetPinValue(void);
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
** @file SonarEcho.h
** @version 01.30
** @brief
**         This component "Capture" simply implements the capture function
**         of timer. The counter counts the same way as in free run mode. On
**         the selected edge of the input signal (on the input pin), the current
**         content of the counter register is written into the capture
**         register and the OnCapture event is called.
*/         
/*!
**  @addtogroup SonarEcho_module SonarEcho module documentation
**  @{
*/         

#ifndef __SonarEcho
#define __SonarEcho

/*Include shared modules, which are used for whole project*/
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "PE_Timer.h"

/* MODULE SonarEcho. */

#include "Cpu.h"

/* PUBLISHED CONSTANTS */
#define SonarEcho_PRESCALER_VALUE           0x02U /* Prescaler value of the timer in high speed mode */
#define SonarEcho_COUNTER_INPUT_CLOCK_HZ    0x2000LU /* Initial counter input clock frequency [Hz] */
#define SonarEcho_TIMER_INPUT_CLOCK         0x01800000LU /* Deprecated, Initial timer input clock frequency [Hz] */
#define SonarEcho_PRESCALER_VALUE_HIGH      0x02U /* Prescaler value of the timer in high speed mode */
#define SonarEcho_COUNTER_INPUT_CLOCK_HZ_HIGH 0x2000LU /* Counter input clock frequency in high speed mode [Hz] */
#define SonarEcho_TIMER_INPUT_CLOCK_HIGH    0x01800000LU /* Deprecated, Timer input clock frequency in high speed mode[Hz] */

#ifndef __BWUserType_SonarEcho_TCapturedValue
#define __BWUserType_SonarEcho_TCapturedValue
  #define SonarEcho_TCapturedValue word /*  Captured value, unsigned integer value. Bit-width of the type depends on the width of selected timer. */
#endif



#define SonarEcho_Reset() \
  (TPM2CNTH = 0U , (byte)ERR_OK)
/*
** ===================================================================
**     Method      :  SonarEcho_Reset (component Capture)
**     Description :
**         This method resets the counter register (see implementation
**         note in <General Info>).
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/

#define SonarEcho_GetCaptureValue(Value) \
  /*lint -save  -e926 -e927 -e928 -e929 Disable MISRA rule (11.4) checking. */\
  (*(SonarEcho_TCapturedValue*)(Value) = TPM2C2V , (byte)ERR_OK) \
  /*lint -restore Enable MISRA rule (11.4) checking. */
/*
** ===================================================================
**     Method      :  SonarEcho_GetCaptureValue (component Capture)
**     Description :
**         This method gets the last value captured by enabled timer.
**         Note: one tick of timer is
**               122.070312 us in high speed mode
**     Parameters  :
**         NAME            - DESCRIPTION
**       * Value           - A pointer to the content of the
**                           capture register
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/

#define SonarEcho_GetPinValue() ((PTAD & 0x80U) ? TRUE : FALSE)
/*
** ===================================================================
**     Method      :  SonarEcho_GetPinValue (component Capture)
**     Description :
**         The method reads the Capture pin value. The method is
**         available only if it is possible to read the pin value
**         (usually not available for internal signals).
**     Parameters  : None
**     Returns     :
**         ---             - Capture pin value.
**                           <true> - high level
**                           <false> - low level.
** ===================================================================
*/

void SonarEcho_Init(void);
/*
** ===================================================================
**     Method      :  SonarEcho_Init (component Capture)
**
**     Description :
**         Initializes the associated peripheral(s) and the component 
**         internal variables. The method is called automatically as a 
**         part of the application initialization code.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/

__interrupt void SonarEcho_Interrupt(void);
/*
** ===================================================================
**     Method      :  Interrupt (component Capture)
**
**     Description :
**         The method services the interrupt of the selected peripheral(s)
**         and eventually invokes event(s) of the component.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/


/* END SonarEcho. */

#endif /* ifndef __SonarEcho */
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
