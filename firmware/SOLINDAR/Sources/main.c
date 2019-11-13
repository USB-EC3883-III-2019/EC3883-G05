/* ###################################################################
**     Filename    : main.c
**     Project     : SOLINDAR
**     Processor   : MC9S08QE128CLK
**     Version     : Driver 01.12
**     Compiler    : CodeWarrior HCS08 C Compiler
**     Date/Time   : 2019-09-27, 20:09, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.12
** @brief
**         Main module.
**         This module contains user's application code.
*/
/*!
**  @addtogroup main_module main module documentation
**  @{
*/
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "AS1.h"
#include "MotorTimer.h"
#include "LidarADC.h"
#include "MotorPort.h"
#include "SonarEcho.h"
#include "SonarTrigger.h"
#include "SonarTimer.h"
#include "IRSerial.h"
#include "IRPWM.h"

/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
#include "Frame.h"
#include "Motor.h"
#include "Sensor.h"
#include "Bluetooth.h"

void main(void)
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  /* For example: for(;;) { } */

  InitMotor();
  InitSensor();
  InitBluetooth();
  
    for(;;){
    if(MotorState == MOTOR_READY){
      // If the motor rotation limit is reached, it changes direction of rotation
      if(StepMotor(&Motor) == STEP_LIMIT){
        if(Motor.Rotation == CW_ROTATION){
          SetOrientation(&Motor, CCW_ROTATION);
        }
        else{
          SetOrientation(&Motor, CW_ROTATION);
        }
      }

      MeasureSensors();
      POSITION_DATA = MOTOR_STEP_COUNT;
      
      Cpu_SetWaitMode();

      while(SENSORS_STATE != SENSORS_DONE);       // Wait for the data is ready

      Pack(&Frame, Data);                         // Pack the data
      AS1_SendBlock(&Frame, FRAME_SIZE, NULL);    // Send the data
      
      MotorState = MOTOR_BUSY;
    }
      Cpu_SetWaitMode();
  }

  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
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
