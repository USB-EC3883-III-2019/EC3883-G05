/*
 * Motor.h
 *
 *  Created on: Sep 30, 2019
 *      Author: Anderson
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#include "IO_Map.h"

#define Q1 PTBD_PTBD0
#define Q2 PTBD_PTBD1
#define Q3 PTBD_PTBD2
#define Q4 PTBD_PTBD3


#define SEC_MASK_Q1 0b0001
#define SEC_MASK_Q2 0b0010
#define SEC_MASK_Q3 0b0100
#define SEC_MASK_Q4 0b1000

#define CW_ROTATION  0
#define CCW_ROTATION 1


#define STEP_OK    0
#define STEP_LIMIT 1


extern struct StepperMotor;
extern void SetOrientation(struct StepperMotor *, char);
extern char StepMotor(struct StepperMotor *);

#endif /* MOTOR_H_ */
