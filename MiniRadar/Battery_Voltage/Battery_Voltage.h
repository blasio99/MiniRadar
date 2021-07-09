/*
*   File:           Battery_Voltage.h
*
*   Project name:   Mini Radar project
*   Author:         Benedek Balazs
*
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "../Constants.h"

boolean BV_IsBatteryUnderVoltage  (uint8_t voltage);
boolean BV_IsBatteryOverVoltage   (uint8_t voltage);
boolean BV_IsBatteryVoltageInRange(uint8_t voltage);