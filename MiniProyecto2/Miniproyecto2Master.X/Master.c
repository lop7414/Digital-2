/*
 * File:   Master.c
 * Author: Francisco Lopez
 *
 * se Adaptaron librerias de Ligo George
 * extraidas de la pagina https://electrosome.com/lcd-pic-mplab-xc8/#Example
 * 
 * Created on March 7, 2021, 2:53 PM
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

#define _XTAL_FREQ 8000000

#include "pic16f887.h"
#include "I2C.h"
#include "UART.h"
#include "OSC.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//******************************************************************************
// Variables
//******************************************************************************
int     sensor;
int     Enviar;
int     DatoIntermedio;

int     O;
int     Destination;

char    COMPARE = 0;
//******************************************************************************
// Funciones
//******************************************************************************
void setup(void);
int Read(int n);

//******************************************************************************
// Main
//******************************************************************************

void __interrupt() ISR(void){
    if (RCIF==1){
        O = Read ((int)RCREG);
        itoa(COMPARE,O,10);
        RCIF=0;
    }
}

void main(void) {
    
    setup();
    I2C_Init(100000);
    InitOSC(7);
    SERIAL_Init();
    
    //**************************************************************************
    // Loop principal
    //**************************************************************************

    while (1) {
        
        if (COMPARE==0){
            PORTDbits.RD6 = 1;
            PORTDbits.RD7 = 0;
        }
        else {
            PORTDbits.RD6 = 0;
            PORTDbits.RD7 = 1;
        }
        
        
        I2C_M_Start();
        sensor = I2C_M_Read(0);
        I2C_M_Stop();
        
        __delay_ms(200);
        
        Enviar = (sensor*30.0)/255.0;
//        Enviar = (DatoIntermedio)+25;
        
        UART_Write(Enviar);
        __delay_ms(10);
         
        COMPARE = UART_READ();
        __delay_ms(10);
    }
    
}

//******************************************************************************
// Configuración
//******************************************************************************

void setup(void) {
    TRISA=0;
    TRISB=0;
    TRISC=0;
    TRISD=0;
    TRISE=0;
    
    PORTA=0;
    PORTB=0;
    PORTC=0;
    PORTD=0;
    PORTE=0;
}

//******************************************************************************
// Funciones
//******************************************************************************
int Read (int  n){
    Destination = n;
    return ((Destination)*1);
}


/*Precodigo
 * En este caso se debera conectar por I2C a un sensor de temperatura
 * La idea es agarrar los datos provenientes del sensor y meterlos en una variable
 * Temp*
 * 
 * Esta variable se debera de mandar por UART al ESP32
 * 
 * El Pic tambien debera tener una variable llamada estado para la luz led
 * 
 * Una interrupcion se encargara de recibir datos por UART y cambiar el valor de
 * Estado
 * 
 * Dependiendo del valor (0, 1) el estado enciende una led o la otra
 * 
 * 
 * En arduino la programacion es mas acerca de mover datos de un lado a otro
 * 
 * Se debe recibir el dato pro UART y mandarlo por Wifi
 * 
 * Se debe recibir el dato por Wifi y se debe enviar por UART
 * 
 *
 * Adafruit solo despliega datos en un feed y manda el dato de un boton por otro
 *  feed
 */