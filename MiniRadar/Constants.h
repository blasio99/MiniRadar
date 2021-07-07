/*
*   File:           Constants.h
*
*   Project name:   Mini Radar project
*   Author:         Benedek Balazs
*
*/

/* TRUE or FALSE */
#define		TRUE				1
#define		FALSE				0

/* States for featurese */
#define		ACTIVE				1
#define		PASSIVE				0		/* At start-up or in case taht System State Machine has ERROR state */

/* Possible states for the GEAR */
#define		NEUTRAL				0 
#define		FORWARD				1
#define		REVERSE				2
#define		PARKED				3

/* ERROR MESSAGES */
#define		UNDER_VOLTAGE		0		/* The battery voltage is under 8 volts */
#define		OVER_VOLTAGE		1		/* The battery voltage is over 16 volts */
#define		LOST_COMMUNICATION	2		/* The message does not arrive in 3 seconds (normally, the messages arrive in every 1 sec) */

/* Error handling states */
#define		NOT_YET_PERFOMED	0
#define		FAILED				1
#define		PASSED				2		/* When the error is no longer existing */