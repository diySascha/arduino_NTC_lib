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

#include "Arduino.h"
#include "NTC.h"

NTC::NTC(int pin, unsigned int NTC_nominal, int temp_nominal, int samples, unsigned int b_value, unsigned int resistor) {
// Pin that the thermistor is connected to
_pin = pin;

// Nominal temperature value for the thermistor
_NTC_nominal = NTC_nominal;

// Nominl temperature depicted on the datasheet
_temp_nominal = temp_nominal;

// Number of samples
_samples = samples;

// Beta value for our thermistor
_b_value = b_value;

// Value of the series resistor
_resistor = resistor;

  // define the reference voltage 3V3 to 5V only!
  analogReference(EXTERNAL);
}

float NTC::readTempC() {

float media;

// preset media to 0
media = 0;

// read [sample] times the NTC Value
  for (int i = 0; i < _samples; i++) {
    media += analogRead(_pin);
    delay(10);
  }
  
// make an average for the read in values
  media /= _samples;
  
// Convert the thermal stress value to resistance
  media = 1023 / media - 1;
  media = _resistor / media;
  
//Calculate temperature using the Beta Factor equation
  // (R/Ro)
  temperatureC = media / _NTC_nominal;
  // ln(R/Ro)
  temperatureC = log(temperatureC);
  // 1/B * ln(R/Ro)
  temperatureC /= _b_value;
  // + (1/To)
  temperatureC += 1.0 / (_temp_nominal + 273.15);
  // Invert the value
  temperatureC = 1.0 / temperatureC;
  // Convert it to Celsius
  temperatureC -= 273.15;

  // Return the Temperature in degree Celsius
  return temperatureC;
}



// returns temperature in degrees F
float NTC::readTempF() {

  // call readTemp to get Temperature  
  readTempC();
  
  // convert to degree Fahrenheit
  temperatureF = (temperatureC * 1.8) + 32;
  
  // Return the Temperature in degree Fahrenheit
  return temperatureF;  
}
