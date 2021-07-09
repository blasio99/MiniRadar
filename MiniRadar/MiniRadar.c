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
#include <time.h>

#include "MiniRadar.h"

uint8_t warning_led     = DEFAULT;      /* SET or RESET the warning led */
uint8_t warning_beep    = DEFAULT;      /* SET or RESET the warning buzzer*/
uint8_t batteryVoltage  = DEFAULT;      /* Input value, normally between 8V and 16V */
boolean waitForRead     = FALSE;        /* Wait for 1s being passed to read data */
time_t  seconds;                        /* Variable for checking the 1s reading and 5s initialization*/
INPUT   data;                           /* Input data structure */

/* Start-up function for initializing stuff */
void start_up();

/* Set warning signs if we are in a collision zone
   and the warning features are ON */
void checkAndSetLedAndBeep();

/* Print the values from the input and the ongoing states */
void printValuesAndStates();

/* If all values are 255, we enter in slepp mode, and prepare for full stop */
boolean checkIfEnteringSleepMode();

int main()
{
    /* Reading the values from the sensor*/
    char* filename = "input.txt";
    FILE* fp = fopen(filename, "r");
    
    if (fp == NULL) {
        printf("Cannot read from %s. \n", filename);
        exit(0);
    }

    /* considering the time for reading values (1s)*/
    seconds = time(NULL);
    time_t prev_seconds = seconds;

    start_up();

    /* Running the program from start-up until it enters in sleep mode*/
    while (1) {

        /* creating the input data structure */
        /* .speed, .gear, .steeringWheel*/
        
        if (time(NULL) - prev_seconds >= 1) {

            /* Reading from txt file the input data */
            data = ComIF_read_inputData(fp);
            
            /* If all values are 255, we enter in slepp mode, and prepare for full stop */
            if (checkIfEnteringSleepMode() == TRUE) break;

            /* Error checking function */
            errorHandler_MainFunction();
            
            /* Calling the system state machine changer function */
            SysStM_MainFunction();

            /* Set warning signs if we are in a collision zone
               and the warning features are ON */
            WF_WarningSigns(data);

            /* Print the values from the input and the ongoing states */
            printValuesAndStates();

            prev_seconds = time(NULL);
        }
        
    }

    fclose(fp);
    return 0;
}

void start_up() {
    setLCW_Feature_State (ACTIVE);
    setRCTA_Feature_State(ACTIVE);
}

void printValuesAndStates() {

    /* Print input values */
    printf("%d\t%d\t%d\t%d\t%d\n", data.speed, data.gear, data.steeringWheel, data.distance, data.batteryVoltage);

    /* Print led and beep states */
    printf("Led and beep: %s\n", (warning_led == WARNING_ACTIVE && warning_beep == WARNING_ACTIVE)?"ON":"OFF");
    
    /* Print System state machine state */
    char* SSM_State_Msg = "";
    if (SSM_State == SSM_INIT)   SSM_State_Msg = "SSM_INIT";
    if (SSM_State == SSM_ACTIVE) SSM_State_Msg = "SSM_ACTIVE";
    if (SSM_State == SSM_ERROR)  SSM_State_Msg = "SSM_ERROR";
    printf("SSM_State: %s\n", SSM_State_Msg);

    /* Print the state of the possible error (if it exits) */
    printf("error: %s - %s\n", (error.failed != NO_ERROR)?"True":"False", 
        (error.failed != NO_ERROR)?error.message:"NONE");

    /* Sectioning for more visible outputs */
    printf("\n---------------------------------------\n");
}

boolean checkIfEnteringSleepMode() {

    /* Stop value is UINT8_MAX == 255 in this case which means end of file */
    if (STOP_VALUE == data.distance && 
        STOP_VALUE == data.gear &&
        STOP_VALUE == data.speed && 
        STOP_VALUE == data.steeringWheel &&
        STOP_VALUE == data.batteryVoltage) {

        printf("The system enters in SLEEP Mode, then it stops working...\n");
        return TRUE;
    }
    
    return FALSE;
}