/*
 * E_TemperatureSensor.cpp
 *
 *  Created on: Apr 18, 2024
 *      Author: Ola
 */

#include "E_TemperatureSensor.hpp"

#define DS_NUM_FIXED_BITS	12
#define DS_DECIMAL_BITS		4

#define	MAX_TEMP			50


TemperatureSensor::TemperatureSensor(void) {
	tempSensor = new ds18b20();
}

TemperatureSensor::~TemperatureSensor(void) {
	delete tempSensor;
}

float TemperatureSensor::FixedToFloat(int16_t fixedPoint) {
	float decimal;
	int8_t digit;

	/* Check if digits is negative */
	if (fixedPoint & 0x8000) {
		fixedPoint = ~fixedPoint + 1;
	}

	/* Store integer digits */
	digit = fixedPoint >> 4;
	digit |= ((fixedPoint >> 8) & 0x7) << 4;

	/* Store decimal digits */
	decimal = fixedPoint & 0x0F;
	decimal *= (float)0.0625;

	return (digit + decimal);
}


TemperatureSensor::E_temperature_status_t TemperatureSensor::E_ReadTemperature(float *floatTemperature) {
	int fixedTemperature;
	fixedTemperature = tempSensor->RA_DS18B20_Read();

	if(fixedTemperature != -1) {
		*floatTemperature = FixedToFloat(fixedTemperature);
		if(*floatTemperature <= MAX_TEMP) {
			return CORRECT_TEMP;
		} else {
			return OVER_TEMP;
		}
	}

	return WRONG_CRC_CODE;
}

void TemperatureSensor::E_Reset(void) {
	delete tempSensor;
	tempSensor = new ds18b20();
}
