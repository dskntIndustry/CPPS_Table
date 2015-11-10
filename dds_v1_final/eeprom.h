/***************************************************************************//**
* \file   eeprom.h
* \author fom
* \date   10.11.2015
* \brief  all pwm related stuff
*
* This files contains all functions concerning time and PWM
*******************************************************************************/
#include <avr/eeprom.h>

struct settings_t
{
  float frequency_pos0;
  float frequency_pos1;
  float frequency_pos2;
  float frequency_pos3;
  float frequency_pos4;
  float frequency_pos5;
  float frequency_pos6;
  float frequency_pos7;
  float frequency_pos8;
  float frequency_pos9;
  float frequency_pos10;
  float frequency_pos11;
  float frequency_pos12;
  float frequency_pos13;
  float frequency_pos14;
  float frequency_pos15;
} settings;


/***************************************************************************//**
* \brief save settings
* 
* Store all setting to the EEPROM
*******************************************************************************/
void saveSettings() {
  eeprom_write_block((const void*)&settings, (void*)CFG_EEPROMADDR_POS_BASE, sizeof(settings));
}

/***************************************************************************//**
* \brief read settings
* 
* Read all setting from the EEPROM and store it in the typedef. Also it return 
* the struct for further use
*******************************************************************************/
settings_t readSettings() {
  eeprom_read_block((void*)&settings, (void*)CFG_EEPROMADDR_POS_BASE, sizeof(settings));
  return settings;
}

/***************************************************************************//**
* \brief read settings
* \param takes a complete settings struct to store 
*
* Read all setting from the EEPROM and store it in the typedef
*******************************************************************************/
void changeSetting(settings_t _settings) {
  settings = _settings;
}
