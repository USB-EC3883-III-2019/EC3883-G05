/* ###################################################################
**     Filename    : Events.c
**     Project     : SOLINDAR
**     Processor   : MC9S08QE128CLK
**     Component   : Events
**     Version     : Driver 01.02
**     Compiler    : CodeWarrior HCS08 C Compiler
**     Date/Time   : 2019-09-27, 20:09, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file Events.c
** @version 01.02
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         
/* MODULE Events */


#include "Cpu.h"
#include "Events.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
#include "string.h"
#include "Frame.h"
#include "Motor.h"
#include "Sensor.h"
#include "Tower.h"

/*
** ===================================================================
**     Event       :  AS1_OnError (module Events)
**
**     Component   :  AS1 [AsynchroSerial]
**     Description :
**         This event is called when a channel error (not the error
**         returned by a given method) occurs. The errors can be read
**         using <GetError> method.
**         The event is available only when the <Interrupt
**         service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void  AS1_OnError(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  AS1_OnRxChar (module Events)
**
**     Component   :  AS1 [AsynchroSerial]
**     Description :
**         This event is called after a correct character is received.
**         The event is available only when the <Interrupt
**         service/event> property is enabled and either the <Receiver>
**         property is enabled or the <SCI output mode> property (if
**         supported) is set to Single-wire mode.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void  AS1_OnRxChar(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  AS1_OnTxChar (module Events)
**
**     Component   :  AS1 [AsynchroSerial]
**     Description :
**         This event is called after a character is transmitted.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void  AS1_OnTxChar(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  AS1_OnFreeTxBuf (module Events)
**
**     Component   :  AS1 [AsynchroSerial]
**     Description :
**         This event is called after the last character in output
**         buffer is transmitted.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void  AS1_OnFreeTxBuf(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  AS1_OnFullRxBuf (module Events)
**
**     Component   :  AS1 [AsynchroSerial]
**     Description :
**         This event is called when the input buffer is full;
**         i.e. after reception of the last character 
**         that was successfully placed into input buffer.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void  AS1_OnFullRxBuf(void)
{
  /* Write your code here ... */
  AS1_RecvBlock(&DataP2M, 4, NULL);
  TowerMode = MASTER;
  TI1_SetPeriodMS(2000);
  is_Data_Ready = TRUE;
}

/*
** ===================================================================
**     Event       :  SonarTimer_OnInterrupt (module Events)
**
**     Component   :  SonarTimer [FreeCntr]
*/
/*!
**     @brief
**         This event is called when a compare matches the counter
**         value (if compare or reload is selected as a interrupt
**         source) or a counter overflows (for free-running devices).
**         It is valid only when the component is enabled - <"Enable">
**         and the events are enabled - <"EnableEvent">. The event is
**         available only if <Interrupt service/event> is enabled.
*/
/* ===================================================================*/
void SonarTimer_OnInterrupt(void)
{
  /* Write your code here ... */
  SonarTimer_Disable();
  SonarTimer_Reset();
  SONAR_DATA = 511;
  SONAR_STATE = SONAR_DONE;
}

/*
** ===================================================================
**     Event       :  SonarEcho_OnCapture (module Events)
**
**     Component   :  SonarEcho [Capture]
**     Description :
**         This event is called on capturing of Timer/Counter actual
**         value (only when the component is enabled - <Enable> and the
**         events are enabled - <EnableEvent>.This event is available
**         only if a <interrupt service/event> is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void SonarEcho_OnCapture(void)
{
  /* Write your code here ... */
  if(SonarEcho_GetPinValue()){
    SonarEcho_Reset();
  }
  else{
    SonarEcho_GetCaptureValue(&SONAR_DATA);
    SonarTimer_Disable();
    SonarTimer_Reset();
    SONAR_STATE = SONAR_DONE;
  }
}

/*
** ===================================================================
**     Event       :  LidarADC_OnEnd (module Events)
**
**     Component   :  LidarADC [ADC]
**     Description :
**         This event is called after the measurement (which consists
**         of <1 or more conversions>) is/are finished.
**         The event is available only when the <Interrupt
**         service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void LidarADC_OnEnd(void)
{
  /* Write your code here ... */
  LidarADC_GetValue16(&LIDAR_DATA);
  LIDAR_STATE = LIDAR_DONE;
}


/*
** ===================================================================
**     Event       :  MotorTimer_OnInterrupt (module Events)
**
**     Component   :  MotorTimer [TimerInt]
**     Description :
**         When a timer interrupt occurs this event is called (only
**         when the component is enabled - <Enable> and the events are
**         enabled - <EnableEvent>). This event is enabled only if a
**         <interrupt service/event> is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void MotorTimer_OnInterrupt(void)
{
  /* Write your code here ... */
  MotorState = MOTOR_READY;
}

/*
** ===================================================================
**     Event       :  IRSerial_OnError (module Events)
**
**     Component   :  IRSerial [AsynchroSerial]
**     Description :
**         This event is called when a channel error (not the error
**         returned by a given method) occurs. The errors can be read
**         using <GetError> method.
**         The event is available only when the <Interrupt
**         service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void  IRSerial_OnError(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  IRSerial_OnRxChar (module Events)
**
**     Component   :  IRSerial [AsynchroSerial]
**     Description :
**         This event is called after a correct character is received.
**         The event is available only when the <Interrupt
**         service/event> property is enabled and either the <Receiver>
**         property is enabled or the <SCI output mode> property (if
**         supported) is set to Single-wire mode.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void  IRSerial_OnRxChar(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  IRSerial_OnTxChar (module Events)
**
**     Component   :  IRSerial [AsynchroSerial]
**     Description :
**         This event is called after a character is transmitted.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void  IRSerial_OnTxChar(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  IRSerial_OnFullRxBuf (module Events)
**
**     Component   :  IRSerial [AsynchroSerial]
**     Description :
**         This eventclea is called when the input buffer is full;
**         i.e. after reception of the last character 
**         that was successfully placed into input buffer.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void  IRSerial_OnFullRxBuf(void)
{
  /* Write your code here ... */
  char i;
  char tmp[8];
  
  IRSerial_RecvBlock(&tmp, 8, NULL);

  for(i = 0; i < 4; i++){
    if((tmp[i] & 0xF0) == 128){
      DataM2M = (*(struct DATAM2M *) (&tmp[i]));
      break;
    } 
  }
  is_Data_Ready = TRUE;
}

/*
** ===================================================================
**     Event       :  IRSerial_OnFreeTxBuf (module Events)
**
**     Component   :  IRSerial [AsynchroSerial]
**     Description :
**         This event is called after the last character in output
**         buffer is transmitted.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void  IRSerial_OnFreeTxBuf(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  TI1_OnInterrupt (module Events)
**
**     Component   :  TI1 [TimerInt]
**     Description :
**         When a timer interrupt occurs this event is called (only
**         when the component is enabled - <Enable> and the events are
**         enabled - <EnableEvent>). This event is enabled only if a
**         <interrupt service/event> is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void TI1_OnInterrupt(void)
{
  /* Write your code here ... */
  TowerMode = SLAVE;
}

/* END Events */

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
