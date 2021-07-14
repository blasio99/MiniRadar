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

INPUT input = { DEFAULT, DEFAULT, DEFAULT, DEFAULT, DEFAULT };

/* TEST variables */
char inputTextLedBeep  [LEDBEEPSTATE_LENGTH];
char inputTextSSMState [SSMSTATE_LENGTH];

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
    if (STR_EQUAL == strcmp(inputTextSSMState, SSM_ACTIVE_TEXT)) {
        test.SSM_State = SSM_ACTIVE;
    }
    else if (STR_EQUAL == strcmp(inputTextSSMState, SSM_INIT_TEXT)) {
        test.SSM_State = SSM_INIT;
    }
    else if (STR_EQUAL == strcmp(inputTextSSMState, SSM_ERROR_TEXT)) {
        test.SSM_State = SSM_ERROR;
    }
    else {
        test.SSM_State = SSM_NO_STATE;
    }

    /* We do the same with the second test input */
    if (STR_EQUAL == strcmp(inputTextLedBeep, OFF_TEXT)) {
        test.LedBeepState = WARNING_INACTIVE;
    }
    else if (STR_EQUAL == strcmp(inputTextLedBeep, ON_TEXT)) {
        test.LedBeepState = WARNING_ACTIVE;
    }
    else {
        test.LedBeepState = LEDBEEP_NO_STATE;
    }

    memset(inputTextSSMState, DEFAULT, strlen(inputTextSSMState));
    memset(inputTextLedBeep,  DEFAULT, strlen(inputTextLedBeep ));

}

INPUT ComIF_read_inputData(FILE* fp) {

    int input_value;
    
    /* Read input values from the given file as parameter*/
    if (!fscanf(fp, "%d", &input_value) || ComIF_IsOutOfRange(input_value) == TRUE) {
        LostCommunicationHandler(SPEED_WRONG_INPUT, SPEED_WRONG_INPUT_MSG);
    }
    else {
        input.speed = (uint8_t)input_value;
        if (SPEED_WRONG_INPUT == error.failed) {
            clearErrorStructure();
        }
    }

    if (!fscanf(fp, "%d", &input_value) || (ComIF_IsOutOfRange(input_value) == TRUE)) {
        LostCommunicationHandler(GEAR_WRONG_INPUT, GEAR_WRONG_INPUT_MSG);
    }
    else {
        input.gear = (uint8_t)input_value;
        if (GEAR_WRONG_INPUT == error.failed) {
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
            input.steeringWheel = (uint8_t)(input_value + STEERING_ANGLE_MID);
            if (STEERINGWHEEL_WRONG_INPUT == error.failed) {
                clearErrorStructure();
            }
        }
    }

    if (!fscanf(fp, "%d", &input_value) || ComIF_IsOutOfRange(input_value) == TRUE) {
        LostCommunicationHandler(DISTANCE_WRONG_INPUT, DISTANCE_WRONG_INPUT_MSG);
    }
    else {
        input.distance = (uint8_t)input_value;
        if (DISTANCE_WRONG_INPUT == error.failed) {
            clearErrorStructure();
        }
    }

    if (!fscanf(fp, "%d", &input_value) || ComIF_IsOutOfRange(input_value) == TRUE) {
        LostCommunicationHandler(BATTERYVOLTAGE_WRONG_INPUT, BATTERYVOLTAGE_WRONG_INPUT_MSG);
    }
    else {
        input.batteryVoltage = (uint8_t)input_value;
        if (BATTERYVOLTAGE_WRONG_INPUT == error.failed) {
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
    else if (LOST_COMMUNICATION == error.failed) {
        clearErrorStructure();
    }

    return input;
}
