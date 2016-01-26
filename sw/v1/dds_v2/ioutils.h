/*#include "constants.h"
#include "hwsetup.h"*/

double pot_frequency;
word pot_value;
int pot_setup;
byte pot_pins;

int state_count = 0;
int setup_on = 0;

Bounce startButton = Bounce(BUT_START, BUT_DEBOUNCE);
#ifdef CFG_ROD
Bounce setupButton = Bounce(BUT_SETUP, BUT_DEBOUNCE);
#endif

int currentStartButtonState = 0;
int lastStartButtonState = 0;


int adcRead(int pin)
{
	int adc_value = analogRead(pin);
	delay(ADC_READ_WAIT);
	return adc_value;
}

void readInputs() {
  // Read analog buttons
	
	#ifdef CFG_HOUSE

		pot_value = adcRead(FREQUENCY_POT);

	#endif

	// Read digital buttons
	#ifdef CFG_ROD
		pot_pins = 0;
		if (digitalRead(POT_PIN1))
		{
			pot_pins &= ~(1 << 0); // clear bit
		}
		else
		{
			pot_pins |= 1 << 0;    // set bit
		}

		if (digitalRead(POT_PIN2))
		{
			pot_pins &= ~(1 << 1); // clear bit
		}
		else
		{
			pot_pins |= 1 << 1;    // set bit
		}

		if (digitalRead(POT_PIN4))
		{
			pot_pins &= ~(1 << 2); // clear bit
		}
		else
		{
			pot_pins |= 1 << 2;    // set bit
		}

		if (digitalRead(POT_PIN8))
		{
			pot_pins &= ~(1 << 3); // clear bit
		}
		else
		{
			pot_pins |= 1 << 3;    // set bit
		}
		pot_setup = adcRead(POT_SETUP);
		setupButton.update();
		
		Serial.println(pot_pins, HEX);

		if (setupButton.risingEdge())
		{
			if (setup_on)
			{
				setup_on = false;
			}
			else
			{
				setup_on = true;
			}
		}

	#endif

	startButton.update();
	if(startButton.risingEdge())
	{
		state_count++;
/*		Serial.println("Rising");
		Serial.println(state_count);*/
		if(state_count%2==1)
		{
			currentStartButtonState = 1;
			digitalWrite(LED_START, HIGH);
			
		}
		else
		{
			currentStartButtonState = 0;
			digitalWrite(LED_START, LOW);
			
		}
	}


}

word getPotValue()
{
	return pot_value;
}

int getCurrenStartButtonState()
{
	return currentStartButtonState;
}

int getCurrenSetupButtonState()
{
	return setup_on;
}

double getPotFrequency()
{
	pot_frequency = (double)FREQUENCY_MIN+
	((POT_MAX-pot_value)/(POT_MAX+1))
	*(FREQUENCY_MAX-FREQUENCY_MIN);

	return pot_frequency;
}

int getPotSetup()
{
	return pot_setup;
}