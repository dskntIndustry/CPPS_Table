/* Microcontroller MIPs (FCY) */
#define SYS_FREQ        64000000L
#define _XTAL_FREQ      64000000L
#define FCY             SYS_FREQ/4

/******************************************************************************/
/* System Function Prototypes                                                 */
/******************************************************************************/



void HW_init(void);
void OSC_init(void);
void VREF_init(void);
void GPIO_init(void);
void IRQ_init(void);
void TMR_init(unsigned int);
void ADC_init(unsigned int);
void USART_init(unsigned int, unsigned int);
void I2C_init(unsigned int);
void PWM_init(unsigned int, unsigned int);
void EEPROM_init(unsigned int);