/*
 * File:   LAB3.c
 * Author: francisco lopez
 *
 * se Adaptaron librerias de Ligo George
 * extraidas de la pagina https://electrosome.com/lcd-pic-mplab-xc8/#Example
 * 
 * Created on February 4, 2021, 7:54 PM
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
// librerías
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
uint8_t adc;

float   voltaje;
int     V1;
int     POT1A;
char    POT1SA[5];
int     POT1B;
char    POT1SB[5];
int     POT1C;
char    POT1SC[5];
char    PUNTO1[5];

float   voltaje2;
int     V2;
int     POT2A;
char    POT2SA[5];
int     POT2B;
char    POT2SB[5];
int     POT2C;
char    POT2SC[5];
char    PUNTO2[5];

char    Contador;
char    COMPARE[5];

//******************************************************************************
// Funciones
//******************************************************************************
void setup(void);

//******************************************************************************
// Main
//******************************************************************************
void __interrupt() ISR(void){
    if (RCIF==1){
        CONTADOR ((int)RCREG,COMPARE);
        
        RCIF=0;
    }
}

void main(void) {
    
    setup();
    
    //**************************************************************************
    // Loop principal
    //**************************************************************************

    while (1) {
        Lcd_Init();
        SERIAL_Init();
        ADC_Init();
        
        Lcd_Write_String("S1    S2    S3  ");
        
        __delay_ms(1);
        adc=ADC_Read(0,0);
        
        voltaje = (adc*5.0)/255.0;
        V1 = (voltaje)*100;
        POT1A = V1%10;
        itoa(POT1SA,POT1A,10);
        POT1B = (V1/10)%10;
        itoa(POT1SB,POT1B,10);
        POT1C = (V1/100)%10;
        itoa(POT1SC,POT1C,10);
        strcpy(PUNTO1,".");
        strcat(POT1SB,POT1SA);
        strcat(PUNTO1,POT1SB);
        strcat(POT1SC,PUNTO1);
        
        __delay_us(600);
        adc=ADC_Read(1,1);
        
        voltaje2 = adc*5.0/255.0;
        V2 = (voltaje2)*100;
        POT2A = V2%10;
        itoa(POT2SA,POT2A,10);
        POT2B = (V2/10)%10;
        itoa(POT2SB,POT2B,10);
        POT2C = (V2/100)%10;
        itoa(POT2SC,POT2C,10);
        strcpy(PUNTO2,".");
        strcat(POT2SB,POT2SA);
        strcat(PUNTO2,POT2SB);
        strcat(POT2SC,PUNTO2);
        
        Lcd_Cmd(0xC0); 
        Lcd_Write_String(POT1SC);
        Lcd_Write_String(" ");
        Lcd_Write_String(POT2SC);
        Lcd_Write_String(" ");
        Lcd_Write_String(COMPARE);
        
    }
    
}

//******************************************************************************
// Configuración
//******************************************************************************

void setup(void) {
    ANSEL = 0b00001001;
    ANSELH= 0b00000000;
    TRISA = 0b00001001;
    TRISB = 0b00000000; 
    TRISD = 0b00000000;
    TRISE = 0;
    
    PORTA = 0;
    PORTB = 0;
    PORTC = 0;
    PORTD = 0;
    PORTE = 0;
    
    OSCCONbits.IRCF = 0b110; //4Mhz
    OSCCONbits.OSTS= 0;
    OSCCONbits.HTS = 0;
    OSCCONbits.LTS = 0;
    OSCCONbits.SCS = 1; 
}

//******************************************************************************
// Funciones
//******************************************************************************



/*Precodigo
 * 
 * Con libreria ADC leer RB0 y RB1 y guardar datos en variables
 * Abrir comunicacion USART con libreria
 * Codigo simple de sumar 1 o restar 1 a una variable "contador"
 * Escribir String " S1:    S2:    S3: "
 * pasar ese valor a puerto D para escribir en LCD RB0
 * Escribir String "V "
 * pasar ese valor a puerto D para escribir en LCD RB1
 * Escribir String "V "
 * Escribir variable de "contador"
 * Escribir String "V "
 */