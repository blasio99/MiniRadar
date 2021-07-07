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

#include "Constants.h"
#include "LaneChangeWarning.h"

uint8_t LCW_IsSpeedOver20kmh(uint8_t speed) {
	return speed >= 20;
}

uint8_t LCW_IsGearOnForward(uint8_t gear) {
	return gear == FORWARD;
}

uint8_t LCW_IsSteeringWheelAngleOver6(uint8_t angle) {
	return angle >= 6;
}

uint8_t LCW_IsSystemStateMachineActive(uint8_t SSM_status) {
	return SSM_status == ACTIVE;
}