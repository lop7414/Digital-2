#ifndef __ADC_H
#define	__ADC_H

#ifndef _XTAL_FREQ
#define _XTAL_FREQ 8000000
#endif

#include <xc.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// include processor files - each processor file is guarded.  

//ADC functions

void ADC_Init(void);

unsigned char ADC_Read(int a,int b);

#endif