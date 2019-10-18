/*
 * Sensor.h
 *
 *  Created on: Oct 5, 2019
 *      Author: Anderson
 */

#ifndef SENSOR_H_
#define SENSOR_H_

#include "PE_Types.h"

#pragma MESSAGE DISABLE C1106 /* WARNING C1106: Non-standard bitfield type */


#define SENSORS_BUSY 1
#define SENSORS_DONE 0

#define LIDAR_BUSY 1
#define LIDAR_DONE 0

#define SONAR_BUSY 1
#define SONAR_DONE 0

#define SENSORS_STATE SensorState.Sensor.GlobalState
#define LIDAR_STATE   SensorState.Sensor.Sensor.LidarState
#define SONAR_STATE   SensorState.Sensor.Sensor.SonarState


struct SENSORSTATE {
    union SENSOR_U {
        byte GlobalState;
        struct SENSOR_S {
            byte LidarState : 4;
            byte SonarState : 4;
        } Sensor;
    } Sensor;
};
extern struct SENSORSTATE SensorState;

extern void InitSensor(void);
extern void MeasureSensors(void);

#endif /* SENSOR_H_ */
