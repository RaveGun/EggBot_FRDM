/*
 * Functions.h
 *
 *  Created on: 18.04.2015
 *      Author: COX
 */

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include "CTypes.h"

extern void SendChar(unsigned char ch, UART_Desc *desc);
extern void SendString(const unsigned char *str,  UART_Desc *desc);

extern void sendVersion(void);
extern void enableMotors(void);
extern void stepperModeConfigure(void);
extern void setPen(void);
extern void stepperMove(void);
extern void ignore(void);
extern void togglePen(void);
extern void ignore(void);
extern void nodeCountIncrement(void);
extern void nodeCountDecrement(void);
extern void setNodeCount(void);
extern void queryNodeCount(void);
extern void setLayer(void);
extern void queryLayer(void);
extern void queryPen(void);
extern void queryButton(void);
extern void unrecognized(const char* command);

extern void initHardware();

extern void inline sendAck(void);
extern void inline sendError(void);


#endif /* FUNCTIONS_H_ */
