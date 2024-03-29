/* ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : FreeCntrLdd1.h
**     Project     : PEX_C_Project
**     Processor   : MK20DX128VLH5
**     Component   : FreeCntr_LDD
**     Version     : Component 01.005, Driver 01.01, CPU db: 3.00.000
**     Compiler    : GNU C Compiler
**     Date/Time   : 2015-04-28, 19:50, # CodeGen: 23
**     Abstract    :
**          This device "FreeCntr_LDD" implements Free Running Counter
**          This FreeCntr component provides a high level API for unified
**          hardware access to various timer devices using the TimerUnit
**          component.
**     Settings    :
**          Component name                                 : FreeCntrLdd1
**          Module name                                    : PIT
**          Counter                                        : PIT_CVAL0
**          Counter direction                              : Down
**          Counter frequency                              : 10 MHz
**          Mode                                           : Compare match
**            Period/offset device                         : PIT_LDVAL0
**            Period/offset                                : 400 sec
**            Interrupt service/event                      : Disabled
**          Value type                                     : Optimal
**          Initialization                                 : 
**            Enabled in init. code                        : yes
**            Auto initialization                          : yes
**            Event mask                                   : 
**              OnInterrupt                                : Disabled
**          CPU clock/configuration selection              : 
**            Clock configuration 0                        : This component enabled
**            Clock configuration 1                        : This component disabled
**            Clock configuration 2                        : This component disabled
**            Clock configuration 3                        : This component disabled
**            Clock configuration 4                        : This component disabled
**            Clock configuration 5                        : This component disabled
**            Clock configuration 6                        : This component disabled
**            Clock configuration 7                        : This component disabled
**          Referenced components                          : 
**            Linked TimerUnit                             : TU1
**     Contents    :
**         Init            - LDD_TDeviceData* FreeCntrLdd1_Init(LDD_TUserData *UserDataPtr);
**         Deinit          - void FreeCntrLdd1_Deinit(LDD_TDeviceData *DeviceDataPtr);
**         GetCounterValue - FreeCntrLdd1_TValueType FreeCntrLdd1_GetCounterValue(LDD_TDeviceData...
**         ResetCounter    - LDD_TError FreeCntrLdd1_ResetCounter(LDD_TUserData *DeviceDataPtr);
**         GetDriverState  - LDD_TDriverState FreeCntrLdd1_GetDriverState(LDD_TUserData *DeviceDataPtr);
**
**     Copyright : 1997 - 2014 Freescale Semiconductor, Inc. 
**     All Rights Reserved.
**     
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**     
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**     
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**     
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**     
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**     
**     http: www.freescale.com
**     mail: support@freescale.com
** ###################################################################*/
/*!
** @file FreeCntrLdd1.h
** @version 01.01
** @brief
**          This device "FreeCntr_LDD" implements Free Running Counter
**          This FreeCntr component provides a high level API for unified
**          hardware access to various timer devices using the TimerUnit
**          component.
*/         
/*!
**  @addtogroup FreeCntrLdd1_module FreeCntrLdd1 module documentation
**  @{
*/         

#ifndef __FreeCntrLdd1_H
#define __FreeCntrLdd1_H

/* MODULE FreeCntrLdd1. */

/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* Include inherited beans */
#include "TU1.h"

#include "Cpu.h"

#ifdef __cplusplus
extern "C" {
#endif 


#ifndef __BWUserType_FreeCntrLdd1_TValueType
#define __BWUserType_FreeCntrLdd1_TValueType
  typedef TU1_TValueType FreeCntrLdd1_TValueType ; /* Type for data parameters of methods */
#endif
#define FreeCntrLdd1_CNT_INP_FREQ_U_0 TU1_CNT_INP_FREQ_U_0 /* Counter input frequency in Hz */
#define FreeCntrLdd1_CNT_INP_FREQ_R_0 TU1_CNT_INP_FREQ_R_0 /* Counter input frequency in Hz */
#define FreeCntrLdd1_CNT_INP_FREQ_COUNT TU1_CNT_INP_FREQ_COUNT /* Count of predefined counter input frequencies */
#ifdef TU1_PERIOD_TICKS
#define FreeCntrLdd1_PERIOD_TICKS TU1_PERIOD_TICKS /* Initialization value of period in 'counter ticks' */
#endif
#define FreeCntrLdd1_COUNTER_DIR 1U    /* Direction of counting DOWN */
#define FreeCntrLdd1_RESET_ON_COMPARE 1 /* This constant is defined if 'Compare match ' mode is selected. */
/*! Peripheral base address of a device allocated by the component. This constant can be used directly in PDD macros. */
#define FreeCntrLdd1_PRPH_BASE_ADDRESS  0x40037000U
  
/*! Device data structure pointer used when auto initialization property is enabled. This constant can be passed as a first parameter to all component's methods. */
#define FreeCntrLdd1_DeviceData  ((LDD_TDeviceData *)PE_LDD_GetDeviceStructure(PE_LDD_COMPONENT_FreeCntrLdd1_ID))

/* Methods configuration constants - generated for all enabled component's methods */
#define FreeCntrLdd1_Init_METHOD_ENABLED /*!< Init method of the component FreeCntrLdd1 is enabled (generated) */
#define FreeCntrLdd1_Deinit_METHOD_ENABLED /*!< Deinit method of the component FreeCntrLdd1 is enabled (generated) */
#define FreeCntrLdd1_GetCounterValue_METHOD_ENABLED /*!< GetCounterValue method of the component FreeCntrLdd1 is enabled (generated) */
#define FreeCntrLdd1_ResetCounter_METHOD_ENABLED /*!< ResetCounter method of the component FreeCntrLdd1 is enabled (generated) */
#define FreeCntrLdd1_GetDriverState_METHOD_ENABLED /*!< GetDriverState method of the component FreeCntrLdd1 is enabled (generated) */

/* Events configuration constants - generated for all enabled component's events */



/*
** ===================================================================
**     Method      :  FreeCntrLdd1_Init (component FreeCntr_LDD)
*/
/*!
**     @brief
**         Initializes the device. Allocates memory for the device data
**         structure, allocates interrupt vectors and sets interrupt
**         priority, sets pin routing, sets timing, etc. If the
**         property ["Enable in init. code"] is set to "yes" value then
**         the device is also enabled (see the description of the
**         [Enable] method). In this case the [Enable] method is not
**         necessary and needn't to be generated. This method can be
**         called only once. Before the second call of Init the [Deinit]
**         must be called first.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer will be
**                           passed as an event or callback parameter.
**     @return
**                         - Pointer to the dynamically allocated private
**                           structure or NULL if there was an error.
*/
/* ===================================================================*/
LDD_TDeviceData* FreeCntrLdd1_Init(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Method      :  FreeCntrLdd1_Deinit (component FreeCntr_LDD)
*/
/*!
**     @brief
**         Deinitializes the device. Switches off the device, frees the
**         device data structure memory, interrupts vectors, etc.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by Init method
*/
/* ===================================================================*/
void FreeCntrLdd1_Deinit(LDD_TDeviceData *DeviceDataPtr);

/*
** ===================================================================
**     Method      :  FreeCntrLdd1_GetCounterValue (component FreeCntr_LDD)
*/
/*!
**     @brief
**         Returns the content of counter register. This method can be
**         used both if counter is enabled and if counter is disabled.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @return
**                         - Counter value (number of counted ticks).
*/
/* ===================================================================*/
FreeCntrLdd1_TValueType FreeCntrLdd1_GetCounterValue(LDD_TDeviceData *DeviceDataPtr);

/*
** ===================================================================
**     Method      :  FreeCntrLdd1_ResetCounter (component FreeCntr_LDD)
*/
/*!
**     @brief
**         Resets counter. If counter is counting up then it is set to
**         zero. If counter is counting down then counter is updated to
**         the reload value.
**         The method is not available if HW doesn't allow resetting of
**         the counter.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK 
**                           ERR_SPEED - The component does not work in
**                           the active clock configuration
*/
/* ===================================================================*/
LDD_TError FreeCntrLdd1_ResetCounter(LDD_TUserData *DeviceDataPtr);

/*
** ===================================================================
**     Method      :  FreeCntrLdd1_GetDriverState (component FreeCntr_LDD)
*/
/*!
**     @brief
**         This method returns the current driver status.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @return
**                         - The current driver status mask.
**                           Following status masks defined in PE_Types.
**                           h can be used to check the current driver
**                           status.
**                           PE_LDD_DRIVER_DISABLED_IN_CLOCK_CONFIGURATIO
**                           N - 1 - Driver is disabled in the current
**                           mode; 0 - Driver is enabled in the current
**                           mode.  
**                           PE_LDD_DRIVER_DISABLED_BY_USER - 1 - Driver
**                           is disabled by the user; 0 - Driver is
**                           enabled by the user.        
*/
/* ===================================================================*/
LDD_TDriverState FreeCntrLdd1_GetDriverState(LDD_TUserData *DeviceDataPtr);

/* END FreeCntrLdd1. */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

#endif 
/* ifndef __FreeCntrLdd1_H */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.4 [05.09]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
