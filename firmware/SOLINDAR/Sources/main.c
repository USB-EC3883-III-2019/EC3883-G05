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
#include "TI1.h"

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
#include "Tower.h"

void main(void)
{
  /* Write your local variable definition here */
  char zone;
  struct DATAM2M data_tmp;

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  /* For example: for(;;) { } */

  InitMotor();
  InitSensor();
  InitBluetooth();
  InitTower();
 
  for(;;){
    if(is_Data_Ready){

      if((getZone(&DataP2M) != 0) && (TowerMode == MASTER)){
        setZone(&Motor, ZonesDef[zone = getZone(&DataP2M)]);  // Set the limits of the tower's zone
      }
      else if((getZone(&DataM2M) != 0) && (TowerMode == SLAVE)){
        setZone(&Motor, ZonesDef[zone = getZone(&DataM2M)]);  // Set the limits of the tower's zone
      }

      // It doesn't move if the zone is zero
      if(zone != 0){
        // Move the motor
        for(;;){
          if(MotorState == MOTOR_READY){
            MotorState = MOTOR_BUSY;
            
            if(StepMotor(&Motor) == STEP_LIMIT){
              break;
            }
          }
        }
      }

      if(TowerMode == MASTER){
        data_tmp = DataP2M;
        clearZone(&data_tmp);
        IRSerial_SendBlock(&data_tmp, 4, NULL);
        // If the zone is 0, send the data to the PC
        if(getZone(&DataM2M) == 0){
          AS1_SendBlock(&DataM2M, 4, NULL);
        }
      }
      else{
        data_tmp = DataM2M;
        clearZone(&data_tmp);
        IRSerial_SendBlock(&data_tmp, 4, NULL);
        AS1_SendBlock(&data_tmp, 4, NULL);
      }

      is_Data_Ready = FALSE;
    }
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
