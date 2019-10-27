/**
 * @file Sensor.c
 * @author Anderson Contreras
 * @brief API for handle the lidar and sonar sensors
 * @version 0.1
 * @date 2019-10-05
 *
 * @copyright Copyright (c) 2019
 *
 */

#include "Sensor.h"

#include "LidarADC.h"
#include "SonarTrigger.h"
#include "SonarEcho.h"
#include "SonarTimer.h"

struct SENSORSTATE SensorState;

/**
 * @brief Initialize the sensors
 *
 */
void InitSensor(void) {
    LIDAR_STATE = LIDAR_BUSY;
    SonarEcho_Reset();
    SonarTimer_Disable();  // Init timer for overflow the Sonar
    SonarTimer_Reset();
    SONAR_STATE = SONAR_BUSY;
};

/**
 * @brief Get a measure from the infrared and ultrasonic sensors
 *
 */
void MeasureSensors(void) {
    // Sonar Sensor
    SonarTrigger_SetVal();  // Set trigger output

    // LIDAR Sensor
    LidarADC_Measure(TRUE);

    // SONAR Sensor
    SonarTrigger_ClrVal();  // Clear trigger output
    SonarTimer_Enable();
    SONAR_STATE = SONAR_BUSY;
};
