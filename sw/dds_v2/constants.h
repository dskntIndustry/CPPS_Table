/***************************************************************************//**
* \file   constants.h
* \author fom
* \date   10.11.2015
* \brief  contatins all the constants values used by the sw
*
*******************************************************************************/

//------------------------------------------------------------------------------
// Constants
//

//------------------------------------------------------------------------------
// Potentiometer
// smallest value for the analog potentiometer
#define	POT_MIN					0.0      
// biggest value for the analog potentiometer      
#define	POT_MAX					1023.0        
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// ADC
// wait time after ADC read
#define ADC_READ_WAIT            5              
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// PWM
// =16MHz / 4080 (Prescaler :8)
#define CLKREF					3921.57
// 15Hz max
#define FREQUENCY_MAX			15.0 
//  1Hz min  
#define FREQUENCY_MIN			1.0
//  5Hz  
#define FREQUENCY_THRES			5.0

#define USEC					1000
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Button debounce
// 5 ms button debounce
#define BUT_DEBOUNCE			5
// Rate for checking the button state      
#define INPUT_REFRESH			200    

//------------------------------------------------------------------------------
// Auto shutoff
// time in ms for auto shutoff of the coils (prevent overheating)
#define AUTO_SHUTOFF			300000  
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Serial Port to PC
#define SERIAL_BAUD_RATE		9600   // 9600 baud
//------------------------------------------------------------------------------