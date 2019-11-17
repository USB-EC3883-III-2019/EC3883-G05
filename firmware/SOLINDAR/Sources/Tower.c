/**
 * @file Tower.c
 * @author Anderson Contreras
 * @brief Functions for handling the tower
 * @version 0.1
 * @date 2019-11-16
 * 
 * @copyright Copyright (c) 2019
 * 
 */


#include "Tower.h"
#include "Motor.h"
#include "Frame.h"

struct ZONESDEF ZonesDef[8];

/**
 * @brief Initialize the zones
 * 
 */
void InitTower(void){
    // Zone 0. This is a not real zone
    ZonesDef[0].LowerLimit = 0;
    ZonesDef[0].UpperLimit = 0;

    // Zone 1
    ZonesDef[1].LowerLimit = -30;
    ZonesDef[1].UpperLimit = -20;
    
    // Zone 2
    ZonesDef[2].LowerLimit = -20;
    ZonesDef[2].UpperLimit = -10;
    
    // Zone 3
    ZonesDef[3].LowerLimit = -10;
    ZonesDef[3].UpperLimit =   0;
    
    // Zone 4
    ZonesDef[4].LowerLimit =  0;
    ZonesDef[4].UpperLimit = 10;
    
    // Zone 5
    ZonesDef[5].LowerLimit = 10;
    ZonesDef[5].UpperLimit = 20;
    
    // Zone 6
    ZonesDef[6].LowerLimit = 20;
    ZonesDef[6].UpperLimit = 30;
}


/**
 * @brief Get the next Zone to send the data. This function clear the zone used
 * 
 * @param DataM2M
 * @return Zone number. If return is 0, there's no more zones
 */
char getZone(struct DATAM2M *DataM2M){
    char zone = 0;

    if(DataM2M->Z1 != 0){
        zone = DataM2M->Z1;
        DataM2M->Z1 = 0;
    }
    else if(DataM2M->Z2 != 0){
        zone = DataM2M->Z2;
        DataM2M->Z2 = 0;
    }
    else if(DataM2M->Z3 != 0){
        zone = DataM2M->Z3;
        DataM2M->Z3 = 0;
    }
    else if(DataM2M->Z4 != 0){
        zone = DataM2M->Z4;
        DataM2M->Z4 = 0;
    }
    return zone;
}


/**
 * @brief Set the Zone to send the message
 * 
 * @param Motor 
 * @param ZonesDef 
 */
void setZone(struct StepperMotor *Motor, struct ZONESDEF ZonesDef){
    Motor->CW_Limit  = ZonesDef.UpperLimit;
    Motor->CCW_Limit = ZonesDef.LowerLimit;

    if(Motor->StepCount > ZonesDef.UpperLimit){
        SetOrientation(&Motor, CCW_ROTATION);
    }
    else{
        SetOrientation(&Motor, CW_ROTATION);
    }
}