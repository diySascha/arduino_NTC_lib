/***********************************************************************************/
/*             NTC -- manages a NTC Thermistor in the follwing circuit: 	       */
/*     																			   */
/*     (Aref) --- (+5V/3V3) --- (10k-Resister) ---|--- (Thermistor) ---- (GND)     */
/*                                                |							       */
/*                                            Analog Pin						   */
/*																				   */
/*			code based from code on Gradge Lab found here:				  		   */
/* http://garagelab.com/profiles/blogs/tutorial-using-ntc-thermistors-with-arduino */
/*		   																		   */
/* packed in a library by S.Bruechert											   */
/* http://diysascha.wordpress.com												   */
/***********************************************************************************/

#ifndef NTC_h
#define NTC_h

#include "Arduino.h"
#include "math.h"

class NTC {
	public:
		// Thermistor(int pin);
		NTC(int pin, unsigned int NTC_nominal, int temp_nominal, int samples, unsigned int b_value, unsigned int resistor);
		float readTempC();
		float readTempF();
	private:
		int _pin;
		unsigned int _NTC_nominal;
		int _temp_nominal;
		int _samples;
		unsigned int _b_value;
		unsigned int _resistor;
		float temperatureC;
		float temperatureF;
};

#endif
