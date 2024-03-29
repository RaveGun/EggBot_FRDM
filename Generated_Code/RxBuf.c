/* ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : RxBuf.c
**     Project     : PEX_C_Project
**     Processor   : MK20DX128VLH5
**     Component   : RingBuffer
**     Version     : Component 01.033, Driver 01.00, CPU db: 3.00.000
**     Compiler    : GNU C Compiler
**     Date/Time   : 2015-05-01, 17:15, # CodeGen: 24
**     Abstract    :
**         This component implements a ring buffer for different integer data type.
**     Settings    :
**          Component name                                 : RxBuf
**          Buffer Size                                    : 64
**     Contents    :
**         Clear           - void RxBuf_Clear(void);
**         Put             - uint8_t RxBuf_Put(RxBuf_ElementType elem);
**         Get             - uint8_t RxBuf_Get(RxBuf_ElementType *elemP);
**         NofElements     - RxBuf_BufSizeType RxBuf_NofElements(void);
**         NofFreeElements - RxBuf_BufSizeType RxBuf_NofFreeElements(void);
**         Init            - void RxBuf_Init(void);
**
**     License   :  Open Source (LGPL)
**     Copyright : (c) Copyright Erich Styger, 2014, all rights reserved.
**     Web: http://www.mcuoneclipse.com
**     This an open source software of an embedded component for Processor Expert.
**     This is a free software and is opened for education,  research  and commercial developments under license policy of following terms:
**     * This is a free software and there is NO WARRANTY.
**     * No restriction on use. You can use, modify and redistribute it for personal, non-profit or commercial product UNDER YOUR RESPONSIBILITY.
**     * Redistributions of source code must retain the above copyright notice.
** ###################################################################*/
/*!
** @file RxBuf.c
** @version 01.00
** @brief
**         This component implements a ring buffer for different integer data type.
*/         
/*!
**  @addtogroup RxBuf_module RxBuf module documentation
**  @{
*/         

/* MODULE RxBuf. */

#include "RxBuf.h"

#if RxBuf_IS_REENTRANT
  #define RxBuf_DEFINE_CRITICAL() CS1_CriticalVariable()
  #define RxBuf_ENTER_CRITICAL()  CS1_EnterCritical()
  #define RxBuf_EXIT_CRITICAL()   CS1_ExitCritical()
#else
  #define RxBuf_DEFINE_CRITICAL() /* nothing */
  #define RxBuf_ENTER_CRITICAL()  /* nothing */
  #define RxBuf_EXIT_CRITICAL()   /* nothing */
#endif
static RxBuf_ElementType RxBuf_buffer[RxBuf_BUF_SIZE]; /* ring buffer */
static RxBuf_BufSizeType RxBuf_inIdx;  /* input index */
static RxBuf_BufSizeType RxBuf_outIdx; /* output index */
static RxBuf_BufSizeType RxBuf_inSize; /* size data in buffer */
/*
** ===================================================================
**     Method      :  RxBuf_Put (component RingBuffer)
**     Description :
**         Puts a new element into the buffer
**     Parameters  :
**         NAME            - DESCRIPTION
**         elem            - New element to be put into the buffer
**     Returns     :
**         ---             - Error code
** ===================================================================
*/
uint8_t RxBuf_Put(RxBuf_ElementType elem)
{
  uint8_t res = ERR_OK;
  RxBuf_DEFINE_CRITICAL();

  RxBuf_ENTER_CRITICAL();
  if (RxBuf_inSize==RxBuf_BUF_SIZE) {
    res = ERR_TXFULL;
  } else {
    RxBuf_buffer[RxBuf_inIdx] = elem;
    RxBuf_inIdx++;
    if (RxBuf_inIdx==RxBuf_BUF_SIZE) {
      RxBuf_inIdx = 0;
    }
    RxBuf_inSize++;
  }
  RxBuf_EXIT_CRITICAL();
  return res;
}

/*
** ===================================================================
**     Method      :  RxBuf_Get (component RingBuffer)
**     Description :
**         Removes an element from the buffer
**     Parameters  :
**         NAME            - DESCRIPTION
**       * elemP           - Pointer to where to store the received
**                           element
**     Returns     :
**         ---             - Error code
** ===================================================================
*/
uint8_t RxBuf_Get(RxBuf_ElementType *elemP)
{
  uint8_t res = ERR_OK;
  RxBuf_DEFINE_CRITICAL();

  RxBuf_ENTER_CRITICAL();
  if (RxBuf_inSize==0) {
    res = ERR_RXEMPTY;
  } else {
    *elemP = RxBuf_buffer[RxBuf_outIdx];
    RxBuf_inSize--;
    RxBuf_outIdx++;
    if (RxBuf_outIdx==RxBuf_BUF_SIZE) {
      RxBuf_outIdx = 0;
    }
  }
  RxBuf_EXIT_CRITICAL();
  return res;
}

/*
** ===================================================================
**     Method      :  RxBuf_NofElements (component RingBuffer)
**     Description :
**         Returns the actual number of elements in the buffer.
**     Parameters  : None
**     Returns     :
**         ---             - Number of elements in the buffer.
** ===================================================================
*/
RxBuf_BufSizeType RxBuf_NofElements(void)
{
  return RxBuf_inSize;
}

/*
** ===================================================================
**     Method      :  RxBuf_NofFreeElements (component RingBuffer)
**     Description :
**         Returns the actual number of free elements/space in the
**         buffer.
**     Parameters  : None
**     Returns     :
**         ---             - Number of elements in the buffer.
** ===================================================================
*/
RxBuf_BufSizeType RxBuf_NofFreeElements(void)
{
  return (RxBuf_BufSizeType)(RxBuf_BUF_SIZE-RxBuf_inSize);
}

/*
** ===================================================================
**     Method      :  RxBuf_Init (component RingBuffer)
**     Description :
**         Initializes the data structure
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void RxBuf_Init(void)
{
  RxBuf_inIdx = 0;
  RxBuf_outIdx = 0;
  RxBuf_inSize = 0;
}

/*
** ===================================================================
**     Method      :  RxBuf_Clear (component RingBuffer)
**     Description :
**         Clear (empty) the ring buffer.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void RxBuf_Clear(void)
{
  RxBuf_DEFINE_CRITICAL();

  RxBuf_ENTER_CRITICAL();
  RxBuf_Init();
  RxBuf_EXIT_CRITICAL();
}

/* END RxBuf. */

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
