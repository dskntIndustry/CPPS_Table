/***************************************************************************//**
* \file   pwm.h
* \author fom
* \date   10.11.2015
* \brief  all pwm related stuff
*
* This files contains all functions concerning time and PWM
*******************************************************************************/
#include "eeprom.h"
#include "arduino.h"
#include "avr/pgmspace.h"

boolean pwm_on = false;
boolean pwm_on_old = false;

settings_t settings_local;
/***************************************************************************//**
* \brief start pwm generation
* 
* To start the pwm generation, timer2 will be enabled
*******************************************************************************/
boolean pwmStart() {
  // enable Timer Interrupt
  //digitalWrite(CFG_EN_DRIVER, HIGH);
  #if defined (__AVR_ATmega168__) || defined (__AVR_ATmega328P__)
    setbit(TIMSK2,TOIE2);
    #ifdef CFG_TwoPwmPins
      setbit(TIMSK1,TOIE1);
    #endif
  #endif
  #if defined (__AVR_ATmega32U4__)  
    setbit(TIMSK3,TOIE3);
  #endif
  pwm_on = true;
  return pwm_on;
}

/***************************************************************************//**
* \brief stop pwm generation
* 
* To stop the pwm generation, timer2 will be disabled
*******************************************************************************/
boolean pwmStop() {
  //digitalWrite(CFG_EN_DRIVER, LOW);
   #if defined (__AVR_ATmega168__) || defined (__AVR_ATmega328P__)
    OCR2A = 0;
    #ifdef CFG_TwoPwmPins
      OCR1AH = 0;
      OCR1AL = 0;
    #endif
  #endif
  #if defined (__AVR_ATmega32U4__)
    OCR3AH = 0;
    OCR3AL = 0;
  #endif
  // enable Timer Interrupt
  #if defined (__AVR_ATmega168__) || defined (__AVR_ATmega328P__)
    clearbit(TIMSK2,TOIE2);
    #ifdef CFG_TwoPwmPins
      clearbit(TIMSK1,TOIE1);
    #endif
  #endif
  #if defined (__AVR_ATmega32U4__)  
    clearbit(TIMSK3,TOIE3);
  #endif
  pwm_on = false;
  return pwm_on;
}

/***************************************************************************//**
* \brief toggle pwm generation
* 
* To toggle the pwm generation, it will be started or stopped according to the 
* actual state
*******************************************************************************/
boolean pwmToggle() {
  if (pwm_on)
    pwmStop();
  else
    pwmStart();
  return pwm_on;
}

/***************************************************************************//**
* \brief pwm status
* 
* returns the on or off state of the pwm generation
*******************************************************************************/
boolean pwmStatus() {
  return pwm_on;
}

/***************************************************************************//**
* \brief read pwm settings
* 
* Read the eeprom frequency settings and stores it locally
*******************************************************************************/
void pwmReadSettings() {
  settings_local = readSettings();
}

/***************************************************************************//**
* \brief save pwm settings
* 
* Saves the pwm frequency settings into the eeprom
*******************************************************************************/
void pwmSaveSettings() {
  changeSetting(settings_local);
  saveSettings();
}

/***************************************************************************//**
* \brief save pwm settings
* 
* Saves the pwm frequency settings into the eeprom
*******************************************************************************/
void pwmChangeSettings(byte knobposition, double posvalue) {
  switch (knobposition) {
    case 0:
      settings_local.frequency_pos0 = posvalue;
      break;
    case 1:
      settings_local.frequency_pos1 = posvalue;
      break;
    case 2:
      settings_local.frequency_pos2 = posvalue;
      break;
    case 3:
      settings_local.frequency_pos3 = posvalue;
      break;
    case 4:
      settings_local.frequency_pos4 = posvalue;
      break;
    case 5:
      settings_local.frequency_pos5 = posvalue;
      break;
    case 6:
      settings_local.frequency_pos6 = posvalue;
      break;
    case 7:
      settings_local.frequency_pos7 = posvalue;
      break;
    case 8:
      settings_local.frequency_pos8 = posvalue;
      break;
    case 9:
      settings_local.frequency_pos9 = posvalue;
      break;
    case 10:
      settings_local.frequency_pos10 = posvalue;
      break;
    case 11:
      settings_local.frequency_pos11 = posvalue;
      break;
    case 12:
      settings_local.frequency_pos12 = posvalue;
      break;
    case 13:
      settings_local.frequency_pos13 = posvalue;
      break;
    case 14:
      settings_local.frequency_pos14 = posvalue;
      break;
    case 15:
      settings_local.frequency_pos15 = posvalue;
      break;
  }
}

/***************************************************************************//**
* \brief convert pot value
* 
* The Analog input delivers a value between 0 - 1023. This value will be
* converted in a frequency value between CFG_FREQUENCY_MAX and CFG_FREQUENCY_MIN
*******************************************************************************/
double ConvertPotToFrequency(word potvalue) {
  return (double)CFG_FREQUENCY_MIN + ((potvalue - CFG_POTVALUE_MIN) / (CFG_POTVALUE_MAX - CFG_POTVALUE_MIN)) * (CFG_FREQUENCY_MAX - CFG_FREQUENCY_MIN);
}

/***************************************************************************//**
* \brief convert 10pos pot to value
* 
* The 16Pos pot delivers a value between 0 - 16. This value will be changed into
* the fixed given value stored in the EEPROM
*******************************************************************************/
double ConvertPosToFrequency(byte knobposition) {
  switch (knobposition) {
    case 0:
      return settings_local.frequency_pos0;
      break;
    case 1:
      return settings_local.frequency_pos1;
      break;
    case 2:
      return settings_local.frequency_pos2;
      break;
    case 3:
      return settings_local.frequency_pos3;
      break;
    case 4:
      return settings_local.frequency_pos4;
      break;
    case 5:
      return settings_local.frequency_pos5;
      break;
    case 6:
      return settings_local.frequency_pos6;
      break;
    case 7:
      return settings_local.frequency_pos7;
      break;
    case 8:
      return settings_local.frequency_pos8;
      break;
    case 9:
      return settings_local.frequency_pos9;
      break;
    case 10:
      return settings_local.frequency_pos10;
      break;
    case 11:
      return settings_local.frequency_pos11;
      break;
    case 12:
      return settings_local.frequency_pos12;
      break;
    case 13:
      return settings_local.frequency_pos13;
      break;
    case 14:
      return settings_local.frequency_pos14;
      break;
    case 15:
      return settings_local.frequency_pos15;
      break;
    default: 
      return CFG_FREQUENCY_MIN;
  }
}
