/*
 * File:   eeprom.h
 * Author: uadmin
 *
 * Created on 7. décembre 2015, 09:04
 */

#ifndef EEPROM_H
#define	EEPROM_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>

    unsigned char EEPROM_readByte(unsigned int);
    unsigned int EEPROM_readWord(unsigned int);

    void EEPROM_writeByte(char, unsigned int);
    void EEPROM_writeWord(int, unsigned int);


#ifdef	__cplusplus
}
#endif

#endif	/* EEPROM_H */

