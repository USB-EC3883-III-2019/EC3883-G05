/*
 * Motor.c
 *
 *  Created on: Sep 30, 2019
 *      Author: Anderson
 */

#include "Bits1.h"
#include "Motor.h"

char MotorState;

char Sequence[8] ={
    0b0101,
    0b0001,
    0b1001,
    0b1000,
    0b1010,
    0b0010,
    0b0110,
    0b0100,
};

struct StepperMotor Motor;

void InitMotor(void){
    SetOrientation(&Motor, CW_ROTATION);
    SetCWLimit(&Motor, CW_LIMIT);
    SetCCWLimit(&Motor, CCW_LIMIT);
    Motor.Port_Func = &Bits1_PutVal;
    (*Motor.Port_Func)(Sequence[Motor.StateSequence]);
}

void SetOrientation(struct StepperMotor *Motor, char Orientation) {
    Motor->Rotation = Orientation;
};

void SetCWLimit(struct StepperMotor *Motor, signed char Limit) {
    Motor->CW_Limit = Limit;
};

void SetCCWLimit(struct StepperMotor *Motor, signed char Limit) {
    Motor->CCW_Limit = Limit;
};

char StepMotor(struct StepperMotor *Motor) {
    if (Motor->Rotation == CW_ROTATION) {
        if (Motor->StepCount == Motor->CW_Limit) {
            return STEP_LIMIT;
        }
        Motor->StepCount++;
        if(Motor->StateSequence++ == 7){
            Motor->StateSequence = 0;
        }
    }
    else {
        if (Motor->StepCount == Motor->CCW_Limit) {
            return STEP_LIMIT;
        }
        Motor->StepCount--;
        if(Motor->StateSequence-- == 0){
            Motor->StateSequence = 7;
        }
    }
    (*Motor->Port_Func)(Sequence[Motor->StateSequence]);
    return STEP_OK;
};