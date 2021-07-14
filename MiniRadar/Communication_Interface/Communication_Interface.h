/*
*   File:           Communication_Interface.h
*
*   Project name:   Mini Radar project
*   Author:         Benedek Balazs
*
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "../Constants.h"
#include "../Error_Handler/Error_Handler.h"

extern time_t seconds;
extern ErrorStructure error;
extern testStructure test;

void LostCommunicationHandler(Error error, char* error_message);
INPUT ComIF_read_inputData(FILE* fp);