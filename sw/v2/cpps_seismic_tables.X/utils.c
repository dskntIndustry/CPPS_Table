#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#elif defined(__18CXX)
    #include <p18cxxx.h>    /* C18 General Include File */
#endif

#if defined(__XC) || defined(HI_TECH_C)

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */

#endif

#include "utils.h"

unsigned char setBit(unsigned char reg, unsigned int bitno)
{
    reg = (1<<bitno);
    return  reg;
}

unsigned char clearBit(unsigned char reg, unsigned int bitno)
{
    reg = (0<<bitno);
    return  reg;
}

unsigned char giveBitValue(unsigned char reg, unsigned int bitno, unsigned int v)
{
    reg = (v<<bitno);
    return  reg;
}
