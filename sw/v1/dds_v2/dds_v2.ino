#include "avr/pgmspace.h"

#include "Bounce.h"
#include "Metro.h"

#include "constants.h"
#include "hwsetup.h"
#include "pwm.h"
#include "ioutils.h"
#include "button.h"

//TODO attach interrupt to button start (pin 0)

int start_pwm = 0;


double currentFrequency;
// put your setup code here, to run once:
void setup()
{
	//Init pins values
	initPins();
	initSerialOutput();
	#ifdef CFG_ROD

	#endif

}

// put your main code here, to run repeatedly: 
void loop()
{
	readInputs();

	#ifdef CFG_HOUSE

		if(getCurrenStartButtonState())
		{
			changePWMSettings(getPotFrequency(), 0.33);
			doPWM();
		}

	#endif

	#ifdef CFG_ROD

		
		digitalWrite(LED_SETUP, getCurrenSetupButtonState());

	// Output
		if (getCurrenSetupButtonState())
		{
			Serial.println("\n-------- Entering Setup Mode --------");
			
			//pwmReadSettings();
		}
		else
		{
			Serial.println("\n---------- Exit Setup Mode ----------");
			//pwmSaveSettings();
		}
		
	#endif
}
