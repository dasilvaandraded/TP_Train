/*
 * SPI.c
 *
 *  Created on: 14 mars 2014
 *      Author: David
 */
#include "SPI.h"

/* CPOL = rising/failling edge
 * CPHA = clock phase control */
void Init_SPI_master_mode(uint8_t S_CPHA, uint8_t S_CPOL, uint32_t SPI_rate, uint8_t _16_or_8bits_com)
{
	if(_16_or_8bits_com == 8)
		LPC_SPI->SPCCR &=~ BIT_ENABLE; // set 8bits mode on SPI
	else
		LPC_SPI->SPCCR |= BIT_ENABLE; // set 16bits mode on SPI

	LPC_SPI->SPCCR |= 1 << MODE_SELECT; // configure spi on master mode
	LPC_SPI->SPCCR = SPI_rate / (SystemCoreClock / 4);
}

void Write_only_SPI_16bits()
{

}

void Write_Read_SPI_16bits()
{

}
