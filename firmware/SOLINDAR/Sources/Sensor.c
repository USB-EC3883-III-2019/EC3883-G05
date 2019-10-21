/*
 * Sensor.c
 *
 *  Created on: Oct 5, 2019
 *      Author: Anderson
 */


#include "AD1.h"
#include "Bit1.h"
#include "Cap1.h"
#include "FC1.h"
#include "Sensor.h"


struct SENSORSTATE SensorState;

void InitSensor(void){
    LIDAR_STATE = LIDAR_BUSY;
    Cap1_Reset();
    FC1_Disable();          // Init timer for overflow the Sonar
    FC1_Reset();
    SONAR_STATE = SONAR_BUSY;
};


void MeasureSensors(void){
    // Sonar Sensor
    Bit1_SetVal();          // Set trigger output
    
    // LIDAR Sensor
    AD1_Measure(TRUE);
    
    // SONAR Sensor
    Bit1_ClrVal();          // Clear trigger output
    FC1_Enable();
    SONAR_STATE = SONAR_BUSY;
};
