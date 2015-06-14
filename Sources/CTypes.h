/*
 * CTypes.h
 *
 *  Created on: 18.04.2015
 *      Author: COX
 */

#ifndef CTYPES_H_
#define CTYPES_H_

typedef struct {
  LDD_TDeviceData *handle; /* LDD device handle */
  volatile uint8_t isSent; /* this will be set to 1 once the block has been sent */
  uint8_t rxChar; /* single character buffer for receiving chars */
  uint8_t (*rxPutFct)(uint8_t); /* callback to put received character into buffer */
} UART_Desc;

#endif /* CTYPES_H_ */
