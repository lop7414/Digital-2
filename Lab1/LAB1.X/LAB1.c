/*
 * File:   LAB1.c
 * Author: Francisco lopez
 *
 * Created on February 3, 2021, 6:54 PM
 */

//******************************************************************************
// librerías
//******************************************************************************

#include <xc.h>

// PIC16F887 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator: Crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
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

#define _XTAL_FREQ 8000000

#define LEDR PORTEbits.RE0
#define LEDA PORTEbits.RE1
#define LEDV PORTEbits.RE2

//******************************************************************************
// Variables
//******************************************************************************

char PLAYER1 = 0;
char PLAYER2 = 0;
char START = 0;
char START2 = 0;

//******************************************************************************
// Funciones
//******************************************************************************
void setup(void);
void semaforo(void);
void player1(void);
void player2(void);

//******************************************************************************
// Main
//******************************************************************************

void main(void) {

    setup();

    //**************************************************************************
    // Loop principal
    //**************************************************************************

    while (1) {

        if (PORTBbits.RB0 == 1){
            semaforo();
            PORTBbits.RB3 = 0;
            PORTBbits.RB4 = 0;
            START=1;
        }
        if (PORTBbits.RB1 == 0){
            if (PORTBbits.RB2 == 0){
                START2 = 1;
            }
        }
        if (START==1){
            if (START2==1){
                if (PORTBbits.RB1 == 1){
                    player1();
                    START2 = 0;
                }
        
                if (PORTBbits.RB2 == 1){
                    player2();
                    START2 = 0;
                }
            }
        }
        
        switch (PLAYER1){
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
                START = 0;
                PORTBbits.RB3 = 1;
                PLAYER1 = 0;
        }
        
        switch (PLAYER2){
            case 0:
                PORTD = 0;
            break;
            
            case 1:
                PORTDbits.RD0 = 1;
            break;
            
            case 2:
                PORTDbits.RD0 = 0;
                PORTDbits.RD1 = 1;
            break;
            
            case 3:
                PORTDbits.RD1 = 0;
                PORTDbits.RD2 = 1;
            break;
            
            case 4:
                PORTDbits.RD2 = 0;
                PORTDbits.RD3 = 1;
            break;
            
            case 5:
                PORTDbits.RD3 = 0;
                PORTDbits.RD4 = 1;
            break;
            
            case 6:
                PORTDbits.RD4 = 0;
                PORTDbits.RD5 = 1;
            break;
            
            case 7:
                PORTDbits.RD5 = 0;
                PORTDbits.RD6 = 1;
            break;
            
            case 8:
                PORTDbits.RD6 = 0;
                PORTDbits.RD7 = 1;
            break;
            
            case 9:
                START = 0;
                PORTBbits.RB4 = 1;
                PLAYER2 = 0;
        }
    
    if (PORTBbits.RB3 == 1){
        if (PORTBbits.RB0 == 1){
            return;
        }
    }
    if (PORTBbits.RB4 == 1){
        if (PORTBbits.RB0 == 1){
            return;
        }
    }
    } 
    
}

//******************************************************************************
// Configuración
//******************************************************************************

void setup(void) {
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
}

//******************************************************************************
// Funciones
//******************************************************************************

void semaforo(void) {
    PORTC = 0;
    PORTD = 0;
    PLAYER1 = 0;
    PLAYER2 = 0;
    LEDR = 1;
    __delay_ms(700);
    LEDR = 0;
    LEDA = 1;
    __delay_ms(200);
    LEDA = 0;
    LEDV = 1;
    __delay_ms(100);
    LEDV = 0;
}

void player1(void){
    PLAYER1++;
    __delay_ms(100);
    return;
}

void player2(void){
    PLAYER2++;
    __delay_ms(100);
    return;
}