/*
*   File:           testMain.h
*
*   Project name:   Mini Radar project
*   Author:         Benedek Balazs
*
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "Constants.h"

extern  uint8_t         tests_run;       /* Number of tests runned */
extern  uint8_t         tests_failed;    /* Number of tests failed */

extern  uint8_t         warning_led;
extern  uint8_t         warning_beep;
extern  SysStMState     SSM_State;

extern  testStructure   test;
extern  INPUT           input; 
extern  ErrorStructure  error;

/* Fail macro to print error message */
#define FAIL() \
        do \
        { \
            printf("[FAIL] in %s\n", error.message); \
            printf("\tExpected SSM value: %d\n", test.SSM_State); \
            printf("\tResulted SSM value: %d\n", SSM_State); \
            printf("\tExpected LED value: %d\n", test.LedBeepState); \
            printf("\tResulted LED value: %d\n", warning_led); \
        } while (0);

/* Assert test macro */
#define _assert(test) \
        do \
        { \
            if (!(test)) \
            { \
                FAIL(); \
                ++ tests_failed; \
                return TRUE; \
             } \
        } while(0)

/* Verify test macro */
#define _verify(test) \
        do \
        { \
            int func = test(); \
            ++ tests_run; \
            if(func) { return func; } \
        } while(0)

void testMain();