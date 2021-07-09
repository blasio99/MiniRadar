/*
*   File:           LaneChangeWarning.h
*
*   Project name:   Mini Radar project
*   Author:         Benedek Balazs
*
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "../../Constants.h"

boolean LCW_IsSpeedOver20kmh(uint8_t speed);
boolean LCW_IsGearOnForward(uint8_t gear);
boolean LCW_IsSteeringWheelAngleOver6(uint8_t angle);
boolean LCW_IsSystemStateMachineActive(uint8_t SSM_status);
boolean LCW_IsInCollisionZone(uint8_t distance);