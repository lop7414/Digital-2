/***********************************************************************************************************
 * Francisco Javier Lopez Menendez 1414
 * Universidad del Valle de Guatemala
 * Digital 2
 */
//**********************************************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"

#include "driverlib/uart.h"
#include "driverlib/pin_map.h"

uint32_t Status;
uint32_t input;
uint32_t LedR;
uint32_t LedG;
uint32_t LedB;


void UARTIntHandler(void){

    UARTIntClear(UART0_BASE, UARTIntStatus(UART0_BASE, true)); //input reset

    input = UARTCharGet(UART0_BASE); //Leer UART0


    if(input == 'r' && LedR == 0){ //encender/apagar LEDR
        UARTCharPut(UART0_BASE, 'R');
        UARTCharPut(UART0_BASE, ' ');
        UARTCharPut(UART0_BASE, 'O');
        UARTCharPut(UART0_BASE, 'N');
        UARTCharPut(UART0_BASE, ' ');
        LedR = 1;
        LedG = 0;
        LedB = 0;
    }

    else if(input == 'r' && LedR == 1){
        UARTCharPut(UART0_BASE, 'R');
        UARTCharPut(UART0_BASE, ' ');
        UARTCharPut(UART0_BASE, 'O');
        UARTCharPut(UART0_BASE, 'F');
        UARTCharPut(UART0_BASE, 'F');
        UARTCharPut(UART0_BASE, ' ');
        LedR = 0;
    }

    else if(input == 'g' && LedG == 0){//encender/apagar LEDG
        UARTCharPut(UART0_BASE, 'G');
        UARTCharPut(UART0_BASE, ' ');
        UARTCharPut(UART0_BASE, 'O');
        UARTCharPut(UART0_BASE, 'N');
        UARTCharPut(UART0_BASE, ' ');
        LedR = 0;
        LedG = 1;
        LedB = 0;
    }

    else if(input == 'g' && LedG == 1){
        UARTCharPut(UART0_BASE, 'G');
        UARTCharPut(UART0_BASE, ' ');
        UARTCharPut(UART0_BASE, 'O');
        UARTCharPut(UART0_BASE, 'F');
        UARTCharPut(UART0_BASE, 'F');
        UARTCharPut(UART0_BASE, ' ');
        LedG = 0;
    }

    else if(input == 'b' && LedB == 0){//encender/apagar LEDB
        UARTCharPut(UART0_BASE, 'B');
        UARTCharPut(UART0_BASE, ' ');
        UARTCharPut(UART0_BASE, 'O');
        UARTCharPut(UART0_BASE, 'N');
        UARTCharPut(UART0_BASE, ' ');
        LedR = 0;
        LedG = 0;
        LedB = 1;
    }

    else if(input == 'b' && LedB == 1){
        UARTCharPut(UART0_BASE, 'B');
        UARTCharPut(UART0_BASE, ' ');
        UARTCharPut(UART0_BASE, 'O');
        UARTCharPut(UART0_BASE, 'F');
        UARTCharPut(UART0_BASE, 'F');
        UARTCharPut(UART0_BASE, ' ');
        LedB = 0;
    }
}




int main(void){
    uint32_t ui32Period;
//Reloj
    SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);
//Perifericos
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
//Configuracion Timer 0
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
//Configurar UART
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

//Periodo de recepcion de variable
    ui32Period = SysCtlClockGet()/2;
    TimerLoadSet(TIMER0_BASE, TIMER_A, ui32Period -1);
//comenzar ints
    IntEnable(INT_TIMER0A);
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

//comenzar timer
    TimerEnable(TIMER0_BASE, TIMER_A);


    //GPIOPinConfigure(GPIO_PA0_U0RX);
    //GPIOPinConfigure(GPIO_PA1_U0TX);
//Pins UART
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

//Configuracion UART
    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

//UART
    IntMasterEnable(); //master enable de ints
    IntEnable(INT_UART0);
    UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);

    while(1){
    }
}

void Timer0IntHandler(void){
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT); //int reset

    if(Status == 1){ //status es la variable propia del timer0 que indica si está activo o no
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 0x00);
        Status = 0;
    }

    else{
        Status = 1;

        if(LedR == 1){
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1);
        }

        else if(LedG == 1){
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3);
        }

        else if(LedB == 1){
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);
        }
    }
}


