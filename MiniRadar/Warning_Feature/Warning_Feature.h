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
#include "LCW/LaneChangeWarning.h"
#include "RCTA/RearCrossTraficAlert.h"

uint8_t warning_led;
uint8_t warning_beep;

extern uint8_t SSM_State;

uint8_t WF_IsLCWActive(INPUT data);
uint8_t WF_IsRCTAActive(INPUT data);
void setLCW_Feature_State(FeatureState state);
void setRCTA_Feature_State(FeatureState state);
void WF_WarningSigns(INPUT data);