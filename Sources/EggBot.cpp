//#include "PE_Types.h"
#include "AS1.h"
#include "CTypes.h"
#include "WAIT1.h"

#ifdef __cplusplus
extern "C" {
#endif
#include "RxBuf.h"

#include "GPIOPenDir.h"
#include "GPIOPenStep.h"
#include "PWMPenServo.h"
#include "GPIOEggDir.h"
#include "GPIOEggStep.h"
#include "GPIOEN.h"

#include "FreeRunning.h"
#include "AccelStepper.h"

#ifdef __cplusplus
}
#endif

#include "EggBot.h"
#include "SerialCommand.h" //nice lib from Stefan Rado, https://github.com/kroimon/Arduino-SerialCommand#include "Functions.h"SerialCommand SCmd;StepperMotor rotMotor;
StepperMotor penMotor;

UART_Desc deviceData;

// Variables... be careful, by messing around here, evrything has a reason and crossrelations...
int penMin = 0;
int penMax = 0;
int penUpPos = 1600;  //can be overwritten from EBB-Command SC
int penDownPos = 1400;  //can be overwritten from EBB-Command SC
int servoRateUp = 0;  //from EBB-Protocol not implemented on machine-side
int servoRateDown = 0;  //from EBB-Protocol not implemented on machine-side
long rotStepError = 0;
long penStepError = 0;
int penState = penUpPos;
volatile uint32_t nodeCount = 0;
unsigned int layer = 0;
bool prgButtonState = 0;
uint8_t rotStepCorrection = 16 / ROT_MICRO_STEP;  //Divide EBB-Coordinates by this factor to get EGGduino-Steps
uint8_t penStepCorrection = 16 / PEN_MICRO_STEP;  //Divide EBB-Coordinates by this factor to get EGGduino-Steps
float rotSpeed = 0;
float penSpeed = 0;  // these are local variables for Function SteppermotorMove-Command, but for performance-reasons it will be initialized here

static void Init(void)
{
  /* initialize struct fields */
  deviceData.handle = AS1_Init (&deviceData);
  deviceData.isSent = FALSE;
  deviceData.rxChar = '\0';
  deviceData.rxPutFct = RxBuf_Put;

  /* set up to receive RX into input buffer */
  //  RxBuf_Init(); /* initialize RX buffer */
  /* Set up ReceiveBlock() with a single byte buffer. We will be called in OnBlockReceived() event. */
  while (AS1_ReceiveBlock (deviceData.handle, (LDD_TData *) &deviceData.rxChar,
                           sizeof(deviceData.rxChar)) != ERR_OK)
  {
  } /* initial kick off for receiving data */


  AccelStepper_Init (&rotMotor, STEP1_PIN, DIR1_PIN);
  AccelStepper_Init (&penMotor, STEP2_PIN, DIR2_PIN);

  /* Init the HW */
  initHardware ();
}


extern "C" void APP_Run(void);
void APP_Run(void)
{
  Init ();
  SCmd.Init ();

  /** Startup delay */
  WAIT1_Waitms(500);

  /** Wait for commands */
  for (;;)
  {
    if (RxBuf_NofElements () != 0)
    {
      SCmd.readSerial ();
    }
  }
}
