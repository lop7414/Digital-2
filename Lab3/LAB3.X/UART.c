#include <xc.h>
#include "UART.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void SERIAL_Init(void){
    SPBRG = 25;
    // EL QUE TX
    TXSTAbits.BRGH = 1;
    TXSTAbits.TXEN = 1;
    TXSTAbits.SYNC = 0;
    TXSTAbits.TX9 = 0;
    //RX
    RCSTAbits.CREN = 1;
    RCSTAbits.SPEN = 1;
    RCSTAbits.RX9 = 0;
    // interruption
    PIE1bits.RCIE = 1;
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;
}

uint8_t UART_READ(){
    while(!RCIF);
    return RCREG;
}
 
uint8_t UART_TX_Empty(){
  // Check the output (transmitter) buffer emptiness
  return TRMT;
}

void UART_Write(uint8_t contador){
  while(!TRMT);
  TXREG = contador;
}