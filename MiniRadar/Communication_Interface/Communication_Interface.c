/*
*   File:           Communication_Interface.c
*
*   Project name:   Mini Radar project
*   Author:         Benedek Balazs
*
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "Communication_Interface.h"

time_t secondsForRead;
INPUT input = { DEFAULT, DEFAULT, DEFAULT, DEFAULT, DEFAULT };

/* TEST variables */
char inputTextLedBeep[3];
char inputTextSSMState[11];

void LostCommunicationHandler(Error error_type, char* error_message) {
    error.failed        = error_type;
    error.errorState    = FAILED;
    error.message       = error_message;
}

boolean ComIF_IsOutOfRange(int value) {
    return ((value < 0) || (value > 255));
}

boolean ComIF_IsSpeedCorrectValue() {
    return ((MIN_SPEED <= input.speed) && (input.speed <= MAX_SPEED));
}


boolean ComIF_IsGearValueInGoodRange() {
    return ((GEAR_MIN_VALUE <= input.gear) && (input.gear <= GEAR_MAX_VALUE));
}

boolean ComIF_IsSteeringWheelValueCorrect(int steeringAngleValue) {
    return(((steeringAngleValue + STEERING_ANGLE_MID) >= STEERING_ANGLE_MIN)
        && ((steeringAngleValue + STEERING_ANGLE_MID) <= STEERING_ANGLE_MAX));
}

boolean ComIF_IsDistanceCorrectValue() {
    return ((MIN_DISTANCE <= input.distance) && (input.distance <= MAX_DISTANCE));
}

boolean ComIF_IsBatteryVoltageInGoodRange() {
    return ((BATTERY_VOLTAGE_MIN <= input.batteryVoltage) 
        && (input.batteryVoltage <= BATTERY_VOLTAGE_MAX));
}

void inputTextParser() {
    
    /* The first input of desired expected value is STRING, so we transform it to INTEGER */
    if (strcmp(inputTextSSMState, SSM_ACTIVE_TEXT) == 0) {
        test.SSM_State = SSM_ACTIVE;
    }
    else if (strcmp(inputTextSSMState, SSM_INIT_TEXT) == 0) {
        test.SSM_State = SSM_INIT;
    }
    else if (strcmp(inputTextSSMState, SSM_ERROR_TEXT) == 0) {
        test.SSM_State = SSM_ERROR;
    }
    else {
        test.SSM_State = SSM_NO_STATE;
    }

    /* We do the same with the second test input */
    if (strcmp(inputTextLedBeep, OFF_TEXT) == 0) {
        test.LedBeepState = WARNING_INACTIVE;
    }
    else if (strcmp(inputTextLedBeep, ON_TEXT) == 0) {
        test.LedBeepState = WARNING_ACTIVE;
    }
    else {
        test.LedBeepState = LEDBEEP_NO_STATE;
    }

    memset(inputTextSSMState, 0, strlen(inputTextSSMState));
    memset(inputTextLedBeep,  0, strlen(inputTextLedBeep ));

}

INPUT ComIF_read_inputData(FILE* fp) {

    int input_value;
    
    /* Read input values from the given file as parameter*/
    if (!fscanf(fp, "%d", &input_value) || ComIF_IsOutOfRange(input_value) == TRUE) {
        LostCommunicationHandler(SPEED_WRONG_INPUT, SPEED_WRONG_INPUT_MSG);
    }
    else {
        input.speed = input_value;
        if (error.failed == SPEED_WRONG_INPUT) {
            clearErrorStructure();
        }
    }

    if (!fscanf(fp, "%d", &input_value) || (ComIF_IsOutOfRange(input_value) == TRUE)) {
        LostCommunicationHandler(GEAR_WRONG_INPUT, GEAR_WRONG_INPUT_MSG);
    }
    else {
        input.gear = input_value;
        if (error.failed == GEAR_WRONG_INPUT) {
            clearErrorStructure();
        }
    }

    if (!fscanf(fp, "%d", &input_value)) {
        LostCommunicationHandler(STEERINGWHEEL_WRONG_INPUT, STEERINGWHEEL_WRONG_INPUT_MSG);
    }
    else {
        if (ComIF_IsSteeringWheelValueCorrect(input_value) == FALSE) {
            LostCommunicationHandler(STEERINGWHEEL_WRONG_INPUT, STEERINGWHEEL_WRONG_INPUT_MSG);
        }
        else {
            input.steeringWheel = input_value + STEERING_ANGLE_MID;
            if (error.failed == STEERINGWHEEL_WRONG_INPUT) {
                clearErrorStructure();
            }
        }
    }

    if (!fscanf(fp, "%d", &input_value) || ComIF_IsOutOfRange(input_value) == TRUE) {
        LostCommunicationHandler(DISTANCE_WRONG_INPUT, DISTANCE_WRONG_INPUT_MSG);
    }
    else {
        input.distance = input_value;
        if (error.failed == DISTANCE_WRONG_INPUT) {
            clearErrorStructure();
        }
    }

    if (!fscanf(fp, "%d", &input_value) || ComIF_IsOutOfRange(input_value) == TRUE) {
        LostCommunicationHandler(BATTERYVOLTAGE_WRONG_INPUT, BATTERYVOLTAGE_WRONG_INPUT_MSG);
    }
    else {
        input.batteryVoltage = input_value;
        if (error.failed == BATTERYVOLTAGE_WRONG_INPUT) {
            clearErrorStructure();
        }
    }
    
    /* Part of the tests */
    if(!fscanf(fp, "%s", inputTextSSMState)) {
        LostCommunicationHandler(LOST_COMMUNICATION, LOST_COMMUNICATION_MSG);
    }
    if(!fscanf(fp, "%s", inputTextLedBeep)) {
        LostCommunicationHandler(LOST_COMMUNICATION, LOST_COMMUNICATION_MSG);
    }
    inputTextParser();

    /* Input value verification */
    if (((FALSE == ComIF_IsSpeedCorrectValue())
      || (FALSE == ComIF_IsGearValueInGoodRange()))
      ||((FALSE == ComIF_IsDistanceCorrectValue())
      || (FALSE == ComIF_IsBatteryVoltageInGoodRange())))
    {
        LostCommunicationHandler(LOST_COMMUNICATION, LOST_COMMUNICATION_MSG);
    }
    else if (error.failed == LOST_COMMUNICATION) {
        clearErrorStructure();
    }


    return input;

}
