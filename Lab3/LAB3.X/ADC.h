#ifndef __ADC_H
#define	__ADC_H

#ifndef _XTAL_FREQ
#define _XTAL_FREQ 4000000
#endif

int O;
int Destination;

#include <xc.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// include processor files - each processor file is guarded.  

//ADC functions

void CONTADOR(int n, char *a);

void ADC_Init(void);

void ADC_Read(unsigned char a,unsigned char b,unsigned char adc);

#endif