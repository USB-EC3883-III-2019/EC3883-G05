/**
 * @file Motor.c
 * @author Anderson Contreras
 * @brief API for handle the stepper motor
 * @version 0.1
 * @date 2019-09-30
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#include "IO_Map.h"

#define CW_ROTATION  0
#define CCW_ROTATION 1

#define CW_LIMIT   30
#define CCW_LIMIT -30

#define STEP_OK     0
#define STEP_LIMIT  1

#define MOTOR_BUSY  0
#define MOTOR_READY 1

#define MOTOR_STEP_COUNT Motor.StepCount

extern char MotorState;

struct StepperMotor {
    char Rotation : 1;
    char          : 7;
    signed char StepCount;
    signed char StateSequence;
    signed char CW_Limit;
    signed char CCW_Limit;
    void (*Port_Func)(byte);
};
extern struct StepperMotor Motor;

extern void InitMotor(void);
extern void SetOrientation(struct StepperMotor*, char);
extern char StepMotor(struct StepperMotor*);
extern void SetCWLimit(struct StepperMotor*, signed char);
extern void SetCCWLimit(struct StepperMotor*, signed char);

#endif /* MOTOR_H_ */
