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
#include "police.h"
#endif


int main(void) {

	Init_display();
	Set_cursor(0,0);
	Create_partial_screen(0, 319, 0, 239);

	/* Taille écran = 320x240 */
	// All screen unlock
	// Create_partial_screen(0, 319, 0, 239);
	int var;
	for (var = 0; var < 320*240; ++var) {
		Write_pixel(0,0,0);
	}

	uint8_t color[3] = {255,0,0};
	Write_char('A',0,0,color);
	while(1) {
		//Write_pixel(0,0,0);
	}
	return 0 ;
}
