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

#include "Motor.h"

#include "MotorPort.h"

char MotorState;

char Sequence[8] = {
    0b0101, 0b0001, 0b1001, 0b1000, 0b1010, 0b0010, 0b0110, 0b0100,
};

struct StepperMotor Motor;

/**
 * @brief Initialize the stepper motor
 *
 */
void InitMotor(void) {
    SetOrientation(&Motor, CW_ROTATION);
    SetCWLimit(&Motor, CW_LIMIT);
    SetCCWLimit(&Motor, CCW_LIMIT);
    Motor.Port_Func = &MotorPort_PutVal;
    (*Motor.Port_Func)(Sequence[Motor.StateSequence]);
}

/**
 * @brief Set the Orientation of the motor
 *
 * @param Motor
 * @param Orientation
 */
void SetOrientation(struct StepperMotor* Motor, char Orientation) {
    Motor->Rotation = Orientation;
};

/**
 * @brief Set the clockwise limit of the motor
 *
 * @param Motor
 * @param Limit
 */
void SetCWLimit(struct StepperMotor* Motor, signed char Limit) {
    Motor->CW_Limit = Limit;
};

/**
 * @brief Set the counter clockwise limit of the motor
 *
 * @param Motor
 * @param Limit
 */
void SetCCWLimit(struct StepperMotor* Motor, signed char Limit) {
    Motor->CCW_Limit = Limit;
};

/**
 * @brief Turn half step the stepper motor
 *
 * @param Motor
 * @return char
 */
char StepMotor(struct StepperMotor* Motor) {
    if (Motor->Rotation == CW_ROTATION) {
        if (Motor->StepCount == Motor->CW_Limit) {
            return STEP_LIMIT;
        }
        Motor->StepCount++;
        if (Motor->StateSequence++ == 7) {
            Motor->StateSequence = 0;
        }
    } else {
        if (Motor->StepCount == Motor->CCW_Limit) {
            return STEP_LIMIT;
        }
        Motor->StepCount--;
        if (Motor->StateSequence-- == 0) {
            Motor->StateSequence = 7;
        }
    }
    (*Motor->Port_Func)(Sequence[Motor->StateSequence]);
    return STEP_OK;
};