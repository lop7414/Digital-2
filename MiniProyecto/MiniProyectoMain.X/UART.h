#ifndef __UART_H
#define	__UART_H

#ifndef _XTAL_FREQ
#define _XTAL_FREQ 4000000
#endif

int O;
int Destination;

#include <xc.h>
#include <stdint.h>// include processor files - each processor file is guarded.

//UART functions

int CONTADOR(int n);

void SERIAL_Init(void);

uint8_t UART_READ();

uint8_t UART_TX_Empty();

void UART_Write(uint8_t a);

#endif