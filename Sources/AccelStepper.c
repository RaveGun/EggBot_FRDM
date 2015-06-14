// AccelStepper.cpp
//
// Copyright (C) 2009-2013 Mike McCauley
// $Id: AccelStepper.cpp,v 1.19 2014/10/31 06:05:27 mikem Exp mikem $

#ifdef __cplusplus
extern "C"
{
#endif

#include "PE_Types.h"

#include "GPIOPenDir.h"
#include "GPIOPenStep.h"
#include "PWMPenServo.h"
#include "GPIOEggDir.h"
#include "GPIOEggStep.h"
#include "WAIT1.h"
#include "FreeRunning.h"

#include "AccelStepper.h"

#ifdef __cplusplus
}
#endif


#define ONE_SECOND_FLOAT (1000000.0)


#define pinMode(a,b)
#define sqrt(a) (a/2)

#define HIGH (1)
#define LOW (0)
#define delayMicroseconds(a) WAIT1_Waitus(a)

uint32 fabs(float a)
{
  if (a < 0)
  {
    return ((uint32) (-a));
  }
  else
  {
    return ((uint32) (a));
  }
}

uint32 micros(void)
{
  FreeRunning_TTimerValue lReturn;
  FreeRunning_GetCounterValue (&lReturn);

  return ((uint32) lReturn);
}

float constrain(float x, float a, float b)
{
  if (x < a)
  {
    return (a);
  }
  else
  {
    if (x > b)
    {
      return (b);
    }
    else
    {
      return (x);
    }
  }
}
float max(float a, float b)
{
  if (a > b)
    return (a);
  else
    return (b);
}

void digitalWrite(uint8 a, bool b)
{
  switch (a)
    {
    case 0:
      GPIOPenDir_PutVal(b);
      break;
    case 1:
      GPIOPenStep_PutVal(b);
      break;
    case 2:
      GPIOEggDir_PutVal(b);
      break;
    case 3:
      GPIOEggStep_PutVal(b);
      break;
    default:
      break;
    }
}

#if 0
// Some debugging assistance
void dump(uint8_t* p, int l)
{
  int i;

  for (i = 0; i < l; i++)
  {
    Serial.print(p[i], HEX);
    Serial.print(" ");
  }
  Serial.println("");
}
#endif

void AccelStepper_moveTo(StepperMotor * motor, long absolute)
{
  if (motor->_targetPos != absolute)
  {
    motor->_targetPos = absolute;
    AccelStepper_computeNewSpeed (motor);
    // compute new n?
  }
}

void AccelStepper_move(StepperMotor * motor, long relative)
{
  AccelStepper_moveTo (motor, motor->_currentPos + relative);
}

// Implements steps according to the current step interval
// You must call this at least once per step
// returns true if a step occurred
bool AccelStepper_runSpeed(StepperMotor * motor)
{
  // Dont do anything unless we actually have a step interval
  if (!motor->_stepInterval)
    return (FALSE);

  unsigned long time = (4000000000 - micros ());
  unsigned long nextStepTime = motor->_lastStepTime + motor->_stepInterval;

  // Gymnastics to detect wrapping of either the nextStepTime and/or the current time
  if (((nextStepTime >= motor->_lastStepTime) && ((time >= nextStepTime) || (time < motor->_lastStepTime)))
      || ((nextStepTime < motor->_lastStepTime) && ((time >= nextStepTime) && (time < motor->_lastStepTime))))

  {
    if (motor->_direction == DIRECTION_CW)
    {
      // Clockwise
      motor->_currentPos += 1;
    }
    else
    {
      // Counterclockwise
      motor->_currentPos -= 1;
    }
    AccelStepper_step (motor);

    motor->_lastStepTime = time;
    return (TRUE);
  }
  else
  {
    return (FALSE);
  }
}

long AccelStepper_distanceToGo(StepperMotor * motor)
{
  return motor->_targetPos - motor->_currentPos;
}

long AccelStepper_targetPosition(StepperMotor * motor)
{
  return motor->_targetPos;
}

long AccelStepper_currentPosition(StepperMotor * motor)
{
  return motor->_currentPos;
}

// Useful during initialisations or after initial positioning
// Sets speed to 0
void AccelStepper_setCurrentPosition(StepperMotor * motor, long position)
{
  motor->_targetPos = motor->_currentPos = position;
  motor->_n = 0;
  motor->_stepInterval = 0;
}

void AccelStepper_computeNewSpeed(StepperMotor * motor)
{
  long distanceTo = AccelStepper_distanceToGo (motor);  // +ve is clockwise from curent location

  long stepsToStop = (long) ((motor->_speed * motor->_speed) / (2.0 * motor->_acceleration));  // Equation 16

  if (distanceTo == 0 && stepsToStop <= 1)
  {
    // We are at the target and its time to stop
    motor->_stepInterval = 0;
    motor->_speed = 0.0;
    motor->_n = 0;
    return;
  }

  if (distanceTo > 0)
  {
    // We are anticlockwise from the target
    // Need to go clockwise from here, maybe decelerate now
    if (motor->_n > 0)
    {
      // Currently accelerating, need to decel now? Or maybe going the wrong way?
      if ((stepsToStop >= distanceTo) || motor->_direction == DIRECTION_CCW)
        motor->_n = -stepsToStop;  // Start deceleration
    }
    else if (motor->_n < 0)
    {
      // Currently decelerating, need to accel again?
      if ((stepsToStop < distanceTo) && motor->_direction == DIRECTION_CW)
        motor->_n = -motor->_n;  // Start accceleration
    }
  }
  else if (distanceTo < 0)
  {
    // We are clockwise from the target
    // Need to go anticlockwise from here, maybe decelerate
    if (motor->_n > 0)
    {
      // Currently accelerating, need to decel now? Or maybe going the wrong way?
      if ((stepsToStop >= -distanceTo) || motor->_direction == DIRECTION_CW)
        motor->_n = -stepsToStop;  // Start deceleration
    }
    else if (motor->_n < 0)
    {
      // Currently decelerating, need to accel again?
      if ((stepsToStop < -distanceTo) && motor->_direction == DIRECTION_CCW)
        motor->_n = -motor->_n;  // Start accceleration
    }
  }

  // Need to accelerate or decelerate
  if (motor->_n == 0)
  {
    // First step from stopped
    motor->_cn = motor->_c0;
    motor->_direction = (distanceTo > 0) ? DIRECTION_CW : DIRECTION_CCW;
  }
  else
  {
    // Subsequent step. Works for accel (n is +_ve) and decel (n is -ve).
    motor->_cn = motor->_cn - ((2.0 * motor->_cn) / ((4.0 * motor->_n) + 1));  // Equation 13
    motor->_cn = max (motor->_cn, motor->_cmin);
  }
  motor->_n++;
  motor->_stepInterval = motor->_cn;
  motor->_speed = ONE_SECOND_FLOAT / motor->_cn;
  if (motor->_direction == DIRECTION_CCW)
    motor->_speed = -motor->_speed;

#if 0
  Serial.println(_speed);
  Serial.println(_acceleration);
  Serial.println(_cn);
  Serial.println(_c0);
  Serial.println(_n);
  Serial.println(_stepInterval);
  Serial.println(distanceTo);
  Serial.println(stepsToStop);
  Serial.println("-----");
#endif
}

// Run the motor to implement speed and acceleration in order to proceed to the target position
// You must call this at least once per step, preferably in your main loop
// If the motor is in the desired position, the cost is very small
// returns true if the motor is still running to the target position.
bool AccelStepper_run(StepperMotor * motor)
{
  if (AccelStepper_runSpeed (motor))
    AccelStepper_computeNewSpeed (motor);
  return motor->_speed != 0.0 || AccelStepper_distanceToGo (motor) != 0;
}

void AccelStepper_Init(StepperMotor * motor, uint8_t pin1, uint8_t pin2)
{
  motor->_currentPos = 0;
  motor->_targetPos = 0;
  motor->_speed = 0.0;
  motor->_maxSpeed = 10.0;
  motor->_acceleration = 0.0;
  motor->_sqrt_twoa = 1.0;
  motor->_stepInterval = 0;
  motor->_minPulseWidth = 50;
  motor->_enablePin = 0xff;
  motor->_lastStepTime = 0;
  motor->_pin[0] = pin1;
  motor->_pin[1] = pin2;

  // NEW
  motor->_n = 0;
  motor->_c0 = 0.0;
  motor->_cn = 0.0;
  motor->_cmin = 1.0;
  motor->_direction = DIRECTION_CCW;

  for (int i = 0; i < 2; i++) {
    motor->_pinInverted[i] = 0;
  }
  // Some reasonable default
  AccelStepper_enableOutputs (motor);
  AccelStepper_setAcceleration (motor, 40);
}

void AccelStepper_setMaxSpeed(StepperMotor * motor, float speed)
{
  if (motor->_maxSpeed != speed)
  {
    motor->_maxSpeed = speed;
    motor->_cmin = ONE_SECOND_FLOAT / speed;
    // Recompute _n from current speed and adjust speed if accelerating or cruising
    if (motor->_n > 0)
    {
      motor->_n = (long) ((motor->_speed * motor->_speed)
          / (2.0 * motor->_acceleration));  // Equation 16
      AccelStepper_computeNewSpeed (motor);
    }
  }
}

void AccelStepper_setAcceleration(StepperMotor * motor, float acceleration)
{
  if (acceleration == 0.0)
    return;
  if (motor->_acceleration != acceleration)
  {
    // Recompute _n per Equation 17
    motor->_n = motor->_n * (motor->_acceleration / acceleration);
    // New c0 per Equation 7, with correction per Equation 15
    motor->_c0 = 0.676 * sqrt(2.0 / acceleration) * ONE_SECOND_FLOAT;  // Equation 15
    motor->_acceleration = acceleration;
    AccelStepper_computeNewSpeed (motor);
  }
}

void AccelStepper_setSpeed(StepperMotor * motor, float speed)
{
  if (speed == motor->_speed)
    return;

  speed = constrain (speed, -motor->_maxSpeed, motor->_maxSpeed);
  if (speed == 0.0)
    motor->_stepInterval = 0;
  else
  {
    motor->_stepInterval = fabs (ONE_SECOND_FLOAT / speed);
    motor->_direction = (speed > 0.0) ? DIRECTION_CW : DIRECTION_CCW;
  }

  motor->_speed = speed;
}

float AccelStepper_speed(StepperMotor * motor)
{
  return motor->_speed;
}

// 1 pin step function (ie for stepper drivers)
// This is passed the current step number (0 to 7)
// Subclasses can override
void AccelStepper_step(StepperMotor * motor)
{
  // _pin[0] is step, _pin[1] is direction
  AccelStepper_setOutputPins (motor, motor->_direction ? 0b10 : 0b00);  // Set direction first else get rogue pulses
  delayMicroseconds(50);

  AccelStepper_setOutputPins (motor, motor->_direction ? 0b11 : 0b01);  // step HIGH
  // Caution 50us setup time
  // Delay the minimum allowed pulse width
  delayMicroseconds(motor->_minPulseWidth);
  AccelStepper_setOutputPins (motor, motor->_direction ? 0b10 : 0b00);  // step LOW
}

// You might want to override this to implement eg serial output
// bit 0 of the mask corresponds to _pin[0]
// bit 1 of the mask corresponds to _pin[1]
// ....
void AccelStepper_setOutputPins(StepperMotor * motor, uint8_t mask)
{
  uint8_t numpins = 2;
  uint8_t i;

  for (i = 0; i < numpins; i++)
    digitalWrite (
        motor->_pin[i],
        (mask & (1 << i)) ?
            (HIGH ^ motor->_pinInverted[i]) : (LOW ^ motor->_pinInverted[i]));
}

// Prevents power consumption on the outputs
void AccelStepper_disableOutputs(StepperMotor * motor)
{
  AccelStepper_setOutputPins (motor, 0);  // Handles inversion automatically
  if (motor->_enablePin != 0xff)
    digitalWrite (motor->_enablePin, LOW ^ motor->_enableInverted);
}

void AccelStepper_enableOutputs(StepperMotor * motor)
{
  pinMode(_pin[0], OUTPUT);
  pinMode(_pin[1], OUTPUT);
  if (motor->_enablePin != 0xff)
  {
    pinMode(_enablePin, OUTPUT);
    digitalWrite (motor->_enablePin, HIGH ^ motor->_enableInverted);
  }
}

void AccelStepper_setMinPulseWidth(StepperMotor * motor, unsigned int minWidth)
{
  motor->_minPulseWidth = minWidth;
}

void AccelStepper_setEnablePin(StepperMotor * motor, uint8_t enablePin)
{
  motor->_enablePin = enablePin;

  // This happens after construction, so init pin now.
  if (motor->_enablePin != 0xff)
  {
    pinMode(_enablePin, OUTPUT);
    digitalWrite (motor->_enablePin, HIGH ^ motor->_enableInverted);
  }
}

void AccelStepper_setPinsInverted(StepperMotor * motor, bool pin1Invert,
    bool pin2Invert, bool pin3Invert, bool pin4Invert, bool enableInvert)
{
  motor->_pinInverted[0] = pin1Invert;
  motor->_pinInverted[1] = pin2Invert;
  motor->_pinInverted[2] = pin3Invert;
  motor->_pinInverted[3] = pin4Invert;
  motor->_enableInverted = enableInvert;
}

// Blocks until the target position is reached and stopped
void AccelStepper_runToPosition(StepperMotor * motor)
{
  while (AccelStepper_run (motor))
  {
    ;
  }
}

bool AccelStepper_runSpeedToPosition(StepperMotor * motor)
{
  if (motor->_targetPos == motor->_currentPos)
    return (FALSE);

  if (motor->_targetPos > motor->_currentPos)
    motor->_direction = DIRECTION_CW;
  else
    motor->_direction = DIRECTION_CCW;

  return AccelStepper_runSpeed (motor);
}

// Blocks until the new target position is reached
void AccelStepper_runToNewPosition(StepperMotor * motor, long position)
{
  AccelStepper_moveTo (motor, position);
  AccelStepper_runToPosition (motor);
}

void AccelStepper_stop(StepperMotor * motor)
{
  if (motor->_speed != 0.0)
  {
    long stepsToStop = (long) ((motor->_speed * motor->_speed)
        / (2.0 * motor->_acceleration)) + 1;  // Equation 16 (+integer rounding)
    if (motor->_speed > 0)
      AccelStepper_move (motor, stepsToStop);
    else
      AccelStepper_move (motor, -stepsToStop);
  }
}
