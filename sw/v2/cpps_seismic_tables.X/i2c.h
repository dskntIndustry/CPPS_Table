/*
 * File:   i2c.h
 * Author: uadmin
 *
 * Created on 9. décembre 2015, 11:32
 */

#ifndef I2C_H
#define	I2C_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>

unsigned char i2cread;
unsigned int a = 0;
unsigned char data = 'a';
char str[32];

void I2C_start(unsigned int);
void I2C_restart(unsigned int);
void I2C_stop(unsigned int);

void I2C_ack(unsigned int);
void I2C_nack(unsigned int);
void I2C_wait(unsigned int);

void I2C_writeByte(unsigned char, unsigned int);
unsigned char I2C_readByte(unsigned int, unsigned char);

void I2C_putByteAtAddress(unsigned int, unsigned char, unsigned char, unsigned int, unsigned char);
//void I2C_putWordAtAddress(unsigned int, unsigned char, unsigned int, unsigned char, unsigned int);

void I2C_putBytesPage(unsigned int channel, unsigned char device_address, unsigned char page, unsigned int address, unsigned char byte);

unsigned char I2C_getByteFromAddress(unsigned int, unsigned char, unsigned char, unsigned int);
//unsigned int I2C_getWordFromAddress(unsigned int, unsigned char, unsigned int);

unsigned char I2C_getBytesPage(unsigned int channel, unsigned char device_address, unsigned char page, unsigned int address);

void I2C_writeEEPROMPage(unsigned char);
void I2C_readEEPROMPage(unsigned char);

#ifdef	__cplusplus
}
#endif

#endif	/* I2C_H */