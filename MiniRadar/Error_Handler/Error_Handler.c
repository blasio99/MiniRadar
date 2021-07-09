/*
*   File:           Error_Handler.c
*
*   Project name:   Mini Radar project
*   Author:         Benedek Balazs
*
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "Error_Handler.h"

ErrorStructure error = { DEFAULT, NOT_YET_PERFOMED, "Empty message" };

void setBatteryOverVoltageError() {
	error.failed = OVER_VOLTAGE;
	error.errorState = FAILED;
	error.message = OVER_VOLTAGE_MSG;
}

void setBatteryUnderVoltageError() {
	error.failed = UNDER_VOLTAGE;
	error.errorState = FAILED;
	error.message = UNDER_VOLTAGE_MSG;
}

void clearErrorStructure() {
	error.failed = NO_ERROR;
	error.errorState = PASSED;
	error.message = NO_ERROR_MSG;
}

void errorHandler_MainFunction() {

	if (BV_IsBatteryOverVoltage(input.batteryVoltage)) {
		setBatteryOverVoltageError();
	}
	else {
		if (error.failed == OVER_VOLTAGE)
			clearErrorStructure();
	}
	
	if (BV_IsBatteryUnderVoltage(input.batteryVoltage)) {
		setBatteryUnderVoltageError();
	}
	else {
		if (error.failed == UNDER_VOLTAGE)
			clearErrorStructure();
	}
}