/*
 * File:   MiniProyectoSPI.c
 * Author: francisco lopez
 *
 * se Adaptaron librerias de Ligo George
 * extraidas de la pagina https://electrosome.com/lcd-pic-mplab-xc8/#Example
 * 
 * Created on February 19, 2021, 4:59 PM
 * 
 */

// PIC16F887 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (XT oscillator: Crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

//******************************************************************************
// librer�as
//******************************************************************************

#include <xc.h>
#include <stdint.h>

#define _XTAL_FREQ 4000000

#include "pic16f887.h"
#include "SPI.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//******************************************************************************
// Variables
//******************************************************************************
char Data;
char Ready;
//******************************************************************************
// Funciones
//******************************************************************************
void setup(void);

//******************************************************************************
// Main
//******************************************************************************

void main(void) {
    
    setup();
    
//**************************************************************************
// Loop principal
//**************************************************************************
        
    while (1) {
        
        SPI_Init(SPI_SLAVE_SS_EN, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW, SPI_IDLE_2_ACTIVE);
        
        Data = 0;
        
        SPI_Write(Data);
    }
}

//******************************************************************************
// Configuraci�n
//******************************************************************************

void setup(void) {
    ANSEL = 0b00001001;
    ANSELH= 0b00000000;
    TRISA = 0b00001001;
    TRISB = 0b00000000;
    TRISC = 0b00001000;
    TRISD = 0b00000000;
    TRISE = 0;
}

//******************************************************************************
// Funciones
//******************************************************************************

/*Precodigo
 */