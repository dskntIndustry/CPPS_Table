/* 
 * File:   utils.h
 * Author: uadmin
 *
 * Created on 18. janvier 2016, 08:45
 */

#ifndef UTILS_H
#define	UTILS_H

#ifdef	__cplusplus
extern "C" {
#endif
    
unsigned char setBit(unsigned char, unsigned int);
unsigned char clearBit(unsigned char, unsigned int);
unsigned char giveBitValue(unsigned char, unsigned int, unsigned int);

#ifdef	__cplusplus
}
#endif

#endif	/* UTILS_H */

