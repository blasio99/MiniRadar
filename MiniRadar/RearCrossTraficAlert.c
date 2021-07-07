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

#include "Constants.h"
#include "RearCrossTraficAlert.h"

uint8_t RCTA_IsSpeedUnder10kmh(uint8_t speed) {
	return speed < 10;
}

uint8_t RCTA_IsGearOnReverse(uint8_t gear) {
	return gear == REVERSE;
}

uint8_t RCTA_IsSytemStateMachineActive(uint8_t SSM_status) {
	return SSM_status == ACTIVE;
}