/*
*   File:           testMain.c
*
*   Project name:   Mini Radar project
*   Author:         Benedek Balazs
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "testMain.h"

uint8_t tests_run = DEFAULT;
uint8_t tests_failed = DEFAULT;

int assert_helper() {
    _assert(((SSM_State == test.SSM_State) && (warning_led == test.LedBeepState)));
    return 0;
}

int verify_helper() {
    _verify(assert_helper);
    return 0;
}

void testMain() {

    int result = verify_helper();

    if (result == 0) {
        printf("[TEST %d]\tPASSED\n", tests_run);
    }
    else {
        printf("[TEST %d]\tFAILED\n", tests_run);
    }

}