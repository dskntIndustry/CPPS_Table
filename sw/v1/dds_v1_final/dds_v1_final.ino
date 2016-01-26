/***************************************************************************//**
* \file   dds_v1_final.ino
* \author fom
* \date   10.11.2015
* \brief  main arduino program
*
* This files contains at least the setup and loop functions for the arduino 
* program
*******************************************************************************/
#include "userConfiguration.h"
#include "initHW.h"
#include "time.h"
#include "adc.h"
#include "pwm.h"
#include "serial.h"
//#include "eeprom.h"

// External Libs
#include "avr/pgmspace.h"
#include "Bounce.h"
#include "Metro.h"



//------------------------------------------------------------------------------
// Global Variables
//
// General Variables
boolean verbose  = false;
boolean setup_on = false;
boolean startup = true;

// PWM
double pwm_frequency = CFG_FREQUENCY_MIN;
double pwm_amplitude = 1;

// Time related Objects
Bounce startButton = Bounce(CFG_BUT_START, CFG_BUT_DEBOUNCE);
#ifdef CFG_RodShaking
Bounce setupButton = Bounce(CFG_BUT_SETUP, CFG_BUT_DEBOUNCE);
#endif

// Time object for auto shutoff
Metro metroShutoff = Metro(CFG_AUTO_SHUTOFF);

// Potentiometer Variables
Metro metroButtons = Metro(CFG_INPUT_REFRESH);
word pot_amplitude;
word pot_frequency;
word pot_setup;
byte pot_pins;

//------------------------------------------------------------------------------
// Functions
//
/***************************************************************************//**
* \brief read all inputs
* 
* Read all digital, analog button attached to the system on the given module 
* configuration
*******************************************************************************/
void readInputs() {
  // Read analog buttons
  #ifdef CFG_HouseBuilder
    pot_amplitude = adcRead(CFG_POT_AMPLITUDE);
  #endif
  pot_frequency = adcRead(CFG_POT_FREQUENCY);

  // Read digital buttons
  #ifdef CFG_RodShaking
    pot_pins = 0;
    if (digitalRead(CFG_POT_PIN1))
      pot_pins &= ~(1 << 0); // clear bit
    else
      pot_pins |= 1 << 0;    // set bit
    if (digitalRead(CFG_POT_PIN2))
      pot_pins &= ~(1 << 1); // clear bit
    else
      pot_pins |= 1 << 1;    // set bit
    if (digitalRead(CFG_POT_PIN4))
      pot_pins &= ~(1 << 2); // clear bit
    else
      pot_pins |= 1 << 2;    // set bit
    if (digitalRead(CFG_POT_PIN8))
      pot_pins &= ~(1 << 3); // clear bit
    else
      pot_pins |= 1 << 3;    // set bit
    
    pot_setup = adcRead(CFG_POT_SETUP);
    setupButton.update();
  #endif

  startButton.update();
}

//------------------------------------------------------------------------------
// Setup & Loop
//
/***************************************************************************//**
* \brief Arduino Setup
* 
* This function will be called once at startup of the system
*******************************************************************************/
void setup() {
  pinSetup();
  serialSetup();
  timer_setup();
  pwmReadSettings();
}

/***************************************************************************//**
* \brief Arduino Loop
* 
* This function will be called over and over, it's the main loop
*******************************************************************************/
void loop() {

  // read inputs
  readInputs();
  
  // Check start button
  if (startButton.risingEdge()) {
    pwmToggle();
    digitalWrite(CFG_LED_START, pwm_on);

    // Output
    if (pwm_on)
      Serial.println("\n------------- Enable PWM ------------");
    else
      Serial.println("\n------------ Disable PWM ------------");
  }

  // Check setup button
  #ifdef CFG_RodShaking
  if (setupButton.risingEdge()) {
    if (setup_on)
      setup_on = false;
    else
      setup_on = true;
    digitalWrite(CFG_LED_SETUP, setup_on);

    // Output
    if (setup_on) {
      Serial.println("\n-------- Entering Setup Mode --------");
      pwmReadSettings();
    }
    else {
      Serial.println("\n---------- Exit Setup Mode ----------");
      pwmSaveSettings();
    }
  }
  #endif

// Change sinus frequency
  if (metroButtons.check() == 1) {
    #ifdef CFG_RodShaking
      // if in Setup mode
      if (setup_on) {
        // save frequency
        pwm_frequency = ConvertPotToFrequency(pot_setup);
        pwm_amplitude = ConvertFrequencyToAmplitude(pwm_frequency);
        setSignalFrequency(pwm_frequency);

        pwmChangeSettings(pot_pins, pwm_frequency);
        if (verbose) {
          Serial.print("Pot Pins Frequency: ");
          Serial.println(pot_pins,HEX);
          Serial.print("PWM Frequency: ");
          printDoubleln(pwm_frequency);
          Serial.print("PWM Amplitude: ");
          printDoubleln(pwm_amplitude);
        }
      }
    #endif
    // if PWM enabled
    if (pwmStatus()) {
      #ifdef CFG_HouseBuilder
        pwm_frequency = ConvertPotToFrequency(pot_frequency);

        setSignalFrequency(pwm_frequency);

        if (verbose) {
          Serial.print("Pot Frequency: ");
          Serial.println(pot_frequency);
          Serial.print("PWM Frequency: ");
          printDoubleln(pwm_frequency);
          Serial.print("PWM Amplitude: ");
          printDoubleln(pwm_amplitude);
          int val = (pgm_read_byte_near(square_half_1));
          Serial.println(val);
          val = (int)(val * pwm_amplitude);
          Serial.println(val);

        }
      #endif
      #ifdef CFG_RodShaking
        pwm_frequency = ConvertPosToFrequency(pot_pins);
        pwm_amplitude = ConvertFrequencyToAmplitude(pwm_frequency);
        setSignalFrequency(pwm_frequency);

        if (verbose) {
          Serial.print("Pot Pins Frequency: ");
          Serial.println(pot_pins,HEX);
          Serial.print("PWM Frequency: ");
          printDoubleln(pwm_frequency);
          Serial.print("PWM Amplitude: ");
          printDoubleln(pwm_amplitude);
        }
      #endif

      if (metroShutoff.check() == 1) // Check for auto shutoff
        if (!setup_on) {             // do not autoshutoff in setup mode
          pwmStop();
          digitalWrite(CFG_LED_START, pwmStatus());
        }
      }
    }
}
