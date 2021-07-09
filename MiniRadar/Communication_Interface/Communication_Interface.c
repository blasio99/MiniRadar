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

#include "Communication_Interface.h"

time_t secondsForRead;
INPUT input = { DEFAULT, DEFAULT, DEFAULT, DEFAULT, DEFAULT };

void LostCommunicationHandler(Error error_type, char* error_message) {
    error.failed        = error_type;
    error.errorState    = FAILED;
    error.message       = error_message;
}

boolean ComIF_IsNegativeNumber(int value) {
    return (value < 0);
}

boolean ComIF_IsSpeedCorrectValue() {
    return (MIN_SPEED <= input.speed && input.speed <= MAX_SPEED);
}


boolean ComIF_AreGearValuesInGoodRange() {
    return (GEAR_MIN_VALUE <= input.gear && input.gear <= GEAR_MAX_VALUE);
}

boolean ComIF_IsSteeringWheelValueCorrect() {
    return((input.steeringWheel + STEERING_ANGLE_MID) >= STEERING_ANGLE_MIN
        && (input.steeringWheel + STEERING_ANGLE_MID) <= STEERING_ANGLE_MAX);
}

boolean ComIF_IsDistanceCorrectValue() {
    return (MIN_DISTANCE <= input.distance && input.distance <= MAX_DISTANCE);
}

boolean ComIF_IsBatteryVoltageInGoodRange() {
    return (DEFAULT <= input.batteryVoltage && input.batteryVoltage <= STOP_VALUE);
}

INPUT ComIF_read_inputData(FILE* fp) {

    int input_value;
    /* Read input values from the given file as parameter*/
    if (!fscanf(fp, "%d", &input_value) || ComIF_IsNegativeNumber(input_value) == TRUE)
        LostCommunicationHandler(SPEED_WRONG_INPUT, SPEED_WRONG_INPUT_MSG);
    else {
        input.speed = input_value;
        if (error.failed == SPEED_WRONG_INPUT)
            clearErrorStructure();
    }

    if (!fscanf(fp, "%d", &input_value) || ComIF_IsNegativeNumber(input_value) == TRUE)
        LostCommunicationHandler(GEAR_WRONG_INPUT, GEAR_WRONG_INPUT_MSG);
    else {
        input.gear = input_value;
        if (error.failed == GEAR_WRONG_INPUT)
            clearErrorStructure();
    }

    if (!fscanf(fp, "%d", &input_value) || ComIF_IsNegativeNumber(input_value) == TRUE)
        LostCommunicationHandler(DISTANCE_WRONG_INPUT, STEERINGWHEEL_WRONG_INPUT_MSG);
    else {
        input.steeringWheel = input_value;
        if (error.failed == STEERINGWHEEL_WRONG_INPUT)
            clearErrorStructure();
    }

    if (!fscanf(fp, "%d", &input_value) || ComIF_IsNegativeNumber(input_value) == TRUE)
        LostCommunicationHandler(DISTANCE_WRONG_INPUT, DISTANCE_WRONG_INPUT_MSG);
    else {
        input.distance = input_value;
        if (error.failed == DISTANCE_WRONG_INPUT)
            clearErrorStructure();
    }

    if (!fscanf(fp, "%d", &input_value) || ComIF_IsNegativeNumber(input_value) == TRUE)
        LostCommunicationHandler(BATTERYVOLTAGE_WRONG_INPUT, BATTERYVOLTAGE_WRONG_INPUT_MSG);
    else {
        input.batteryVoltage = input_value;
        if (error.failed == BATTERYVOLTAGE_WRONG_INPUT)
            clearErrorStructure();
    }
    

    if (!ComIF_IsSpeedCorrectValue() ||
        !ComIF_AreGearValuesInGoodRange() ||
        !ComIF_IsSteeringWheelValueCorrect() ||
        !ComIF_IsDistanceCorrectValue() ||
        !ComIF_IsBatteryVoltageInGoodRange())
    {
        LostCommunicationHandler(LOST_COMMUNICATION, LOST_COMMUNICATION_MSG);
    }


    return input;

}
