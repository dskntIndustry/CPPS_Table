/***************************************************************************//**
* \file   serial.h
* \author fom
* \date   10.11.2015
* \brief  serial related stuff
*
* This files contains all functions concering the serial connection
*******************************************************************************/

/***************************************************************************//**
* \brief Configuration serial connection
* 
* Serial Connection will be initialised
*******************************************************************************/
void serialSetup() {
  // Open serial communications and wait for port to open:
  Serial.begin(CFG_SERIAL_BAUD);
  while (!Serial) {}; // wait for connect
  delay(1000);
  // Welcome Message
  Serial.print(HESSO_logo);
  Serial.println(Welcome_Message);
  #ifdef CFG_RodShaking
    Serial.println("Config: Rod");
  #endif
  #ifdef CFG_HouseBuilder
    Serial.println("Config: House");
  #endif
  #if defined (__AVR_ATmega168__)
    Serial.println("uC:     AVR ATmega168");
  #endif
  #if defined (__AVR_ATmega328P__)
    Serial.println("uC:     AVR ATmega328P");
  #endif
  #if defined (__AVR_ATmega32U4__)
    Serial.println("uC:     AVR ATmega32U4");
  #endif
  Serial.flush();
}

/***************************************************************************//**
* \brief print floating point on serial
* \param val is the doule value to print
* \param precision is the number of after comma presicion
* 
* This function lets you sent floating point values over the serial connection
* printDouble(3.1415926, 4) = 3.1415
*******************************************************************************/
void printDouble(double val, byte precision) {
  Serial.print(int(val));   // prints the int part
  if( precision > 0) {
    Serial.print(".");      // print the decimal point
    unsigned long frac;
    unsigned long mult = 1;
    byte padding = precision -1;
    while(precision--)
      mult *=10;
 
    if(val >= 0)
      frac = (val - int(val)) * mult;
    else
      frac = (int(val)- val ) * mult;
    unsigned long frac1 = frac;
    while( frac1 /= 10 )
      padding--;
    while(padding--)
      Serial.print("0");
    Serial.print(frac,DEC);
  }
}

void printDouble(double val) {
  printDouble(val, 4);
}

void printDoubleln(double val, byte precision) {
  Serial.print(int(val));   // prints the int part
  if( precision > 0) {
    Serial.print(".");      // print the decimal point
    unsigned long frac;
    unsigned long mult = 1;
    byte padding = precision -1;
    while(precision--)
      mult *=10;
 
    if(val >= 0)
      frac = (val - int(val)) * mult;
    else
      frac = (int(val)- val ) * mult;
    unsigned long frac1 = frac;
    while( frac1 /= 10 )
      padding--;
    while(padding--)
      Serial.print("0");
    Serial.println(frac,DEC);
  }
}

void printDoubleln(double val) {
  printDoubleln(val, 4);
}
