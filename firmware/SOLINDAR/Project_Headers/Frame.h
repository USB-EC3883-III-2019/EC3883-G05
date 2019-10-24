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

#ifndef FRAME_H_
#define FRAME_H_

#include "PE_Types.h"

#pragma MESSAGE DISABLE C1106 /* WARNING C1106: Non-standard bitfield type */

#define FRAME_SIZE    4
#define POSITION_DATA Data.Position
#define LIDAR_DATA    Data.Lidar.fulldata
#define SONAR_DATA    Data.Sonar.fulldata

extern volatile byte is_Data_Ready;

// Struct for Data
struct DATA {
    byte Position;
    union LIDAR {
        word fulldata;
        struct LIDARBYTE {
            byte high : 7;
            byte low : 5;
        } byte;
    } Lidar;
    union SONAR {
        word fulldata;
        struct SONARBYTE {
            byte high : 2;
            byte low : 7;
        } byte;
    } Sonar;
};
extern struct DATA Data;

// Data frame struct
struct FRAME {
    byte Position   : 6;
    byte Syn_0      : 2;
    byte Sonar_low  : 7;
    byte Syn_1      : 1;
    byte Lidar_low  : 5;
    byte Sonar_high : 2;
    byte Syn_2      : 1;
    byte Lidar_high : 7;
    byte Syn_3      : 1;
};
extern struct FRAME Frame;

// Function for packing the data into the frame
void Pack(struct FRAME* frame, struct DATA data);

#endif /* FRAME_H_ */
