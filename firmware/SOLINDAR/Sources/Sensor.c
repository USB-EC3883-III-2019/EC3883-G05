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

#include "AD1.h"
#include "Bit1.h"
#include "Cap1.h"
#include "FC1.h"

struct SENSORSTATE SensorState;

/**
 * @brief Initialize the sensors
 *
 */
void InitSensor(void) {
    LIDAR_STATE = LIDAR_BUSY;
    Cap1_Reset();
    FC1_Disable();  // Init timer for overflow the Sonar
    FC1_Reset();
    SONAR_STATE = SONAR_BUSY;
};

/**
 * @brief Get a measure from the infrared and ultrasonic sensors
 *
 */
void MeasureSensors(void) {
    // Sonar Sensor
    Bit1_SetVal();  // Set trigger output

    // LIDAR Sensor
    AD1_Measure(TRUE);

    // SONAR Sensor
    Bit1_ClrVal();  // Clear trigger output
    FC1_Enable();
    SONAR_STATE = SONAR_BUSY;
};
