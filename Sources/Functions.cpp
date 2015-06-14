#ifdef __cplusplus
extern "C" {
#endif

#include "WAIT1.h"
#include "EggBot.h"
#include "GPIOEN.h"
#include "PWMPenServo.h"

#ifdef __cplusplus
}
#endif

#include "Functions.h"

#include "AS1.h"
#include "stdlib.h"
//#include "stdio.h"

//#define atoi(a) (0)
#define delay(a) WAIT1_Waitus(a)
#define digitalWrite(a,b) ;
#define abs(a) (a)

void SendChar(unsigned char ch, UART_Desc *desc)
{
  desc->isSent = FALSE; /* this will be set to 1 once the block has been sent */
  while (AS1_SendBlock (desc->handle, (LDD_TData*) &ch, 1) != ERR_OK)
  {
  } /* Send char */
  while (!desc->isSent)
  {
  } /* wait until we get the green flag from the TX interrupt */
}

void SendString(const unsigned char *str, UART_Desc *desc)
{
  while (*str != '\0')
  {
    SendChar (*str++, desc);
  }
}

void queryPen()
{
  if (penState == penUpPos)
  {
    //  XSerial.print("1\r\n");
    SendString ((unsigned char*) "1\r\n", &deviceData);
  }
  else
  {
    //  XSerial.print("0\r\n");
    SendString ((unsigned char*) "0\r\n", &deviceData);
  }
  sendAck ();
}

void queryButton()
{
  char prgButtonStateString[3];
//	(void)sprintf(prgButtonStateString, "%d", prgButtonState);

  prgButtonStateString[0] = '0' + prgButtonState;
  prgButtonStateString[1] = '\r';
  prgButtonStateString[2] = '\n';
  //	XSerial.print(String(prgButtonState) + "\r\n");
  SendString ((unsigned char*) prgButtonStateString, &deviceData);
  prgButtonState = 0;
  sendAck ();
}

void queryLayer()
{
//	XSerial.print(String(layer) + "\r\n");
  sendAck ();
}

void setLayer()
{
  uint32_t value = 0;
  char *arg1;
  arg1 = SCmd.next ();
  if (arg1 != NULL)
  {
    value = atoi (arg1);
    layer = value;
    sendAck ();
  }
  else
    sendError ();
}

void queryNodeCount()
{
//	XSerial.print(String(nodeCount) + "\r\n");
  sendAck ();

}

void setNodeCount()
{
  uint32_t value = 0;
  char *arg1;
  arg1 = SCmd.next ();
  if (arg1 != NULL)
  {
    value = atoi (arg1);
    nodeCount = value;
    sendAck ();
  }
  else
    sendError ();
}

void nodeCountIncrement()
{
  nodeCount++;
  sendAck ();
}

void nodeCountDecrement()
{
  nodeCount--;
  sendAck ();
}

void stepperMove()
{
  uint16_t duration = 0;  //in ms
  int penStepsEBB = 0;  //Pen
  int rotStepsEBB = 0;  //Rot
  char *arg1;
  char *arg2;
  char *arg3;

  arg1 = SCmd.next ();
  arg2 = SCmd.next ();
  arg3 = SCmd.next ();

  if (arg1 != '\0')
  {
    duration = atoi (arg1);
  }
  if (arg2 != '\0')
  {
    penStepsEBB = atoi (arg2);
  }
  if (arg3 != '\0')
  {
    rotStepsEBB = atoi (arg3);

    if ((penStepsEBB == 0) && (rotStepsEBB == 0))
    {
      delay(duration);
      sendAck ();
    }
    if ((penStepsEBB != 0) || (rotStepsEBB != 0))
    {
//################### Move-Code Start ############################################################
      if ((1 == rotStepCorrection) && (1 == penStepCorrection))
      {  // if coordinatessystems are identical
         //set Coordinates and Speed
        AccelStepper_move (&rotMotor, rotStepsEBB);
        AccelStepper_setSpeed (&rotMotor, abs((float ) rotStepsEBB * (float ) 1000 / (float ) duration));

        AccelStepper_move (&penMotor, penStepsEBB);
        AccelStepper_setSpeed (&penMotor, abs((float ) penStepsEBB * (float ) 1000 / (float ) duration));
      }
      else
      {
        //incoming EBB-Steps will be multiplied by 16, then Integer-maths is done, result will be divided by 16
        // This make thinks here really complicated, but floating point-math kills performance and memory, believe me... I tried...
        long rotSteps = ((long) rotStepsEBB * 16 / rotStepCorrection)
            + (long) rotStepError;	//correct incoming EBB-Steps to our microstep-Setting and multiply  by 16 to avoid floatingpoint...
        long penSteps = ((long) penStepsEBB * 16 / penStepCorrection)
            + (long) penStepError;
        int rotStepsToGo = (int) (rotSteps / 16);  //Calc Steps to go, which are possible on our machine
        int penStepsToGo = (int) (penSteps / 16);
        rotStepError = (long) rotSteps - ((long) rotStepsToGo * (long) 16);  // calc Position-Error, if there is one
        penStepError = (long) penSteps - ((long) penStepsToGo * (long) 16);
        long temp_rotSpeed = ((long) rotStepsToGo * (long) 1000
            / (long) duration);  // calc Speed in Integer Math
        long temp_penSpeed = ((long) penStepsToGo * (long) 1000
            / (long) duration);
        float rotSpeed = (float) abs(temp_rotSpeed);	// type cast
        float penSpeed = (float) abs(temp_penSpeed);
        //set Coordinates and Speed
        AccelStepper_move (&rotMotor, rotStepsToGo);
        AccelStepper_setSpeed (&rotMotor, rotSpeed);
        AccelStepper_move (&penMotor, penStepsToGo);
        AccelStepper_setSpeed (&penMotor, penSpeed);
      }

      //Start Move
      while (AccelStepper_distanceToGo (&penMotor)
          || AccelStepper_distanceToGo (&rotMotor))
      {
        AccelStepper_runSpeedToPosition (&penMotor);
        AccelStepper_runSpeedToPosition (&rotMotor);
      }
//################### Move-Code End ############################################################
      sendAck ();     //report Mission completed
    }
  }
  else
    sendError ();
}

void setPen()
{
  int cmd;
  int value;
  char *arg;

  arg = SCmd.next ();
  if (arg != NULL)
  {
    cmd = atoi (arg);
    switch (cmd)
      {
      case 0:
        penState = penDownPos;
        PWMPenServo_SetDutyUS(penState); /* Up */
        break;

      case 1:
        penState = penUpPos;
        PWMPenServo_SetDutyUS(penState); /* Down */
        break;

      default:
        sendError ();
        break;
      }
  }
  char *val;
  val = SCmd.next ();
  if (val != NULL)
  {
    value = atoi (val);
    delay(value);
    sendAck ();
  }
  else if (val == NULL && arg != NULL)
  {
    delay(50);
    sendAck ();
  }
  else if (val == NULL && arg == NULL)
  {
    sendError ();
  }
}

void togglePen()
{
  int value;
  char *arg;

  arg = SCmd.next ();
  if (arg != NULL)
    value = atoi (arg);

  if (penState == penUpPos)
  {
    penState = penDownPos;
  }
  else
  {
    penState = penUpPos;
  }

  PWMPenServo_SetDutyUS(penState); /* Down */
  WAIT1_Waitms(250);
  sendAck ();
}

void enableMotors()
{
  int cmd;
  int value;
  char *arg;
  char *val;

  arg = SCmd.next ();
  if (arg != NULL)
    cmd = atoi (arg);

  val = SCmd.next ();
  if (val != NULL)
    value = atoi (val);

  //values parsed
  if (arg != NULL)
  {
    switch (cmd)
    {
      case 0:
        GPIOEN_SetVal();
        sendAck ();
        break;
      case 1:
        GPIOEN_ClrVal();
        sendAck ();
        break;
      default:
        sendError ();
        break;
    }
  }
}

void stepperModeConfigure()
{
  int cmd;
  int value;
  char* arg;
  char* val;

  arg = SCmd.next ();
  if (arg != '\0')
    cmd = atoi (arg);

  val = SCmd.next ();
  if (val != '\0')
    value = atoi (val);

  if ((arg != '\0') && (val != '\0'))
  {
    switch (cmd)
      {
        case 4:
          penUpPos = ((value/240 - 25) * 1000) / 100 + 1000;  // transformation from EBB to PWM-Servo
          sendAck ();
          break;
        case 5:
          penDownPos = ((value/240 - 25) * 1000) / 100 + 1000;  // transformation from EBB to PWM-Servo
          sendAck ();
          break;
        case 6:  //rotMin=value;    ignored
          sendAck ();
          break;
        case 7:  //rotMax=value;    ignored
          sendAck ();
          break;
        case 11:
          servoRateUp = value;
          sendAck ();
          break;
        case 12:
          servoRateDown = value;
          sendAck ();
          break;
        default:
          sendError ();
          break;
      }
  }
}

void sendVersion()
{
//	XSerial.print(initSting);
//	XSerial.print("\r\n");
  SendString ((unsigned char*) "EBBv13_and_above from FRDM_Egg_Bot\r\n", &deviceData);
}

void unrecognized(const char* command)
{
  sendError ();
}

void ignore()
{
  sendAck ();
}

void initHardware()
{
  AccelStepper_setMaxSpeed (&rotMotor, 500.0);
  AccelStepper_setAcceleration (&rotMotor, 10.0);
  AccelStepper_setMaxSpeed (&penMotor, 500.0);
  AccelStepper_setAcceleration (&penMotor, 10.0);
}

void inline sendAck()
{
//	XSerial.print("OK\r\n");
  SendString ((unsigned char*) "OK\r\n", &deviceData);
}

void inline sendError()
{
//	XSerial.print("unknown CMD\r\n");
  SendString ((unsigned char*) "unknown CMD\r\n", &deviceData);
}
