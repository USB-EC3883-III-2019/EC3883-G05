/*
 * Motor.c
 *
 *  Created on: Sep 30, 2019
 *      Author: Anderson
 */

#include "Motor.h"

char Sequence[8] ={
    0b1010,
    0b1000,
    0b1001,
    0b0001,
    0b0101,
    0b0100,
    0b0110,
    0b0010,
};


struct StepperMotor {
    char Rotation  : 1;
    char           : 1;
    char StepCount : 6;
    char SequenceState;
    char CW_Limit;
    char CCW_Limit;
};

void SetOrientation(struct StepperMotor *Motor, char Orientation) {
    Motor->Rotation = Orientation;
};

char StepMotor(struct StepperMotor *Motor) {
    if (Motor->Rotation == CW_ROTATION) {
        if (Motor->StepCount > Motor->CW_Limit) {
            return STEP_LIMIT;
        }
        Motor->SequenceState++;
    } else {
        if (Motor->StepCount < Motor->CCW_Limit) {
            return STEP_LIMIT;
        }
        Motor->SequenceState--;
    }
    Q1 = SEC_MASK_Q1 & Sequence[Motor->SequenceState];
    Q2 = SEC_MASK_Q2 & Sequence[Motor->SequenceState];
    Q3 = SEC_MASK_Q3 & Sequence[Motor->SequenceState];
    Q4 = SEC_MASK_Q4 & Sequence[Motor->SequenceState];
    return STEP_OK;
};