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
#include "LCD.h"
#include "ADC.h"
#include "UART.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//******************************************************************************
// Variables
//******************************************************************************
char BBB = 0;
char START = 0;

char    Contador;
char    COMPARE[5];
//******************************************************************************
// Funciones
//******************************************************************************
void setup2(void);
void PLUS(void);
void MINUS(void);
//******************************************************************************
// Main
//******************************************************************************

void main2(void) {
    
    setup2();
    
//**************************************************************************
// Loop principal
//**************************************************************************
        
    while (1) {
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
                PORTC = 0;
            break;
            
            case 1:
                PORTCbits.RC0 = 1;
            break;
            
            case 2:
                PORTCbits.RC0 = 0;
                PORTCbits.RC1 = 1;
            break;
            
            case 3:
                PORTCbits.RC1 = 0;
                PORTCbits.RC2 = 1;
            break;
            
            case 4:
                PORTCbits.RC2 = 0;
                PORTCbits.RC3 = 1;
            break;
            
            case 5:
                PORTCbits.RC3 = 0;
                PORTCbits.RC4 = 1;
            break;
            
            case 6:
                PORTCbits.RC4 = 0;
                PORTCbits.RC5 = 1;
            break;
            
            case 7:
                PORTCbits.RC5 = 0;
                PORTCbits.RC6 = 1;
            break;
            
            case 8:
                PORTCbits.RC6 = 0;
                PORTCbits.RC7 = 1;
            break;
            
            case 9:
                BBB = 0;
        }
        
         UART_Write(BBB);//place holder
         
    }
}

//******************************************************************************
// Configuraci�n
//******************************************************************************

void setup2(void) {
    TRISE = 0;
    PORTE = 0;
    ANSEL = 0;
    ANSELH = 0;
    TRISB = 0;
    PORTB = 0;
    TRISC = 0;
    PORTC = 0;
    TRISD = 0;
    PORTD = 0;
    
    OSCCONbits.IRCF = 0b110; //4Mhz
    OSCCONbits.OSTS= 0;
    OSCCONbits.HTS = 0;
    OSCCONbits.LTS = 0;
    OSCCONbits.SCS = 1; 
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