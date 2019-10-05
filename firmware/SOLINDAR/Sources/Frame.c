/*
 * Frame.c
 *
 *  Created on: Oct 2, 2019
 *      Author: Anderson
 */


#include "Frame.h"


volatile char is_Data_Ready;
volatile char *BufferSerialCount;

struct FRAME Frame;
struct DATA Data;

void Pack(struct FRAME *frame, struct DATA data) {
    // Byte 0
    frame->Syn_0      = 0;
    frame->Position   = data.Position;
    // Byte 1
    frame->Syn_1      = 1;
    frame->Sonar_low  = data.Sonar.byte.low;
    // Byte 2
    frame->Syn_2 = 1;
    frame->Sonar_high = data.Sonar.byte.high;
    frame->Lidar_low  = data.Lidar.byte.low;
    // Byte 3
    frame->Syn_3 = 1;
    frame->Lidar_high = data.Lidar.byte.high;
}
