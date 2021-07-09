/*
*   File:           MiniRadar.c
*
*   Project name:   Mini Radar project
*   Author:         Benedek Balazs
*
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "../Constants.h"
#include "../Battery_Voltage/Battery_Voltage.h"

extern INPUT input;

extern ErrorStructure error;

void setBatteryOverVoltageError();
void setBatteryUnderVoltageError();
void errorHandler_MainFunction();