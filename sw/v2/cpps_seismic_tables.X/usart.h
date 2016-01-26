#ifndef UART_H
#define	UART_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <xc.h>

char rx1 = 0;
char rx2 = 0;

char currentLine[256];
int index = 0;

char USART_TXempty(unsigned int channel);
char USART_RXdataReady(unsigned int channel);

// TX
void USART_putChar(char, unsigned int);
void USART_putCharLine(char, unsigned int);
void USART_putString(const char*, unsigned int);
void USART_putLine(const char*, unsigned int);
void UART_putInt(int, unsigned int);

// RX
char USART_getChar(unsigned int);
char* USART_getLine(unsigned int channel);

#ifdef	__cplusplus
}
#endif

#endif	/* UART_H */

