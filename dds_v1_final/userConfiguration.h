/***************************************************************************//**
* \file   userConfiguration.h
* \author fom
* \date   10.11.2015
* \brief  all userConfigrable parameters
*
* This files contains all parameters which are constant in the system but could
* be changed if needed
*******************************************************************************/
#include "Arduino.h"

//#define CFG_OnePinPWM
//------------------------------------------------------------------------------
// Module Configuration
//
// Select for which use the module is (only enable one)
#define CFG_HouseBuilder           // Table for creating a house
//#define CFG_RodShaking             // 4 Rods with static frequency

//------------------------------------------------------------------------------
// Output configuration
//
// CFG_FullSinus & not CFG_TwoPwmPins
// (CFG_HalfSinus || CFG_HalfSquare) & CFG_TwoPwmPins
//#define CFG_FullSinus               // One coil and with full sinus wave
                                    // 255    .-.          |  .-.
                                    //      ,'   `.        |,'   `.
                                    // 127 +-------\-------/-------\-------+
                                    //              `.   ,'|        `.   ,'
                                    //   0            `-'  |          `-'
#define CFG_TwoPwmPins              // Define two PWM Pins instead of one
#define CFG_HalfSinus               // Two coils and two half sinus waves
                                    //  255    .-.          |  .-.
                                    //       .'   `.        |.'   `.
                                    //    0 +-------+-------+-------+---------
                                    //  255            .-.  |           .-.
                                    //               .'   `.|         .'   `.
                                    //    0 --------+-------+--------+-------+
#define CFG_HalfSquare              // Two coils and two square waves
                                    //  255 +-------+       +-------+
                                    //      |       |       |       |
                                    //    0 +-------+-------+-------+--------
                                    //  255         +-------+       +-------+
                                    //              |       |       |       |
                                    //    0 --------+-------+-------+-------+


//------------------------------------------------------------------------------
// Hardware Configuration
//
// 
#ifdef CFG_HouseBuilder
  #define CFG_POT_AMPLITUDE A0
  #define CFG_POT_FREQUENCY A1
#endif

#ifdef CFG_RodShaking
  #define CFG_POT_PIN1       5
  #define CFG_POT_PIN2       6
  #define CFG_POT_PIN4       7
  #define CFG_POT_PIN8       8
  #define CFG_BUT_SETUP      3
  #define CFG_LED_SETUP      4
  #define CFG_POT_SETUP     A2
#endif

#define CFG_BUT_START        0
#define CFG_LED_START        2

// PWM
#define CFG_PWM_1            11
#ifdef CFG_TwoPwmPins
  #define CFG_PWM_2          9
  #define CFG_PWM_3          10
#endif

#ifdef CFG_OnePinPWM
  #define CFG_PWM          11
  #define CFG_EN_DRIVER    9
#endif



#define CFG_DEBUG_PIN1      12
#define CFG_DEBUG_PIN2      13
 
//------------------------------------------------------------------------------
// Constants
//
// Potentiometer
#define CFG_POTVALUE_MIN        0.0            // smallest value for the analog potentiometer
#define CFG_POTVALUE_MAX        1023.0         // biggest value for the analog potentiometer


// ADC
#define CFG_ADC_WAIT            5              // wait time after ADC read

// PWM
//#define CFG_REFCLK            31372.549      // =16MHz / 510 (Prescaler :1)
#define CFG_REFCLK              3921.57        // =16MHz / 4080 (Prescaler :8)
#define CFG_FREQUENCY_MAX       15.0           // 15Hz max
#define CFG_FREQUENCY_MIN       1.0            //  1Hz min

// Button debounce
#define CFG_BUT_DEBOUNCE        5              // 5 ms button debounce
#define CFG_INPUT_REFRESH       200            // Rate for checking the button state

// Auto shutoff
#define CFG_AUTO_SHUTOFF        300000          // time in ms for auto shutoff of the coils (prevent overheating)


// Serial Port to PC
#define CFG_SERIAL_BAUD         9600           // 9600 baud
//#define HESSO_logo \
//"\n \
//----------------------------------------------------------------------\n \
//--  _   _ _____ ____       ____   ___    _     _     _       _      --\n \
//-- | | | | ____| ___|     | ___| | _ |  | |   | |_ _| | __ _(_)___  --\n \
//-- | |_| |  _| |___ | ____|___ || | | |  | | | | _` | || _` | | __| --\n \
//-- |  _  | |___ ___) |_____|__) | |_| |   | V | (_| | | (_| | |__ | --\n \
//-- |_| |_|_____|____|     |____| |___|     |_| |__,_|_||__,_|_|___| --\n \
//--                                                                  --\n \
//----------------------------------------------------------------------\n"
#define HESSO_logo      "\n\n---------------- HESSO ----------------\n"
#define Welcome_Message "Welcome to HESSOs Earthquake Simulator for Schools \n      => Enter help for more informations"

//    Amp |        ________
//   1    |  . ' `   
//        /        
//   0 ---|----+----+----+->
//        0    5    10   15 f [Hz]
#define CFG_AMP_REG_LIN_B       0  // 0.05
#define CFG_AMP_REG_LIN_A       0.5  // 0.15
#define CFG_COIL_MISMATCH       0  // 0.15

#ifdef CFG_FullSinus
// table of 256 sine values / one sine period / stored in flash memory
PROGMEM  prog_uchar sinus[]  = {
  127,130,133,136,139,143,146,149,152,155,158,161,164,167,170,173,176,178,181,184,187,190,192,195,198,200,203,205,208,210,212,215,217,219,221,223,225,227,229,231,233,234,236,238,239,240,
  242,243,244,245,247,248,249,249,250,251,252,252,253,253,253,254,254,254,254,254,254,254,253,253,253,252,252,251,250,249,249,248,247,245,244,243,242,240,239,238,236,234,233,231,229,227,225,223,
  221,219,217,215,212,210,208,205,203,200,198,195,192,190,187,184,181,178,176,173,170,167,164,161,158,155,152,149,146,143,139,136,133,130,127,124,121,118,115,111,108,105,102,99,96,93,90,87,84,81,78,
  76,73,70,67,64,62,59,56,54,51,49,46,44,42,39,37,35,33,31,29,27,25,23,21,20,18,16,15,14,12,11,10,9,7,6,5,5,4,3,2,2,1,1,1,0,0,0,0,0,0,0,1,1,1,2,2,3,4,5,5,6,7,9,10,11,12,14,15,16,18,20,21,23,25,27,29,31,
  33,35,37,39,42,44,46,49,51,54,56,59,62,64,67,70,73,76,78,81,84,87,90,93,96,99,102,105,108,111,115,118,121,124
};
#endif
#ifdef CFG_HalfSinus
  PROGMEM  prog_uchar sinus_half_1[]  = {
  0,6,13,19,25,31,37,44,50,56,62,68,74,80,86,92,98,103,109,115,120,126,131,136,142,147,152,157,162,167,171,176,180,
  185,189,193,197,201,205,208,212,215,219,222,225,228,231,233,236,238,240,242,244,246,247,249,250,251,252,253,254,254,255,255,255,
  255,255,254,254,253,252,251,250,249,247,246,244,242,240,238,236,233,231,228,225,222,219,215,212,208,205,201,197,193,189,185,180,
  176,171,167,162,157,152,147,142,136,131,126,120,115,109,103,98,92,86,80,74,68,62,56,50,44,37,31,25,19,13,6,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
  };
  
  PROGMEM  prog_uchar sinus_half_2[]  = {
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,6,13,19,25,31,37,44,50,56,62,68,74,80,86,92,98,103,109,115,120,126,131,136,142,147,152,157,162,167,171,176,180,
  185,189,193,197,201,205,208,212,215,219,222,225,228,231,233,236,238,240,242,244,246,247,249,250,251,252,253,254,254,255,255,255,
  255,255,254,254,253,252,251,250,249,247,246,244,242,240,238,236,233,231,228,225,222,219,215,212,208,205,201,197,193,189,185,180,
  176,171,167,162,157,152,147,142,136,131,126,120,115,109,103,98,92,86,80,74,68,62,56,50,44,37,31,25,19,13,6
  };
#endif

#ifdef CFG_HalfSquare
  PROGMEM  prog_uchar square_half_1[]  = {
  255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
  255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
  255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
  255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
  };
  
  PROGMEM  prog_uchar square_half_2[]  = {
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
  255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
  255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
  255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255
  };
#endif

// EEPROM locations

//10-Position Wheel baseaddr
#define CFG_EEPROMADDR_POS_BASE           0
//10-Position Wheel offsets
#define CFG_EEPROMADDR_POS0_FREQ          0
#define CFG_EEPROMADDR_POS1_FREQ          1
#define CFG_EEPROMADDR_POS2_FREQ          2
#define CFG_EEPROMADDR_POS3_FREQ          3
#define CFG_EEPROMADDR_POS4_FREQ          4
#define CFG_EEPROMADDR_POS5_FREQ          5
#define CFG_EEPROMADDR_POS6_FREQ          6
#define CFG_EEPROMADDR_POS7_FREQ          7
#define CFG_EEPROMADDR_POS8_FREQ          8
#define CFG_EEPROMADDR_POS9_FREQ          9
#define CFG_EEPROMADDR_POS10_FREQ         10
#define CFG_EEPROMADDR_POS11_FREQ         11
#define CFG_EEPROMADDR_POS12_FREQ         12
#define CFG_EEPROMADDR_POS13_FREQ         13
#define CFG_EEPROMADDR_POS14_FREQ         14
#define CFG_EEPROMADDR_POS15_FREQ         15


//------------------------------------------------------------------------------
// Bit stuff
//
#define clearbit(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#define setbit(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
