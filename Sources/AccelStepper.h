/** AccelStepper.h
 *
 * \mainpage AccelStepper library for Arduino
 *
 * This is the Arduino AccelStepper library.
 * It provides an object-oriented interface for 2, 3 or 4 pin stepper motors.
 *
 * The standard Arduino IDE includes the Stepper library
 * (http://arduino.cc/en/Reference/Stepper) for stepper motors. It is
 * perfectly adequate for simple, single motor applications.
 *
 * AccelStepper significantly improves on the standard Arduino Stepper library in several ways:
 * \li Supports acceleration and deceleration
 * \li Supports multiple simultaneous steppers, with independent concurrent stepping on each stepper
 * \li API functions never delay() or block
 * \li Supports 2, 3 and 4 wire steppers, plus 3 and 4 wire half steppers.
 * \li Supports alternate stepping functions to enable support of AFMotor (https://github.com/adafruit/Adafruit-Motor-Shield-library)
 * \li Supports stepper drivers such as the Sparkfun EasyDriver (based on 3967 driver chip)
 * \li Very slow speeds are supported
 * \li Extensive API
 * \li Subclass support
 *
 * The latest version of this documentation can be downloaded from
 * http://www.airspayce.com/mikem/arduino/AccelStepper
 * The version of the package that this documentation refers to can be downloaded
 * from http://www.airspayce.com/mikem/arduino/AccelStepper/AccelStepper-1.47.zip
 *
 * Example Arduino programs are included to show the main modes of use.
 *
 * You can also find online help and discussion at http://groups.google.com/group/accelstepper
 * Please use that group for all questions and discussions on this topic.
 * Do not contact the author directly, unless it is to discuss commercial licensing.
 * Before asking a question or reporting a bug, please read http://www.catb.org/esr/faqs/smart-questions.html
 *
 * Tested on Arduino Diecimila and Mega with arduino-0018 & arduino-0021
 * on OpenSuSE 11.1 and avr-libc-1.6.1-1.15,
 * cross-avr-binutils-2.19-9.1, cross-avr-gcc-4.1.3_20080612-26.5.
 * Tested on Teensy http://www.pjrc.com/teensy including Teensy 3.1 built using Arduino IDE 1.0.5 with
 * teensyduino addon 1.18 and later.
 *
 * \par Installation
 *
 * Install in the usual way: unzip the distribution zip file to the libraries
 * sub-folder of your sketchbook.
 *
 * \par Theory
 *
 * This code uses speed calculations as described in
 * "Generate stepper-motor speed profiles in real time" by David Austin
 * http://fab.cba.mit.edu/classes/MIT/961.09/projects/i0/Stepper_Motor_Speed_Profile.pdf
 * with the exception that AccelStepper uses steps per second rather than radians per second
 * (because we dont know the step angle of the motor)
 * An initial step interval is calculated for the first step, based on the desired acceleration
 * On subsequent steps, shorter step intervals are calculated based
 * on the previous step until max speed is achieved.
 *
 * \par Donations
 *
 * This library is offered under a free GPL license for those who want to use it that way.
 * We try hard to keep it up to date, fix bugs
 * and to provide free support. If this library has helped you save time or money, please consider donating at
 * http://www.airspayce.com or here:
 *
 * \htmlonly <form action="https://www.paypal.com/cgi-bin/webscr" method="post"><input type="hidden" name="cmd" value="_donations" /> <input type="hidden" name="business" value="mikem@airspayce.com" /> <input type="hidden" name="lc" value="AU" /> <input type="hidden" name="item_name" value="Airspayce" /> <input type="hidden" name="item_number" value="AccelStepper" /> <input type="hidden" name="currency_code" value="USD" /> <input type="hidden" name="bn" value="PP-DonationsBF:btn_donateCC_LG.gif:NonHosted" /> <input type="image" alt="PayPal — The safer, easier way to pay online." name="submit" src="https://www.paypalobjects.com/en_AU/i/btn/btn_donateCC_LG.gif" /> <img alt="" src="https://www.paypalobjects.com/en_AU/i/scr/pixel.gif" width="1" height="1" border="0" /></form> \endhtmlonly
 *
 * \par Trademarks
 *
 * AccelStepper is a trademark of AirSpayce Pty Ltd. The AccelStepper mark was first used on April 26 2010 for
 * international trade, and is used only in relation to motor control hardware and software.
 * It is not to be confused with any other similar marks covering other goods and services.
 *
 * \par Copyright
 *
 * This software is Copyright (C) 2010 Mike McCauley. Use is subject to license
 * conditions. The main licensing options available are GPL V2 or Commercial:
 *
 * \par Open Source Licensing GPL V2
 * This is the appropriate option if you want to share the source code of your
 * application with everyone you distribute it to, and you also want to give them
 * the right to share who uses it. If you wish to use this software under Open
 * Source Licensing, you must contribute all your source code to the open source
 * community in accordance with the GPL Version 2 when your application is
 * distributed. See http://www.gnu.org/copyleft/gpl.html
 *
 * \par Commercial Licensing
 * This is the appropriate option if you are creating proprietary applications
 * and you are not prepared to distribute and share the source code of your
 * application. Contact info@airspayce.com for details.
 *
 * \par Revision History
 * \version 1.0 Initial release
 *
 * \version 1.1 Added speed() function to get the current speed.
 * \version 1.2 Added runSpeedToPosition() submitted by Gunnar Arndt.
 * \version 1.3 Added support for stepper drivers (ie with Step and Direction inputs) with _pins == 1
 * \version 1.4 Added functional contructor to support AFMotor, contributed by Limor, with example sketches.
 * \version 1.5 Improvements contributed by Peter Mousley: Use of microsecond steps and other speed improvements
 *              to increase max stepping speed to about 4kHz. New option for user to set the min allowed pulse width.
 *              Added checks for already running at max speed and skip further calcs if so.
 * \version 1.6 Fixed a problem with wrapping of microsecond stepping that could cause stepping to hang.
 *              Reported by Sandy Noble.
 *              Removed redundant _lastRunTime member.
 * \version 1.7 Fixed a bug where setCurrentPosition() did not always work as expected.
 *              Reported by Peter Linhart.
 * \version 1.8 Added support for 4 pin half-steppers, requested by Harvey Moon
 * \version 1.9 setCurrentPosition() now also sets motor speed to 0.
 * \version 1.10 Builds on Arduino 1.0
 * \version 1.11 Improvments from Michael Ellison:
 *   Added optional enable line support for stepper drivers
 *   Added inversion for step/direction/enable lines for stepper drivers
 * \version 1.12 Announce Google Group
 * \version 1.13 Improvements to speed calculation. Cost of calculation is now less in the worst case,
 *    and more or less constant in all cases. This should result in slightly beter high speed performance, and
 *    reduce anomalous speed glitches when other steppers are accelerating.
 *    However, its hard to see how to replace the sqrt() required at the very first step from 0 speed.
 * \version 1.14 Fixed a problem with compiling under arduino 0021 reported by EmbeddedMan
 * \version 1.15 Fixed a problem with runSpeedToPosition which did not correctly handle
 *    running backwards to a smaller target position. Added examples
 * \version 1.16 Fixed some cases in the code where abs() was used instead of fabs().
 * \version 1.17 Added example ProportionalControl
 * \version 1.18 Fixed a problem: If one calls the funcion runSpeed() when Speed is zero, it makes steps
 *    without counting. reported by  Friedrich, Klappenbach.
 * \version 1.19 Added MotorInterfaceType and symbolic names for the number of pins to use
 *               for the motor interface. Updated examples to suit.
 *               Replaced individual pin assignment variables _pin1, _pin2 etc with array _pin[4].
 *               _pins member changed to _interface.
 *               Added _pinInverted array to simplify pin inversion operations.
 *               Added new function setOutputPins() which sets the motor output pins.
 *               It can be overridden in order to provide, say, serial output instead of parallel output
 *               Some refactoring and code size reduction.
 * \version 1.20 Improved documentation and examples to show need for correctly
 *               specifying AccelStepper::FULL4WIRE and friends.
 * \version 1.21 Fixed a problem where desiredSpeed could compute the wrong step acceleration
 *               when _speed was small but non-zero. Reported by Brian Schmalz.
 *               Precompute sqrt_twoa to improve performance and max possible stepping speed
 * \version 1.22 Added Bounce.pde example
 *               Fixed a problem where calling moveTo(), setMaxSpeed(), setAcceleration() more
 *               frequently than the step time, even
 *               with the same values, would interfere with speed calcs. Now a new speed is computed
 *               only if there was a change in the set value. Reported by Brian Schmalz.
 * \version 1.23 Rewrite of the speed algorithms in line with
 *               http://fab.cba.mit.edu/classes/MIT/961.09/projects/i0/Stepper_Motor_Speed_Profile.pdf
 *               Now expect smoother and more linear accelerations and decelerations. The desiredSpeed()
 *               function was removed.
 * \version 1.24  Fixed a problem introduced in 1.23: with runToPosition, which did never returned
 * \version 1.25  Now ignore attempts to set acceleration to 0.0
 * \version 1.26  Fixed a problem where certina combinations of speed and accelration could cause
 *                oscillation about the target position.
 * \version 1.27  Added stop() function to stop as fast as possible with current acceleration parameters.
 *                Also added new Quickstop example showing its use.
 * \version 1.28  Fixed another problem where certain combinations of speed and accelration could cause
 *                oscillation about the target position.
 *                Added support for 3 wire full and half steppers such as Hard Disk Drive spindle.
 *                Contributed by Yuri Ivatchkovitch.
 * \version 1.29  Fixed a problem that could cause a DRIVER stepper to continually step
 *                with some sketches. Reported by Vadim.
 * \version 1.30  Fixed a problem that could cause stepper to back up a few steps at the end of
 *                accelerated travel with certain speeds. Reported and patched by jolo.
 * \version 1.31  Updated author and distribution location details to airspayce.com
 * \version 1.32  Fixed a problem with enableOutputs() and setEnablePin on Arduino Due that
 *                prevented the enable pin changing stae correctly. Reported by Duane Bishop.
 * \version 1.33  Fixed an error in example AFMotor_ConstantSpeed.pde did not setMaxSpeed();
 *                Fixed a problem that caused incorrect pin sequencing of FULL3WIRE and HALF3WIRE.
 *                Unfortunately this meant changing the signature for all step*() functions.
 *                Added example MotorShield, showing how to use AdaFruit Motor Shield to control
 *                a 3 phase motor such as a HDD spindle motor (and without using the AFMotor library.
 * \version 1.34  Added setPinsInverted(bool pin1Invert, bool pin2Invert, bool pin3Invert, bool pin4Invert, bool enableInvert)
 *                to allow inversion of 2, 3 and 4 wire stepper pins. Requested by Oleg.
 * \version 1.35  Removed default args from setPinsInverted(bool, bool, bool, bool, bool) to prevent ambiguity with
 *                setPinsInverted(bool, bool, bool). Reported by Mac Mac.
 * \version 1.36  Changed enableOutputs() and disableOutputs() to be virtual so can be overridden.
 *                Added new optional argument 'enable' to constructor, which allows you toi disable the
 *                automatic enabling of outputs at construction time. Suggested by Guido.
 * \version 1.37  Fixed a problem with step1 that could cause a rogue step in the
 *                wrong direction (or not,
 *                depending on the setup-time requirements of the connected hardware).
 *                Reported by Mark Tillotson.
 * \version 1.38  run() function incorrectly always returned true. Updated function and doc so it returns true
 *                if the motor is still running to the target position.
 * \version 1.39  Updated typos in keywords.txt, courtesey Jon Magill.
 * \version 1.40  Updated documentation, including testing on Teensy 3.1
 * \version 1.41  Fixed an error in the acceleration calculations, resulting in acceleration of haldf the intended value
 * \version 1.42  Improved support for FULL3WIRE and HALF3WIRE output pins. These changes were in Yuri's original
 *                contribution but did not make it into production.<br>
 * \version 1.43  Added DualMotorShield example. Shows how to use AccelStepper to control 2 x 2 phase steppers using the
 *                Itead Studio Arduino Dual Stepper Motor Driver Shield model IM120417015.<br>
 * \version 1.44  examples/DualMotorShield/DualMotorShield.ino examples/DualMotorShield/DualMotorShield.pde
 *                was missing from the distribution.<br>
 * \version 1.45  Fixed a problem where if setAcceleration was not called, there was no default
 *                acceleration. Reported by Michael Newman.<br>
 * \version 1.45  Fixed inaccuracy in acceleration rate by using Equation 15, suggested by Sebastian Gracki.<br>
 *                Performance improvements in runSpeed suggested by Jaakko Fagerlund.<br>
 * \version 1.46  Fixed error in documentation for runToPosition().
 *                Reinstated time calculations in runSpeed() since new version is reported
 *                not to work correctly under some circumstances. Reported by Oleg V Gavva.<br>
 */

/**
 * \author  Mike McCauley (mikem@airspayce.com) DO NOT CONTACT THE AUTHOR DIRECTLY: USE THE LISTS
 * Copyright (C) 2009-2013 Mike McCauley
 * $Id: AccelStepper.h,v 1.21 2014/10/31 06:05:30 mikem Exp mikem $ */

#ifndef AccelStepper_h
#define AccelStepper_h

#include "PE_Types.h"

/**
 * \class AccelStepper AccelStepper.h <AccelStepper.h>
 * \brief Support for stepper motors with acceleration etc.
 *
 * This defines a single 2 or 4 pin stepper motor, or stepper moter with fdriver chip, with optional
 * acceleration, deceleration, absolute positioning commands etc. Multiple
 * simultaneous steppers are supported, all moving
 * at different speeds and accelerations.
 *
 * \par Operation
 * This module operates by computing a step time in microseconds. The step
 * time is recomputed after each step and after speed and acceleration
 * parameters are changed by the caller. The time of each step is recorded in
 * microseconds. The run() function steps the motor once if a new step is due.
 * The run() function must be called frequently until the motor is in the
 * desired position, after which time run() will do nothing.
 *
 * \par Positioning
 * Positions are specified by a signed long integer. At
 * construction time, the current position of the motor is consider to be 0. Positive
 * positions are clockwise from the initial position; negative positions are
 * anticlockwise. The current position can be altered for instance after
 * initialization positioning.
 *
 * \par Caveats
 * This is an open loop controller: If the motor stalls or is oversped,
 * AccelStepper will not have a correct
 * idea of where the motor really is (since there is no feedback of the motor's
 * real position. We only know where we _think_ it is, relative to the
 * initial starting point).
 *
 * \par Performance
 * The fastest motor speed that can be reliably supported is about 4000 steps per
 * second at a clock frequency of 16 MHz on Arduino such as Uno etc.
 * Faster processors can support faster stepping speeds.
 * However, any speed less than that
 * down to very slow speeds (much less than one per second) are also supported,
 * provided the run() function is called frequently enough to step the motor
 * whenever required for the speed set.
 * Calling setAcceleration() is expensive,
 * since it requires a square root to be calculated.*/
typedef enum {
  FUNCTION = 0, /**< Use the functional interface, implementing your own driver functions (internal use only) */
  DRIVER = 1, /**< Stepper Driver, 2 driver pins required */
  FULL2WIRE = 2, /**< 2 wire stepper, 2 motor pins required */
  FULL3WIRE = 3, /**< 3 wire stepper, such as HDD spindle, 3 motor pins required */
  FULL4WIRE = 4, /**< 4 wire full stepper, 4 motor pins required */
  HALF3WIRE = 6, /**< 3 wire half stepper, such as HDD spindle, 3 motor pins required */
  HALF4WIRE = 8 /**< 4 wire half stepper, 4 motor pins required */
} MotorInterfaceType;

typedef enum {
  DIRECTION_CCW = 0, /**< Clockwise */
  DIRECTION_CW = 1 /**< Counter-Clockwise */
} MotorDirection;

typedef struct {
  /** Arduino pin number assignments for the 2 or 4 pins required to interface to the stepper motor or driver*/
  uint8_t _pin[2];
  /** Whether the _pins is inverted or not*/
  uint8_t _pinInverted[2];
  /** The current absolution position in steps.*/
  long _currentPos; /**< Steps*/
  /** The target position in steps. The AccelStepper library will move the
   *  motor from the _currentPos to the _targetPos, taking into account the
   *  max speed, acceleration and deceleration.*/
  long _targetPos;     // Steps
  /** The current motos speed in steps per second. Positive is clockwise.*/
  float _speed;         // Steps per second
  /// The maximum permitted speed in steps per second. Must be > 0.
  float _maxSpeed;
  /// The acceleration to use to accelerate or decelerate the motor in steps
  /// per second per second. Must be > 0
  float _acceleration;
  float _sqrt_twoa;  // Precomputed sqrt(2*_acceleration)
  /// The current interval between steps in microseconds.
  /// 0 means the motor is currently stopped with _speed == 0
  unsigned long _stepInterval;
  /// The last step time in microseconds
  unsigned long _lastStepTime;
  /// The minimum allowed pulse width in microseconds
  unsigned int _minPulseWidth;
  /// Is the enable pin inverted?
  bool _enableInverted;
  /// Enable pin for stepper driver, or 0xFF if unused.
  uint8_t _enablePin;
  /// The step counter for speed calculations
  long _n;
  /// Initial step size in microseconds
  float _c0;
  /// Last step size in microseconds
  float _cn;
  /// Min step size in microseconds based on maxSpeed
  float _cmin;  // at max speed
  /// Current direction motor is spinning in
  MotorDirection _direction;  // 1 == CW
} StepperMotor;

/// Set the target position. The run() function will try to move the motor (at most one step per call)
/// from the current position to the target position set by the most
/// recent call to this function. Caution: moveTo() also recalculates the speed for the next step.
/// If you are trying to use constant speed movements, you should call setSpeed() after calling moveTo().
/// \param[in] absolute The desired absolute position. Negative is
/// anticlockwise from the 0 position.
void AccelStepper_moveTo(StepperMotor * motor, long absolute);

/// Set the target position relative to the current position
/// \param[in] relative The desired position relative to the current position. Negative is
/// anticlockwise from the current position.
void AccelStepper_move(StepperMotor * motor, long relative);

/// Poll the motor and step it if a step is due, implementing
/// accelerations and decelerations to acheive the target position. You must call this as
/// frequently as possible, but at least once per minimum step time interval,
/// preferably in your main loop. Note that each call to run() will make at most one step, and then only when a step is due,
/// based on the current speed and the time since the last step.
/// \return true if the motor is still running to the target position.
bool AccelStepper_run(StepperMotor * motor);

void AccelStepper_Init(StepperMotor * motor, uint8_t pin1, uint8_t pin2);

/// Poll the motor and step it if a step is due, implementing a constant
/// speed as set by the most recent call to setSpeed(). You must call this as
/// frequently as possible, but at least once per step interval,
/// \return true if the motor was stepped.
bool AccelStepper_runSpeed(StepperMotor * motor);

/// Sets the maximum permitted speed. The run() function will accelerate
/// up to the speed set by this function.
/// Caution: the maximum speed achievable depends on your processor and clock speed.
/// \param[in] speed The desired maximum speed in steps per second. Must
/// be > 0. Caution: Speeds that exceed the maximum speed supported by the processor may
/// Result in non-linear accelerations and decelerations.
void AccelStepper_setMaxSpeed(StepperMotor * motor, float speed);

/// Sets the acceleration/deceleration rate.
/// \param[in] acceleration The desired acceleration in steps per second
/// per second. Must be > 0.0. This is an expensive call since it requires a square
/// root to be calculated. Dont call more ofthen than needed
void AccelStepper_setAcceleration(StepperMotor * motor, float acceleration);

/// Sets the desired constant speed for use with runSpeed().
/// \param[in] speed The desired constant speed in steps per
/// second. Positive is clockwise. Speeds of more than 1000 steps per
/// second are unreliable. Very slow speeds may be set (eg 0.00027777 for
/// once per hour, approximately. Speed accuracy depends on the Arduino
/// crystal. Jitter depends on how frequently you call the runSpeed() function.
void AccelStepper_setSpeed(StepperMotor * motor, float speed);

/// The most recently set speed
/// \return the most recent speed in steps per second
float AccelStepper_speed(StepperMotor * motor);

/// The distance from the current position to the target position.
/// \return the distance from the current position to the target position
/// in steps. Positive is clockwise from the current position.
long AccelStepper_distanceToGo(StepperMotor * motor);

/// The most recently set target position.
/// \return the target position
/// in steps. Positive is clockwise from the 0 position.
long AccelStepper_targetPosition(StepperMotor * motor);

/// The currently motor position.
/// \return the current motor position
/// in steps. Positive is clockwise from the 0 position.
long AccelStepper_currentPosition(StepperMotor * motor);

/// Resets the current position of the motor, so that wherever the motor
/// happens to be right now is considered to be the new 0 position. Useful
/// for setting a zero position on a stepper after an initial hardware
/// positioning move.
/// Has the side effect of setting the current motor speed to 0.
/// \param[in] position The position in steps of wherever the motor
/// happens to be right now.
void AccelStepper_setCurrentPosition(StepperMotor * motor, long position);

/// Moves the motor (with acceleration/deceleration)
/// to the target position and blocks until it is at
/// position. Dont use this in event loops, since it blocks.
void AccelStepper_runToPosition(StepperMotor * motor);

/// Runs at the currently selected speed until the target position is reached
/// Does not implement accelerations.
/// \return true if it stepped
bool AccelStepper_runSpeedToPosition(StepperMotor * motor);

/// Moves the motor (with acceleration/deceleration)
/// to the new target position and blocks until it is at
/// position. Dont use this in event loops, since it blocks.
/// \param[in] position The new target position.
void AccelStepper_runToNewPosition(StepperMotor * motor, long position);

/// Sets a new target position that causes the stepper
/// to stop as quickly as possible, using the current speed and acceleration parameters.
void AccelStepper_stop(StepperMotor * motor);

/// Disable motor pin outputs by setting them all LOW
/// Depending on the design of your electronics this may turn off
/// the power to the motor coils, saving power.
/// This is useful to support Arduino low power modes: disable the outputs
/// during sleep and then reenable with enableOutputs() before stepping
/// again.
void AccelStepper_disableOutputs(StepperMotor * motor);

/// Enable motor pin outputs by setting the motor pins to OUTPUT
/// mode. Called automatically by the constructor.
void AccelStepper_enableOutputs(StepperMotor * motor);

/// Sets the minimum pulse width allowed by the stepper driver. The minimum practical pulse width is
/// approximately 20 microseconds. Times less than 20 microseconds
/// will usually result in 20 microseconds or so.
/// \param[in] minWidth The minimum pulse width in microseconds.
void AccelStepper_setMinPulseWidth(StepperMotor * motor, unsigned int minWidth);

/// Sets the enable pin number for stepper drivers.
/// 0xFF indicates unused (default).
/// Otherwise, if a pin is set, the pin will be turned on when
/// enableOutputs() is called and switched off when disableOutputs()
/// is called.
/// \param[in] enablePin Arduino digital pin number for motor enable
/// \sa setPinsInverted
void AccelStepper_setEnablePin(StepperMotor * motor, uint8_t enablePin);

/// Sets the inversion for 2, 3 and 4 wire stepper pins
/// \param[in] pin1Invert True for inverted pin1, false for non-inverted
/// \param[in] pin2Invert True for inverted pin2, false for non-inverted
/// \param[in] pin3Invert True for inverted pin3, false for non-inverted
/// \param[in] pin4Invert True for inverted pin4, false for non-inverted
/// \param[in] enableInvert    True for inverted enable pin, false (default) for non-inverted
void AccelStepper_setPinsInverted(StepperMotor *motor, bool pin1Invert,
    bool pin2Invert, bool pin3Invert, bool pin4Invert, bool enableInvert);

/// Forces the library to compute a new instantaneous speed and set that as
/// the current speed. It is called by
/// the library:
/// \li  after each step
/// \li  after change to maxSpeed through setMaxSpeed()
/// \li  after change to acceleration through setAcceleration()
/// \li  after change to target position (relative or absolute) through
/// move() or moveTo()
void AccelStepper_computeNewSpeed(StepperMotor * motor);

/// Low level function to set the motor output pins
/// bit 0 of the mask corresponds to _pin[0]
/// bit 1 of the mask corresponds to _pin[1]
/// You can override this to impment, for example serial chip output insted of using the
/// output pins directly
void AccelStepper_setOutputPins(StepperMotor * motor, uint8_t mask);

/// Called to execute a step on a stepper driver (ie where pins == 1). Only called when a new step is
/// required. Subclasses may override to implement new stepping
/// interfaces. The default sets or clears the outputs of Step pin1 to step,
/// and sets the output of _pin2 to the desired direction. The Step pin (_pin1) is pulsed for 1 microsecond
/// which is the minimum STEP pulse width for the 3967 driver.
/// \param[in] step The current step phase number (0 to 7)
void AccelStepper_step(StepperMotor * motor);

#endif 
