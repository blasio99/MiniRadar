/*
*   File:           Warning_Feature.c
*
*   Project name:   Mini Radar project
*   Author:         Benedek Balazs
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "Warning_Feature.h"

FeatureState LCW_Feature_State	= PASSIVE;
FeatureState RCTA_Feature_State = PASSIVE;

boolean WF_IsLCWActive(INPUT data) {
	return (LCW_IsSpeedOver20kmh(data.speed)
		&&  LCW_IsGearOnForward(data.gear)
		&&  LCW_IsSteeringWheelAngleOver6(data.steeringWheel)
		&&  LCW_IsSystemStateMachineActive(SSM_State));
}

boolean WF_IsRCTAActive(INPUT data) {
	return (RCTA_IsSpeedUnder10kmh(data.speed)
		&&  RCTA_IsGearOnReverse(data.gear)
		&&  RCTA_IsSytemStateMachineActive(SSM_State));
}

void setLCW_Feature_State(FeatureState state) {
	LCW_Feature_State = state;
}

void setRCTA_Feature_State(FeatureState state) {
	RCTA_Feature_State = state;
}

void WF_WarningSigns(INPUT data) {
	
	if (((WF_IsLCWActive (data) == TRUE) && (LCW_IsInCollisionZone (data.distance) == TRUE))
	 || ((WF_IsRCTAActive(data) == TRUE) && (RCTA_IsInCollisionZone(data.distance) == TRUE)))
	{
		warning_led  = WARNING_ACTIVE;
		warning_beep = WARNING_ACTIVE;
	}
	else {
		warning_led  = WARNING_INACTIVE;
		warning_beep = WARNING_INACTIVE;
	}
}