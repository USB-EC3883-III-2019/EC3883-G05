/**
 * @file Frame.c
 * @author Anderson Contreras
 * @brief API for handle the data frame
 * @version 0.1
 * @date 2019-10-02
 *
 * @copyright Copyright (c) 2019
 *
 */

#include "Frame.h"

volatile char is_Data_Ready;

struct FRAME Frame;
struct DATA Data;
struct DATAM2M DataM2M;

/**
 * @brief Pack the data in the frame structure
 *
 * @param frame
 * @param data
 */
void Pack(struct FRAME* frame, struct DATA data) {
    // Byte 0
    frame->Syn_0 = 0;
    frame->Position = data.Position;
    // Byte 1
    frame->Syn_1 = 1;
    frame->Sonar_low = data.Sonar.byte.low;
    // Byte 2
    frame->Syn_2 = 1;
    frame->Sonar_high = data.Sonar.byte.high;
    frame->Lidar_low = data.Lidar.byte.low;
    // Byte 3
    frame->Syn_3 = 1;
    frame->Lidar_high = data.Lidar.byte.high;
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