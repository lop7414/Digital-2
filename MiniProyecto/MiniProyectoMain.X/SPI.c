#include <xc.h>
#include "SPI.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void SPI_Init(unsigned char a){
    switch(a){
        case 0:                     // Master mode Fosc/4
            TRISCbits.TRISC5 = 0;
            TRISCbits.TRISC3 = 0;
            SSPSTATbits.SMP = 0;
            SSPSTATbits.CKE = 0;
            SSPSTATbits.BF = 0;
            SSPCON = 0b00100000;
            //SSPCONbits.CKP = 0;
            //SSPCONbits.SSPEN = 1;
            break;
        case 1:                     // Master mode Fosc/16
            TRISCbits.TRISC5 = 0;
            TRISCbits.TRISC3 = 0;
            SSPSTATbits.SMP = 0;
            SSPSTATbits.CKE = 0;
            SSPSTATbits.BF = 0;
            SSPCON = 0b00100001;
            //SSPCONbits.CKP = 0;
            //SSPCONbits.SSPEN = 1;
            break;
        case 2:                     // Master mode Fosc/64
            TRISCbits.TRISC5 = 0;
            TRISCbits.TRISC3 = 0;
            SSPSTATbits.SMP = 0;
            SSPSTATbits.CKE = 0;
            SSPSTATbits.BF = 0;
            SSPCON = 0b00100010;
            //SSPCONbits.CKP = 0;
            //SSPCONbits.SSPEN = 1;
            break;
        case 3:                     // Slave mode
            TRISCbits.TRISC5 = 0;
            TRISCbits.TRISC3 = 1;
            TRISCbits.TRISC4 = 1;
            SSPSTATbits.SMP = 0;
            SSPSTATbits.CKE = 0;
            SSPSTATbits.BF = 0;
            SSPCON = 0b00100100;
    }
}

void SPI_Write(char a){
    SSPBUF = a;
    SSPIF = 0;
}

void SPI_Ready(unsigned char a){
    if (SSPSTATbits.BF == 1){
        a = 1;
    }
    else if (SSPSTATbits.BF == 0){
        a = 0;
    }
}

void SPI_Read(char a){
    a = SSPBUF;
    SSPIF = 0;
}