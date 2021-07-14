/*
*   File:           MiniRadar.h
*
*   Project name:   Mini Radar project
*   Author:         Benedek Balazs
*
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "Constants.h"
#include "Error_Handler/Error_Handler.h"
#include "Battery_Voltage/Battery_Voltage.h"
#include "Communication_Interface/Communication_Interface.h"
#include "SystemStateMachine/SystemStateMachine.h"
#include "Warning_Feature/Warning_Feature.h"
#include "testMain.h"

extern INPUT data;
extern uint8_t warning_led;
extern uint8_t warning_beep;

extern FeatureState LCW_Feature_State;
extern FeatureState RCTA_Feature_State;

extern SysStMState SSM_State;
extern ErrorStructure error;

extern testStructure test;
extern uint8_t tests_run;
extern uint8_t tests_failed;
