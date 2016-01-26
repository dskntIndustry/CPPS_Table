/***************************************************************************//**
* \file   adc.h
* \author fom
* \date   10.11.2015
* \brief  adc related stuff
*
* This files contains all functions concering the analog input pins (e.g. Pot)
*******************************************************************************/

/***************************************************************************//**
* \brief read all inputs
* \param pin, number of input pin to read
*  
* Read all digital, analog button attached to the system on the given module 
* configuration
*******************************************************************************/
word adcRead(int pin) {
  word adc_value = analogRead(pin);
  delay(CFG_ADC_WAIT);
  return adc_value;
}
