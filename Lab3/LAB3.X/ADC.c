#include <xc.h>
#include "ADC.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void CONTADOR (int  n, char *a){
    Destination = n;
    O = (Destination)*1;
    itoa(a,O,10);
    return;
}

void ADC_Init (void){
    ADCON0bits.ADCS0 = 1;
    ADCON0bits.ADCS1 = 0;
    ADCON0bits.ADON = 1;   // adc on
    ADCON1bits.ADFM = 0;
    ADCON1bits.VCFG0 = 0;
    ADCON1bits.VCFG1 = 0;
}

void ADC_Read(unsigned char a,unsigned char b,unsigned char c){
    ADCON0bits.CHS0 = a;
    ADCON0bits.CHS1 = b;
    ADCON0bits.CHS2 = 0;
    ADCON0bits.CHS3 = 0;
    ADCON0bits.ADON = 1;
    ADCON0bits.GO = 1;
    PIR1bits.ADIF = 0;
    c = ADRESH;
    return;
}