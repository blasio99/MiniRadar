/*
*   File:           Battery_Voltage.c
*
*   Project name:   Mini Radar project
*   Author:         Benedek Balazs
*
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "Battery_Voltage.h"

boolean BV_IsBatteryUnderVoltage(uint8_t voltage) {
	return (BATTERY_VOLTAGE_MIN > voltage);
}

boolean BV_IsBatteryOverVoltage(uint8_t voltage) {
	return (BATTERY_VOLTAGE_MAX < voltage);
}

boolean BV_IsBatteryVoltageInRange(uint8_t voltage) {
	return (BV_IsBatteryUnderVoltage(voltage) == FALSE
		&& BV_IsBatteryOverVoltage(voltage) == FALSE);
}
