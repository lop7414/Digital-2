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
#pragma config FOSC = XT// Oscillator Selection bits (XT oscillator: Crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
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
// librerías
//******************************************************************************

#include <xc.h>
#include <stdint.h>

#define _XTAL_FREQ 8000000

#include "pic16f887.h"
#include "SPI.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//******************************************************************************
// Variables
//******************************************************************************
char    BBB;
char    START;
char    Ready;
char    slave;
//******************************************************************************
// Funciones
//******************************************************************************
void setup(void);
void PLUS(void);
void MINUS(void);
//******************************************************************************
// Main
//******************************************************************************
void __interrupt() ISR(void){
    if (SSPIF == 1){
        slave = SPI_Read();
        SPI_Write(BBB);
        SSPIF = 0;
    }
}


void main(void) {
    
    setup();
    
//**************************************************************************
// Loop principal
//**************************************************************************
        
    while (1) {
        
        GIE = 1;
        PEIE = 1;
        SSPIF = 0;
        SSPIE = 1;
        ADCON1 = 0x07;
        
        SPI_Init(SPI_SLAVE_SS_EN, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW, SPI_IDLE_2_ACTIVE);
        
        if (PORTBbits.RB1 == 0){
            if (PORTBbits.RB2 == 0){
                START = 1;
            }
        }
        
        if (START==1){
            if (PORTBbits.RB1 == 1){
                PLUS();
                START = 0;
            }
        
            if (PORTBbits.RB2 == 1){
                MINUS();
                START = 0;
            }
        }
        
         switch (BBB){
            case 0:
                PORTD = 0;
            break;
            
            case 1:
                PORTDbits.RD1 = 0;
                PORTDbits.RD0 = 1;
            break;
            
            case 2:
                PORTDbits.RD2 = 0;
                PORTDbits.RD1 = 1;
            break;
            
            case 3:
                PORTDbits.RD3 = 0;
                PORTDbits.RD2 = 1;
            break;
            
            case 4:
                PORTDbits.RD4 = 0;
                PORTDbits.RD3 = 1;
            break;
            
            case 5:
                PORTDbits.RD5 = 0;
                PORTDbits.RD4 = 1;
            break;
            
            case 6:
                PORTDbits.RD6 = 0;
                PORTDbits.RD5 = 1;
            break;
            
            case 7:
                PORTDbits.RD7 = 0;
                PORTDbits.RD6 = 1;
            break;
            
            case 8:
                PORTDbits.RD7 = 1;
            break;
            
            case 9:
                BBB = 0;
        }
    }
}

//******************************************************************************
// Configuración
//******************************************************************************

void setup(void) {
    TRISA5 = 1;
    ANSEL = 0;
    ANSELH = 0;
    TRISB = 0;
    PORTB = 0;
    TRISC = 0b00011000;
    TRISD = 0;
    PORTD = 0;
}

//******************************************************************************
// Funciones
//******************************************************************************
void PLUS(void){
    BBB++;
    __delay_ms(100);
    return;
}

void MINUS(void){
    BBB--;
    __delay_ms(100);
    return;
}
/*Precodigo
 */