#include <TimerOne.h>

#include "avr/pgmspace.h"

#include "Bounce.h"
#include "Metro.h"

#include "constants.h"
#include "hwsetup.h"
#include "pwm.h"
#include "ioutils.h"
#include "button.h"

// put your setup code here, to run once:
void setup()
{
  //Init pins values
  initPins();
  initSerialOutput();
}

// put your main code here, to run repeatedly:
void loop()
{
  readInputs();
#ifdef CFG_HOUSE
  if (getCurrenStartButtonState())
  {
    updatePWMSettings(getPotFrequency(), 0.33);
    doPWM();
  }
#endif
}
