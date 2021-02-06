//LCD Functions Developed by electroSome
/*
 * File:   LAB3.c
 * Author: francisco lopez
 *
 * se Adaptaron librerias de Ligo George
 * extraidas de la pagina https://electrosome.com/lcd-pic-mplab-xc8/#Example
 * 
 * Created on February 4, 2021, 7:54 PM
 */

#ifndef LCD_H
#define LCD_H

#ifndef _XTAL_FREQ
#define _XTAL_FREQ 8000000
#endif

#define RS PORTEbits.RE0
#define EN PORTEbits.RE1
#define D0 PORTDbits.RD0
#define D1 PORTDbits.RD1
#define D2 PORTDbits.RD2
#define D3 PORTDbits.RD3
#define D4 PORTDbits.RD4
#define D5 PORTDbits.RD5
#define D6 PORTDbits.RD6
#define D7 PORTDbits.RD7

#ifndef RS
#define RS PORTCbits.RC6
#endif

#ifndef EN
#define EN RC7
#endif

#ifndef D0
#define D0 RD0
#endif

#ifndef D1
#define D1 RD1
#endif

#ifndef D2
#define D2 RD2
#endif

#ifndef D3
#define D3 RD3
#endif

#ifndef D4
#define D4 RD4
#endif

#ifndef D5
#define D5 RD5
#endif

#ifndef D6
#define D6 RD6
#endif

#ifndef D7
#define D7 RD7
#endif

#include <xc.h>


//LCD functions

void Lcd_Port(char a);

void Lcd_Cmd(char a);

void Lcd_Clear(void);

void Lcd_Set_Cursor(char a, char b);

void Lcd_Init(void);

void Lcd_Write_Char(char a);

void Lcd_Write_String(char *a);

void Lcd_Shift_Right(void);

void Lcd_Shift_Left(void);

#endif