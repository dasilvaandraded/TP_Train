/**
 * @file uart.c
 * @author Da Silva Andrade David, Antoine Berger, Dos Santos Rafael
 * @version 1.0
 * @date 19 June 2014
 * @brief Contain all functions to initialize, write and read on UART 0 and 3
 */
#include "LPC17xx.h"
#include "uart.h"

/**
 * Initialize UART0 port, setup pin select,
 * clock, parity, stop bits, FIFO, etc.
 * @param baudrate UART0 baudrate [bit/s]
 */
void uart0_init(uint32_t baudrate) {
	uint32_t Fdiv;
	uint32_t pclkdiv, pclk;

	LPC_PINCON->PINSEL0 &= ~0x000000F0;
	LPC_PINCON->PINSEL0 |= 0x00000050; /* RxD0 is P0.3 and TxD0 is P0.2 */
	/* By default, the PCLKSELx value is zero, thus, the PCLK for
	 all the peripherals is 1/4 of the SystemFrequency. */
	/* Bit 6~7 is for UART0 */
	pclkdiv = (LPC_SC->PCLKSEL0 >> 6) & 0x03;
	switch (pclkdiv) {
	case 0x00:
	default:
		pclk = SystemCoreClock / 4;
		break;
	case 0x01:
		pclk = SystemCoreClock;
		break;
	case 0x02:
		pclk = SystemCoreClock / 2;
		break;
	case 0x03:
		pclk = SystemCoreClock / 8;
		break;
	}

	LPC_UART0->LCR = 0x83; /* 8 bits, no Parity, 1 Stop bit */
	Fdiv = (pclk / 16) / baudrate; /* setup baud rate */
	LPC_UART0->DLM = Fdiv / 256;
	LPC_UART0->DLL = Fdiv % 256;
	LPC_UART0->LCR = 0x03; /* DLAB = 0 */
	LPC_UART0->FCR = 0x07; /* Enable and reset TX and RX FIFO. */
}

/**
 * Initialize UART3 port, setup pin select,
 * clock, parity, stop bits, FIFO, etc.
 * @param baudrate UART3 baudrate [bit/s]
 */
void uart3_init(uint32_t baudrate) {
	uint32_t Fdiv;
	uint32_t pclkdiv, pclk;

	LPC_SC->PCONP |= 0x1 << 25;			// Enable UART 3

	// Enable pin TXD3 and RXD3
	LPC_PINCON->PINSEL9 |= 0b1111 << 24;
	/* By default, the PCLKSELx value is zero, thus, the PCLK for
	 all the peripherals is 1/4 of the SystemFrequency. */
	/* Bit 6~7 is for UART0 */
	pclkdiv = (LPC_SC->PCLKSEL0 >> 6) & 0x03;
	switch (pclkdiv) {
	case 0x00:
	default:
		pclk = SystemCoreClock / 4;
		break;
	case 0x01:
		pclk = SystemCoreClock;
		break;
	case 0x02:
		pclk = SystemCoreClock / 2;
		break;
	case 0x03:
		pclk = SystemCoreClock / 8;
		break;
	}

	LPC_UART3->LCR = 0x83; /* 8 bits, no Parity, 1 Stop bit */
	Fdiv = (pclk / 16) / baudrate; /* setup baud rate */
	LPC_UART3->DLM = Fdiv / 256;
	LPC_UART3->DLL = Fdiv % 256;
	LPC_UART3->LCR = 0x03; /* DLAB = 0 */
	LPC_UART3->FCR = 0x07; /* Enable and reset TX and RX FIFO. */
}

/**
 * Send data on UART0
 * @param data Pointer on the datas to be sent
 * @param baudrate Number of bytes to send
 */
void uart0_send(char *data, uint32_t length) {
	int var;
	for (var = 0; var < length; var++) {
		while (!(LPC_UART0->LSR & 0x1 << 5))
			;
		LPC_UART0->THR = data[var];
	}
}

/**
 * Read data from UART0
 * @param data Pointer that store the data read from UART 0
 * @param length Number of bytes to read
 */
uint32_t uart0_read(char *data, uint32_t length) {
	uint32_t var;
	for (var = 0; var < length; var++) {
		// Read Rx buffer while we have data inside
		if ((LPC_UART0->LSR & 0x1) == 1)
			data[var] = LPC_UART0->RBR;
		else
			break;
	}
	return var;
}

/**
 * Read one byte from UART0
 * @param ch Pointer that store the byte read from UART 0
 */
uint32_t uart0_read_one_char(char *ch) {
	if ( LPC_UART0->LSR & (LSR_OE | LSR_PE | LSR_FE | LSR_RXFE | LSR_BI)) {
		/* Clear errors */
		ch[0] = LPC_UART0->LSR;
		ch[0] = LPC_UART0->RBR;
		return 0;
	}
	if ( LPC_UART0->LSR & LSR_RDR) /* Receive Data Ready */
	{
		*ch = LPC_UART0->RBR;
		return 1;
	}
	return 0;
}

/**
 * Send data on UART3
 * @param data Pointer on the datas to be sent
 * @param baudrate Number of bytes to send
 */
void uart3_send(char *data, uint32_t length) {
	int var;
	for (var = 0; var < length; var++) {
		while (!(LPC_UART3->LSR & 0x1 << 5))
			;
		LPC_UART3->THR = data[var];
	}
}

/**
 * Read data from UART3
 * @param data Pointer that store the data read from UART 3
 * @param length Number of bytes to read
 */
uint32_t uart3_read(char *data, uint32_t length) {
	uint32_t var;
	for (var = 0; var < length; var++) {
		// Read Rx buffer while we have data inside
		if ((LPC_UART3->LSR & 0x1) == 1)
			data[var] = LPC_UART3->RBR;
		else
			break;
	}
	return var;
}

/**
 * Read one byte from UART3
 * @param ch Pointer that store the byte read from UART 3
 */
uint32_t uart3_read_one_char(char *ch) {
	if ( LPC_UART3->LSR & (LSR_OE | LSR_PE | LSR_FE | LSR_RXFE | LSR_BI)) {
		/* Clear errors */
		ch[0] = LPC_UART3->LSR;
		ch[0] = LPC_UART3->RBR;
		return 0;
	}
	if ( LPC_UART3->LSR & LSR_RDR) /* Receive Data Ready */
	{
		ch[0] = LPC_UART3->RBR;
		return 1;
	}
	return 0;
}
