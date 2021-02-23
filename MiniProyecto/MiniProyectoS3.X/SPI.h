#ifndef _XTAL_FREQ
#define _XTAL_FREQ 4000000
#endif

#ifndef __LIB_SPI_H_
#define	__LIB_SPI_H_

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>
#include <stdio.h>

void SPI_Init(unsigned char a);

void SPI_Write(char a);

void SPI_Ready(unsigned char a);

void SPI_Read(char a);

#endif	/* XC_HEADER_TEMPLATE_H */