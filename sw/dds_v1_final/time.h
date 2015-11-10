/***************************************************************************//**
* \file   time.h
* \author fom
* \date   10.11.2015
* \brief  all timer related stuff
*
* This files contains all functions concerning time and PWM
*******************************************************************************/
#include "avr/pgmspace.h"

// variables used inside interrupt service declared as volatile
volatile byte sinusmem_offset_1;   // offset for reading sinus value in memory
volatile unsigned long phaccu_1;   // phase accumulator
volatile unsigned long tword_1;    // dds tuning word
volatile byte sinusmem_offset_2;   // offset for reading sinus value in memory
volatile unsigned long phaccu_2;   // phase accumulator
volatile unsigned long tword_2;    // dds tuning word

volatile double amplitude_1 = 1; // Amplitude adjustment for PWM
volatile double amplitude_2 = 1; // Amplitude adjustment for PWM

/***************************************************************************//**
* \brief timer2 setup
* 
* This function will be setup the times 2 needed for pwm generation.
* set prscaler to 1, PWM mode to phase correct PWM,  16000000/510 = 31372.55 Hz clock
*******************************************************************************/
void timer_setup() {
  #if defined (__AVR_ATmega168__) || defined (__AVR_ATmega328P__)
    // For pin PWM_1 (pin 11 or PB3) (weaker coil)
    // Timer2 Clock Prescaler to : 1
    //setbit(TCCR2B, CS20);
    //clearbit(TCCR2B, CS21);
    //clearbit(TCCR2B, CS22);

    // Timer2 Clock Prescaler to : 8
    clearbit(TCCR2B, CS20);
    setbit(TCCR2B, CS21);
    clearbit(TCCR2B, CS22);
  
    // Timer2 PWM Mode set to Phase Correct PWM
    clearbit(TCCR2A, COM2A0);  // clear Compare Match
    setbit(TCCR2A, COM2A1);
  
    setbit(TCCR2A, WGM20);     // Mode 1  / Phase Correct PWM
    clearbit(TCCR2A, WGM21);
    clearbit(TCCR2B, WGM22);

    // For pin PWM_2 (pin 9 or PB1) (stronger coil)
    #ifdef CFG_TwoPwmPins
      // Timer1 Clock Prescaler to : 1
      //setbit(TCCR1B, CS10);
      //clearbit(TCCR1B, CS11);
      //clearbit(TCCR1B, CS12);

      // Timer1 Clock Prescaler to : 8
      clearbit(TCCR1B, CS10);
      setbit(TCCR1B, CS11);
      clearbit(TCCR1B, CS12);
    
      // Timer1 PWM Mode set to Phase Correct PWM
      clearbit(TCCR1A, COM1A0);  // clear Compare Match Channel A
      setbit(TCCR1A, COM1A1);

      clearbit(TCCR1A, COM1B0);  // clear Compare Match Channel B
      setbit(TCCR1A, COM1B1);
    
      setbit(TCCR1A, WGM10);     // Mode 1  / Phase Correct PWM 8-bit
      clearbit(TCCR1A, WGM11);
      clearbit(TCCR1B, WGM12);
      clearbit(TCCR1B, WGM13);    

    #endif
  #endif

  #if defined (__AVR_ATmega32U4__)
    // Timer 3
    // Clock Prescaler to : 1
    clearbit(TCCR3B, CS32);
    clearbit(TCCR3B, CS31);
    setbit(TCCR3B, CS30);
  
    // clear Compare Match
    setbit(TCCR3A, COM3A1);
    clearbit(TCCR3A, COM3A0);

    // PWM Mode1 / to Phase Correct PWM
    clearbit(TCCR3B, WGM33);
    clearbit(TCCR3B, WGM32);
    clearbit(TCCR3A, WGM31);
    setbit(TCCR3A, WGM30);
  #endif
}

/***************************************************************************//**
* \brief Output PWM
* 
* This function will change the compare value for the output pwm generation
*******************************************************************************/
void pwm_compare(int timer, byte offset) {
  // read value from ROM sine table and send to PWM DAC
  #if defined (__AVR_ATmega168__) || defined (__AVR_ATmega328P__)
    #ifdef CFG_OneFullSinus
      OCR2A = (int)(pgm_read_byte_near(sinus + offset) * amplitude_1);
      OCR1AH = 0;
    #endif
    #if defined (CFG_HalfSinus) && defined (CFG_TwoPwmPins)
      if (timer == 0) {
        OCR1AH = 0;
        OCR1AL = (int)(pgm_read_byte_near(sinus_half_1 + offset) * amplitude_1);
      }
      else if (timer == 1) {
        OCR2A  = (int)(pgm_read_byte_near(sinus_half_2 + offset) * amplitude_2);
      }
    #endif
    #if defined (CFG_HalfSquare) && defined (CFG_TwoPwmPins)
      if (timer == 0) {
        OCR1AH = 0;
        OCR1AL = (int)(pgm_read_byte_near(square_half_1 + offset) * amplitude_1);
      }
      else if (timer == 1) {
        OCR2A  = (int)(pgm_read_byte_near(square_half_2 + offset) * amplitude_2);
      }
    #endif
  #endif
  #if defined (__AVR_ATmega32U4__)
    OCR3AH = 0;
    OCR3AL = (int)(pgm_read_byte_near(sinus + offset) * amplitude_1);
  #endif
}

/***************************************************************************//**
* \brief Timer3 Interrupt Service
* 
* Will be called at 31372,550 KHz = 32uSec.
* FOUT = (M (REFCLK)) / (2 exp 32)
*******************************************************************************/
#if defined (__AVR_ATmega32U4__)
ISR(TIMER3_OVF_vect) {

  phaccu_1 = phaccu_1 + tword_1;        // soft DDS, phase accu with 32 bits
  sinusmem_offset_1 = phaccu_1 >> 24;   // use upper 8 bits for phase accu as frequency information
  pwm_compare(2, sinusmem_offset_1);
}
#endif

/***************************************************************************//**
* \brief Timer2 Interrupt Service
* 
* Will be called at 31372,550 KHz = 32uSec.
* FOUT = (M (REFCLK)) / (2 exp 32)
*******************************************************************************/
#if defined (__AVR_ATmega168__) || defined (__AVR_ATmega328P__)
ISR(TIMER2_OVF_vect) {

  phaccu_2 = phaccu_2 + tword_2; // soft DDS, phase accu with 32 bits
  sinusmem_offset_2   = phaccu_2 >> 24;   // use upper 8 bits for phase accu as frequency information
  
  pwm_compare(1, sinusmem_offset_2);  
}
/***************************************************************************//**
* \brief Timer1 Interrupt Service
* 
* Will be called at 31372,550 KHz = 32uSec.
* FOUT = (M (REFCLK)) / (2 exp 32)
*******************************************************************************/
#ifdef CFG_TwoPwmPins
ISR(TIMER1_OVF_vect) {

  phaccu_1 = phaccu_1 + tword_1; // soft DDS, phase accu with 32 bits
  sinusmem_offset_1   = phaccu_1 >> 24;   // use upper 8 bits for phase accu as frequency information

  pwm_compare(0, sinusmem_offset_1);
}
#endif
#endif
/***************************************************************************//**
* \brief changes the generated sinus frequency
* 
* This function calculates the 
* a new PWM value for the sinus generation will given to the PMW output
*******************************************************************************/
void setSignalFrequency(double frequency)
{
  #if defined (__AVR_ATmega168__) || defined (__AVR_ATmega328P__)
    clearbit(TIMSK2,TOIE2);                // disable Timer2 Interrupt
    tword_2=pow(2,32)*frequency/CFG_REFCLK;  // calculate DDS new tuning word
    setbit(TIMSK2,TOIE2);                  // enable Timer2 Interrupt 

    #ifdef CFG_TwoPwmPins
      clearbit(TIMSK1,TOIE1);                // disable Timer2 Interrupt
      tword_1=pow(2,32)*frequency/CFG_REFCLK;  // calculate DDS new tuning word
      setbit(TIMSK1,TOIE1);                  // enable Timer2 Interrupt 
    #endif
  #endif
  #if defined (__AVR_ATmega32U4__)
    clearbit(TIMSK3,TOIE3);                // disable Timer2 Interrupt
    tword_1=pow(2,32)*frequency/CFG_REFCLK;  // calculate DDS new tuning word
    setbit(TIMSK3,TOIE3);                  // enable Timer2 Interrupt 
  #endif
}

void setSignalAmplitude(double amplitude)
{
  amplitude_1 = amplitude;
  #ifdef CFG_TwoPwmPins
    amplitude_2 = amplitude - CFG_COIL_MISMATCH;
    if (amplitude_2 > 1)
      amplitude_2 = 1;
    else if (amplitude_2 < 0)
      amplitude_2 = 0;
  #endif
}
