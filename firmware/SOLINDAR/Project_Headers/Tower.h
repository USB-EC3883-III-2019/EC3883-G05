/**
 * @file Tower.h
 * @author Anderson Contreras
 * @brief Functions for handling the tower
 * @version 0.1
 * @date 2019-11-16
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef TOWER_H_
#define TOWER_H_

#define SLAVE    0
#define MASTER   1

#define MIDDLEPOINT(a, b)   (a + b)/2

// Uncomment for set the scanning mode
//#define TOWERSCAN

extern char TowerMode;

struct ZONESDEF{
    signed char UpperLimit;
    signed char LowerLimit;
};
extern struct ZONESDEF ZonesDef[];

extern char clearZone(struct DATAM2M *DataM2M);
extern char getZone(struct DATAM2M *DataM2M);
extern void setZone(struct StepperMotor *Motor, struct ZONESDEF ZonesDef);

#endif /* TOWER_H_ */
