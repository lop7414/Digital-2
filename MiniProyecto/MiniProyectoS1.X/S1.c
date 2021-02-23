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
#include "ADC.h"
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

char    Ready;
char    slave;
//******************************************************************************
// Funciones
//******************************************************************************
void setup(void);

//******************************************************************************
// Main
//******************************************************************************
void __interrupt() ISR(void){
    if (SSPIF == 1){
        slave = SPI_Read();
        SPI_Write(POT1SC);
        SSPIF = 0;
    }
}


void main(void) {
    
    setup();
    
//**************************************************************************
// Loop principal
//**************************************************************************
        
    while (1) {
        ADC_Init();
        GIE = 1;
        PEIE = 1;
        SSPIF = 0;
        SSPIE = 1;
        ADCON1 = 0x07;
        
        SPI_Init(SPI_SLAVE_SS_EN, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW, SPI_IDLE_2_ACTIVE);
        
        
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
    }
}

//******************************************************************************
// Configuración
//******************************************************************************

void setup(void) {
    ANSEL = 0b00100001;
    ANSELH= 0b00000000;
    ADCON1 = 0x07;
    TRISA = 0b00100001;
    TRISB = 0b00000000; 
    TRISD = 0b00000000;
    TRISC = 0b00011000;
    TRISE = 0;
    
    PORTA = 0;
    PORTB = 0;
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
 */