#include "PE_Types.h"
#include "SerialCommand.h" //nice lib from Stefan Rado, https://github.com/kroimon/Arduino-SerialCommand#include "AccelStepper.h"
#include "CTypes.h"

//Pen Stepper
#define STEP2_PIN (1)	/*D5 - PTA1*/
#define DIR2_PIN (0)		/*D4 - PTC8*/
#define enablePenMotor 6
#define PEN_MICRO_STEP 16 /*MicrostepMode, only 1,2,4,8,16 allowed, because of Integer-Math in this Sketch*/

//Rotational Stepper
#define STEP1_PIN (3) /*D7 - PTC4*/
#define DIR1_PIN (2)		/*D6 - PTC3*/
#define enableRotMotor 9
#define ROT_MICRO_STEP 16  /*MicrostepMode, only 1,2,4,8,16 allowed, because of Integer-Math in this Sketch */

//Servo
#define PrgButton 2 /*optional Pushbutton between Pin and Ground to use certain functions with Eggbot-Inkscape extension*/

extern SerialCommand SCmd;
extern StepperMotor rotMotor;
extern StepperMotor penMotor;

extern UART_Desc deviceData;

extern int penMin;
extern int penMax;
extern int penUpPos;
extern int penDownPos;
extern int servoRateUp;
extern int servoRateDown;
extern long rotStepError;
extern long penStepError;
extern int penState;
extern volatile uint32_t nodeCount;
extern unsigned int layer;
extern bool prgButtonState;
extern uint8_t rotStepCorrection;
extern uint8_t penStepCorrection;
extern float rotSpeed;
extern float penSpeed;
