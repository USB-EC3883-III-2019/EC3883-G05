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

struct ZONESDEF{
    char UpperLimit;
    char LowerLimit;
};
extern struct ZONESDEF ZonesDef[];

extern char getZone(struct DATAM2M *DataM2M);
extern void setZone(struct StepperMotor *Motor, struct ZONESDEF ZonesDef);

#endif /* TOWER_H_ */
