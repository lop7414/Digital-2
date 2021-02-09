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
#define _XTAL_FREQ 4000000
#endif

#ifndef LCD
#define LCD PORTD
#endif

#ifndef RS
#define RS RE0
#endif

#ifndef RW
#define RW RE1
#endif

#ifndef EN
#define EN RE2
#endif


#include <xc.h>


//LCD functions

void Lcd_Cmd(char a);

void Lcd_Clear(void);

void Lcd_Set_Cursor(char a, char b);

void Lcd_Init(void);

void Lcd_Write_Char(char a);

void Lcd_Write_String(char *a);

void Lcd_Shift_Right(void);

void Lcd_Shift_Left(void);

#endif