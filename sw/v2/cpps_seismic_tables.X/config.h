#ifndef CONFIG_H
#define	CONFIG_H

#ifdef	__cplusplus
extern "C" {
#endif

#define SERIAL (unsigned int)1
#define USER_ANALOG_INPUT (unsigned int)0

//Base address
#define EXT_EEPROM_I2C_ADD (unsigned char)0x53
#define EXT_EEPROM_I2C_CHANNEL (unsigned int)1

#define UMIN 0;
#define UMAX 1;

#ifdef	__cplusplus
}
#endif

#endif	/* CONFIG_H */