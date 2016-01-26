int start_button_status;
int lastState = 0;

int checkButton(int pin)
{
	int state1 = digitalRead(pin);
	long lastdebounce = millis();
	if(state1 != lastState)
	{
		lastdebounce = millis();
	}
	if((millis()-lastdebounce)>BUT_DEBOUNCE)
	{
		if(state1 != start_button_status)
		{
			start_button_status = state1;
		}
	}
	return start_button_status;
}