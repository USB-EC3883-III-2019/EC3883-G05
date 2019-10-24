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
