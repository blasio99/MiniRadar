/*
*   File:           LaneChangeWarning.c
*
*   Project name:   Mini Radar project
*   Author:         Benedek Balazs
*
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "LaneChangeWarning.h"

boolean LCW_IsSpeedOver20kmh(uint8_t speed) {
	return (speed > LCW_SPEED);
}

boolean LCW_IsGearOnForward(uint8_t gear) {
	return (gear == FORWARD);
}

boolean LCW_IsSteeringWheelAngleOver6(uint8_t angle) {
	return (angle > LCW_STEERING_ANGLE);
}

boolean LCW_IsSystemStateMachineActive(uint8_t SSM_status) {
	return (SSM_status == SSM_ACTIVE);
}

boolean LCW_IsInCollisionZone(uint8_t distance) {
	return (distance < LCW_COLL_DISTANCE);
}