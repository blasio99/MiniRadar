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

/* Constants */
#define		DEFAULT				0

/* Program helpers */
#define		STOP_VALUE			255
#define		MIN_SPEED			0
#define		MAX_SPEED			255
#define		STEERING_ANGLE_MIN	0
#define		STEERING_ANGLE_MAX	90
#define		STEERING_ANGLE_MID	45
#define		MAX_DISTANCE		255
#define		MIN_DISTANCE		0

/* Warning active or inactive */
#define		WARNING_ACTIVE		1
#define		WARNING_INACTIVE	0

/* States for features */
#define		ACTIVE				1
#define		PASSIVE				0			/* At start-up or in case taht System State Machine has ERROR state */

/* System State Machine values*/
#define		SSM_INIT			0
#define		SSM_ACTIVE			1
#define		SSM_ERROR			2

/* Possible states for the GEAR */
#define		NEUTRAL				0 
#define		FORWARD				1
#define		REVERSE				2
#define		PARKED				3
#define		GEAR_MAX_VALUE		4
#define		GEAR_MIN_VALUE		0

/* ERROR MESSAGES */
#define		NO_ERROR			0			/* The program is not FAILED */
#define		UNDER_VOLTAGE		1			/* The battery voltage is under 8 volts */
#define		OVER_VOLTAGE		2			/* The battery voltage is over 16 volts */
#define		LOST_COMMUNICATION	3			/* The message does not arrive in 3 seconds (normally, the messages arrive in every 1 sec) */
#define		SPEED_WRONG_INPUT	4
#define		GEAR_WRONG_INPUT	5
#define		STEERINGWHEEL_WRONG_INPUT	6
#define		DISTANCE_WRONG_INPUT		7
#define		BATTERYVOLTAGE_WRONG_INPUT	8

#define		NO_ERROR_MSG					"[PASSED] There is no error"
#define		UNDER_VOLTAGE_MSG				"[ERROR] Under voltage on battery"
#define		OVER_VOLTAGE_MSG				"[ERROR] Over voltage on battery"
#define		LOST_COMMUNICATION_MSG			"[ERROR] We lost the communication with the sensors"
#define		SPEED_WRONG_INPUT_MSG			"[ERROR] Incorrect input data from SPEED"
#define		GEAR_WRONG_INPUT_MSG			"[ERROR] Incorrect input data from GEAR"
#define		STEERINGWHEEL_WRONG_INPUT_MSG	"[ERROR] Incorrect input data from GEAR"
#define		DISTANCE_WRONG_INPUT_MSG		"[ERROR] Incorrect input data from GEAR"
#define		BATTERYVOLTAGE_WRONG_INPUT_MSG	"[ERROR] Incorrect input data from GEAR"

/* Error handling states */
#define		NOT_YET_PERFOMED	0
#define		PASSED				1			/* When the error is no longer existing */
#define		FAILED				2	
#define		ERROR_STR_SIZE		255			/* Maximum length for error message */

/* RCTA values */
#define		RCTA_COLL_DISTANCE	4			/* In RCTA mode the collsion zone is at distance of 20m */
#define		RCTA_SPEED			10

/* LCW values*/
#define		LCW_COLL_DISTANCE	20			/* In RCTA mode the collsion zone is at distance of 4m */
#define		LCW_SPEED			20		
#define		LCW_STEERING_ANGLE	6

/* BATTERY VOLTAGE range values */
#define		BATTERY_VOLTAGE_MIN 8			/* Minimum voltage: 8V  */
#define		BATTERY_VOLTAGE_MAX 16			/* Maximum voltage: 16V */


#ifndef INPUT_HEADER
#define INPUT_HEADER

typedef struct _input_data {
	uint8_t speed;							/* Input value for speed */
	uint8_t gear;							/* Input value for gear */
	uint8_t steeringWheel;					/* Input value for angle of steering wheel */
	uint8_t distance;						/* Input value for distance of objects */
	uint8_t batteryVoltage;					/* Input value for battery voltage */
}INPUT;

#endif

typedef uint8_t FeatureState;
typedef uint8_t SysStMState;
typedef uint8_t Error;
typedef uint8_t ErrorState;

#ifndef ERRORSTATE
#define ERRORSTATE
typedef struct error_state {
	Error failed;
	ErrorState errorState;
	char *message;
}ErrorStructure;
#endif


#ifndef boolean
typedef uint8_t boolean;
#endif

extern uint8_t warning_led;
extern uint8_t warning_beep;

extern time_t seconds;

