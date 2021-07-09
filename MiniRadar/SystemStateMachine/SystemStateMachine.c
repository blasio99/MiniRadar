/*
*   File:           SystemStateMachine.c
*
*   Project name:   Mini Radar project
*   Author:         Benedek Balazs
*
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "SystemStateMachine.h"

boolean waitForInit = TRUE;
SysStMState SSM_State = SSM_INIT;

void SysStM_MainFunction() {

	waitForInit = (SSM_State == SSM_INIT && time(NULL) - seconds <= 5) ? TRUE : FALSE;

	if (waitForInit == FALSE) {

		switch (SSM_State) {

		case SSM_INIT: {
			if (error.failed != NO_ERROR)
				SSM_State = SSM_ERROR;
			else 
				SSM_State = SSM_ACTIVE;
		}
		break;
		case SSM_ACTIVE: {
			if (error.failed != NO_ERROR)
				SSM_State = SSM_ERROR;
		}
		break;
		case SSM_ERROR: {
			if (error.failed == NO_ERROR)
				SSM_State = SSM_ACTIVE;
		}
		break;
		default:
			break;
		}
	}


}


