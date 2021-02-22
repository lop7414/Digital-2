#include <xc.h>
#include "ADC.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ADC_Init (void){
    ADCON0bits.ADCS0 = 1;
    ADCON0bits.ADCS1 = 0;
    ADCON0bits.ADON = 1;   // adc on
    ADCON1bits.ADFM = 0;
    ADCON1bits.VCFG0 = 0;
    ADCON1bits.VCFG1 = 0;
}

unsigned char ADC_Read(int a,int b){
    ADCON0bits.CHS0 = a;
    ADCON0bits.CHS1 = b;
    ADCON0bits.CHS2 = 0;
    ADCON0bits.CHS3 = 0;
    ADCON0bits.ADON = 1;
    ADCON0bits.GO = 1;
    PIR1bits.ADIF = 0;
    return(ADRESH);
}