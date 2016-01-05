/***************************************************************************//**
* \file   pwm.h
* \author fom
* \date   10.11.2015
* \brief  PWM functions
*
*******************************************************************************/
double pwm_frequency;
double pwm_duty;
double pwm_period;

void changePWMSettings(double frequency, double duty)
{
	pwm_frequency = frequency;
	pwm_period = (1.0/frequency)*USEC;
	pwm_duty = duty;

}

void doPWM()
{
	
	if(pwm_frequency < (double)FREQUENCY_THRES)
	{

		pwm_duty = pwm_frequency*0.02;
		digitalWrite(PWM_OUTPUT_0, HIGH);
		digitalWrite(PWM_OUTPUT_1, LOW);

		delay(abs(pwm_period*pwm_duty));
		
		digitalWrite(PWM_OUTPUT_0, LOW);

		delay(abs(pwm_period/2 - pwm_duty*pwm_period));
		digitalWrite(PWM_OUTPUT_1, HIGH);

		delay((pwm_period)*(pwm_duty));
		digitalWrite(PWM_OUTPUT_1, LOW);

		delay(abs((1-pwm_duty)*pwm_period)-(pwm_period/2));
	}
	else
	{
		digitalWrite(PWM_OUTPUT_0, HIGH);
		digitalWrite(PWM_OUTPUT_1, LOW);

		delay(abs(pwm_period*pwm_duty));
		
		digitalWrite(PWM_OUTPUT_0, LOW);

		delay(abs(pwm_period/2 - pwm_duty*pwm_period));
		digitalWrite(PWM_OUTPUT_1, HIGH);

		delay((pwm_period)*(pwm_duty));
		digitalWrite(PWM_OUTPUT_1, LOW);

		delay(abs((1-pwm_duty)*pwm_period)-(pwm_period/2));
	}


}
