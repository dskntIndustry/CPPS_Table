/***************************************************************************//**
* \file   initHW.h
* \author fom
* \date   10.11.2015
* \brief  hardware initialisation
*
* This files contains all parameters which are constant in the system but could
* be changed if needed
*******************************************************************************/

/***************************************************************************//**
* \brief Configuration all pins
* 
* With help of the userConfiguration file, all pins are configurated according 
* to the choosen module configuration
*******************************************************************************/
void pinSetup() {
  // For both module configuration
  pinMode(CFG_BUT_START, INPUT_PULLUP);
  pinMode(CFG_LED_START, OUTPUT);
  digitalWrite(CFG_LED_START, LOW);
  
  #ifdef CFG_RodShaking
    // 10 pos Pot, 2 button and 2 leds for Rod shaker
    pinMode(CFG_POT_PIN1, INPUT_PULLUP);
    pinMode(CFG_POT_PIN2, INPUT_PULLUP);
    pinMode(CFG_POT_PIN4, INPUT_PULLUP);
    pinMode(CFG_POT_PIN8, INPUT_PULLUP);
    pinMode(CFG_BUT_SETUP, INPUT_PULLUP);
    pinMode(CFG_LED_SETUP, OUTPUT);
    digitalWrite(CFG_LED_SETUP, LOW);
  #endif
  
  // PWM output pin
  pinMode(CFG_PWM_1, OUTPUT);

  #ifdef CFG_TwoPwmPins
    pinMode(CFG_PWM_2, OUTPUT);
    pinMode(CFG_PWM_3, OUTPUT);
  #endif
}
