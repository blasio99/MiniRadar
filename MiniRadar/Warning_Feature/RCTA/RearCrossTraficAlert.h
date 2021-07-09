/*
*   File:           RearCrossTraficAlert.h
*
*   Project name:   Mini Radar project
*   Author:         Benedek Balazs
*
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "../../Constants.h"

boolean RCTA_IsSpeedUnder10kmh(uint8_t speed);
boolean RCTA_IsGearOnReverse(uint8_t gear);
boolean RCTA_IsSytemStateMachineActive(uint8_t SSM_status);
boolean RCTA_IsInCollisionZone(uint8_t distance);