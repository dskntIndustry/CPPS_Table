/***************************************************************************//**
* \file   hwsetup.h
* \author fom
* \date   10.11.2015
* \brief  set hw up and running
*
*******************************************************************************/
#include "Arduino.h"
#include "constants.h"

//#define CFG_ROD
#define CFG_HOUSE

//------------------------------------------------------------------------------
//Global configuration (for all simulations)
//------------------------------------------------------------------------------
#define BUT_START			0
#define LED_START			2

// in-phase PWM output
#define PWM_OUTPUT_0		9
// anti-phase PWM output
#define PWM_OUTPUT_1		11

//#define PWM_DRIVER_EN		11

//------------------------------------------------------------------------------
//Special pin configuration for simulation
//------------------------------------------------------------------------------
#ifdef CFG_HOUSE
	//#define POT_AMPLITUDE	A0
	#define FREQUENCY_POT	A1		
#endif

#ifdef CFG_ROD
	#define POT_PIN1		5
	#define POT_PIN2 		6
	#define POT_PIN4 		7
	#define POT_PIN8 		8

	#define BUT_SETUP		3
	
	#define LED_SETUP		4
	#define POT_SETUP		A2
#endif

//------------------------------------------------------------------------------
//Default startup pin values
//------------------------------------------------------------------------------

void initPins()
{
	
	pinMode(BUT_START, INPUT_PULLUP);
	pinMode(LED_START, OUTPUT);
	digitalWrite(LED_START, LOW);
  
  #ifdef CFG_ROD
    // 10 pos Pot, 2 button and 2 leds for Rod shaker
/*    pinMode(CFG_POT_PIN1, INPUT_PULLUP);
    pinMode(CFG_POT_PIN2, INPUT_PULLUP);
    pinMode(CFG_POT_PIN4, INPUT_PULLUP);
    pinMode(CFG_POT_PIN8, INPUT_PULLUP);
    pinMode(CFG_BUT_SETUP, INPUT_PULLUP);
    pinMode(CFG_LED_SETUP, OUTPUT);
    digitalWrite(CFG_LED_SETUP, LOW);*/
  #endif
  
    pinMode(PWM_OUTPUT_0, OUTPUT);
    pinMode(PWM_OUTPUT_1, OUTPUT);
}

void initSerialOutput()
{
	// Open serial communications and wait for port to open:
	Serial.begin(SERIAL_BAUD_RATE);
	// wait for connect
	while(!Serial){};

	delay(1000);
	// Welcome Message
	Serial.println("Hello");
	#ifdef ROD
	Serial.println("Config: ROD");
	#endif
	#ifdef HOUSE
	Serial.println("Config: HOUSE");
	#endif

	#if defined (__AVR_ATmega168__)
		Serial.println("uC: AVR ATmega168");
	#endif
	#if defined (__AVR_ATmega328P__)
		Serial.println("uC: AVR ATmega328P");
	#endif
	#if defined (__AVR_ATmega32U4__)
		Serial.println("uC: AVR ATmega32U4");
	#endif

	Serial.flush();
}
