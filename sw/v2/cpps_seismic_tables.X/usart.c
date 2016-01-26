#include "usart.h"

unsigned char temp[256];

void USART_putChar(char c, unsigned int channel)
{
    switch(channel)
    {
        case 1:
            while(!TRMT1);
            TXREG1 = c;
            break;
        case 2:
            while(!TRMT2);
            TXREG2 = c;
            break;
        default:
            break;
    }
}

char USART_TXempty(unsigned int channel)
{
    switch(channel)
    {
        case 1:
            return TRMT1;

        case 2:
            return TRMT2;
        default:
            return -1;
    }
}

char USART_RXdataReady(unsigned int channel)
{
    switch(channel)
    {
        case 1:
            return RC1IF;

        case 2:
            return RC2IF;
        default:
            return -1;
    }
}

void USART_putCharLine(char c, unsigned int channel)
{
    switch(channel)
    {
        case 1:
            while(!TX1IF);
            TXREG1 = c;
            break;
        case 2:
            while(!TX2IF);
            TXREG2 = c;
            break;
        default:
            break;
    }
    USART_putLine("", channel);
}

void USART_putString(const char* string, unsigned int channel)
{
    switch(channel)
    {
        case 1:
            while((*string)!='\0')
            {
                //Wait for TXREG Buffer to become available
                while(!TX1IF);
                //Write data
                TX1REG=(*string);
                //Next goto char
                string++;
            }
            break;
        case 2:
            while((*string)!='\0')
            {
                //Wait for TXREG Buffer to become available
                while(!TX2IF);
                //Write data
                TX2REG=(*string);
                //Next goto char
                string++;
            }
            break;
        default:
            break;
    }
}

void USART_putLine(const char* line, unsigned int channel)
{
    USART_putString(line, channel);
    USART_putChar('\r', channel);
    USART_putChar('\n', channel);
}

void UART_putInt(int data, unsigned int channel)
{
    char buffer[128];
    sprintf(buffer, "%d", data);
    USART_putLine(buffer, channel);
}

char USART_getChar(unsigned int channel)
{
    switch(channel)
    {
        case 1:
            rx1 = RCREG1;
            return rx1;
        case 2:
            rx2 = RCREG2;
            return rx2;
        default:
            return -1;
    }
}

char* USART_getLine(unsigned int channel)
{
    int index = 0;
    unsigned char c;
    while(RC1IF)
    {
        c = USART_getChar(channel);
        if(c == '\r' || c == '\n' || c==0x00)
        {
            break;
        }
        else
        {
            temp[index] = c;
            index++;
        }
    }
    return temp;
}

