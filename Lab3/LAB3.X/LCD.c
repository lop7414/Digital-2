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

void Lcd_Port(char a){
	if(a & 1)
		D0 = 1;
	else
		D0 = 0;
    
    if(a & 2)
		D1 = 1;
	else
		D1 = 0;
    
    if(a & 4)
		D2 = 1;
	else
		D2 = 0;
    
    if(a & 8)
		D3 = 1;
	else
		D3 = 0;
    
    if(a & 0x10)
		D4 = 1;
	else
		D4 = 0;

	if(a & 0x20)
		D5 = 1;
	else
		D5 = 0;

	if(a & 0x40)
		D6 = 1;
	else
		D6 = 0;

	if(a & 0x80)
		D7 = 1;
	else
		D7 = 0;
}

void Lcd_Cmd(char a){
	RS = 0;             // => RS = 0
	Lcd_Port(a);
	EN = 1;            // => E = 1
    __delay_ms(4);
    EN = 0;            // => E = 0
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
  Lcd_Port(0x00);
   __delay_ms(20);
  Lcd_Cmd(0x30);
	__delay_ms(5);
  Lcd_Cmd(0x30);
	__delay_ms(11);
  Lcd_Cmd(0x30);
  /////////////////////////////////////////////////////
  Lcd_Cmd(0x38);
  Lcd_Cmd(0x08); //0x10 tentativamente
  Lcd_Cmd(0x01);
  Lcd_Cmd(0x06);
}

void Lcd_Write_Char(char a){
   char temp;
   temp = a&0xFF;
   RS = 1;             // => RS = 1
   Lcd_Port(temp);
   EN = 1;
   __delay_us(40);
   EN = 0;
}

void Lcd_Write_String(char *a){
	int i;
	for(i=0;a[i]!='\0';i++)
	   Lcd_Write_Char(a[i]);
}

void Lcd_Shift_Right(){
	Lcd_Cmd(0x1C);
}

void Lcd_Shift_Left(){
	Lcd_Cmd(0x18);
}