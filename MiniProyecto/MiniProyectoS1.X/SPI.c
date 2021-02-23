#include <xc.h>
#include "SPI.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void SPI_Init(Spi_Type sType, Spi_Data_Sample sDataSample, Spi_Clock_Idle sClockIdle, Spi_Transmit_Edge sTransmitEdge)
{
    TRISC5 = 0;     //SDI
    TRISC4 = 1;     //SDO
   
    if(sType & 0b00000100) //If Slave Mode
    {
        SSPSTAT = sTransmitEdge;
        TRISC3 = 1;
    }
    else              //If Master Mode
    {
        SSPSTAT = sDataSample | sTransmitEdge;
        TRISC3 = 0;
    }

    SSPCON = sType | sClockIdle;
}

void SPI_Write(char a){
    SSPBUF = a;
}

unsigned SPI_Ready(void){
    if(SSPSTATbits.BF)
        return 1;
    else
        return 0;
}

char SPI_Read(void){
    while ( !SSPSTATbits.BF );
    return (SSPBUF);
}