/*
 * police.h
 *
 *  Created on: 14 mars 2014
 *      Author: David
 */

#ifndef POLICE_H_
#define POLICE_H_

#include "LPC17xx.h"
#include <cr_section_macros.h>
#include "Ecran.h"



void Write_char(char character, uint8_t x,uint8_t y, uint8_t *color);

#endif /* POLICE_H_ */