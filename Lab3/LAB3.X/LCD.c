/*
 * File:   LAB3.c
 * Author: francisco lopez
 *
 * se Adaptaron librerias de Ligo George
 * extraidas de la pagina https://electrosome.com/lcd-pic-mplab-xc8/#Example
 * 
 * Created on February 4, 2021, 7:54 PM
 */

#include "LCD.h"

void Lcd_Cmd(unsigned char a){
	LCD = 0xFF;
    LCD &= 0x80;
    RS = 0;
    RW = 1;
    EN = 0;
    __delay_ms(30);
    EN = 1;
    if (LCD == 0x80){
    EN = 0;
    __delay_ms(30);
    EN = 1;  
    }
    else{   
    }  
    LCD = a;
    RS = 0;
    RW = 0;
    EN = 1;
    __delay_ms(30);
    EN = 0;
}

void Lcd_Clear(void){
	Lcd_Cmd(1);
}

void Lcd_Set_Cursor(char a, char b){
	char temp;
	if(a == 1){
	  temp = 0x80 + b - 1;
		Lcd_Cmd(temp);
	}
	else if(a == 2)	{
        temp = 0xC0 + b - 1;
		Lcd_Cmd(temp);
	}
}

void Lcd_Init(){
    Lcd_Cmd(0x38);
    Lcd_Cmd(0x0C);
    Lcd_Cmd(0x01);
    Lcd_Cmd(0x06);
    Lcd_Cmd(0x80);
}

void Lcd_Write_Char(unsigned char a){
    LCD = 0xFF;
    LCD &= 0x80;
    RS = 0;
    RW = 1;
    EN = 0;
    __delay_ms(30);
    EN = 1;
    if (LCD == 0x80){
    EN = 0;
    __delay_ms(30);
    EN = 1;  
    }
    else{   
    } 
    LCD = a;
    RS = 1;
    RW = 0;
    EN = 1;
    __delay_ms(30);
    EN = 0; 
}

void Lcd_Write_String(char *a){
    while(*a != 0)
        Lcd_Write_Char(*a++);
}

void Lcd_Shift_Right(){
	Lcd_Cmd(0x1C);
}

void Lcd_Shift_Left(){
	Lcd_Cmd(0x18);
}