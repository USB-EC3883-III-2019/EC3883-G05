/*
 * Sensor.c
 *
 *  Created on: Oct 5, 2019
 *      Author: Anderson
 */


#include "AD1.h"
#include "Sensor.h"


struct SENSORSTATE SensorState;

void InitSensor(void){
    LIDAR_STATE = LIDAR_BUSY;
    SONAR_STATE = SONAR_BUSY;
};


void MeasureSensors(void){
    // LIDAR Sensor
    AD1_Measure(FALSE);
    LIDAR_STATE = LIDAR_BUSY;
    // SONAR Sensor
    SONAR_STATE = SONAR_BUSY;
};