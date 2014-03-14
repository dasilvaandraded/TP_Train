/*
===============================================================================
 Name        : main.c
 Author      : 
 Version     :
 Copyright   : Copyright (C) 
 Description : main definition
===============================================================================
*/

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#include "Ecran.h"
#endif


int main(void) {

	Init_display();
	Set_cursor(0,0);
	//Create_partial_screen(50, 100, 50,100);
	while(1) {
		Write_pixel(0,255,0);
	}
	return 0 ;
}