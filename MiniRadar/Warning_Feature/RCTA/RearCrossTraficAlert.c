/*
*   File:           RearCrossTraficAlert.c
*
*   Project name:   Mini Radar project
*   Author:         Benedek Balazs
*
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "RearCrossTraficAlert.h"

boolean RCTA_IsSpeedUnder10kmh(uint8_t speed) {
	return (speed < RCTA_SPEED);
}

boolean RCTA_IsGearOnReverse(uint8_t gear) {
	return (gear == REVERSE);
}

boolean RCTA_IsSytemStateMachineActive(uint8_t SSM_status) {
	return (SSM_status == SSM_ACTIVE);
}

boolean RCTA_IsInCollisionZone(uint8_t distance) {
	return (distance < RCTA_COLL_DISTANCE);
}