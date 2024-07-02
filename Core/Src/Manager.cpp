/*
 * Manager.cpp
 *
 *  Created on: May 19, 2024
 *      Author: Ola
 */

#include "Manager.hpp"

#define MAX_TEMPREAD_FLAG	3

Manager::Manager(void) {
	M_measurements = { 0, 0 };
}

void Manager::M_ComponentInit(void) {
	wifiModule.E_WiFiInit();
}

void Manager::M_PeriodicReadings(void) {
	float currentTemperature;
	M_measurements.lastTemperature = M_measurements.temperature;
	bool tempStatus = M_GetTemperature(&currentTemperature);
	if(tempStatus)
		M_measurements.temperature = currentTemperature;
}

bool Manager::M_GetTemperature(float *floatTemperature) {
	TemperatureSensor::E_temperature_status_t status = tempSensor.E_ReadTemperature(floatTemperature);
	tempReadFlag++;

	// Correct reading and temperature within normal range
	if(status == TemperatureSensor::CORRECT_TEMP) {
		tempReadFlag = 0;
		return true;
	} else if(tempReadFlag >= MAX_TEMPREAD_FLAG)
		tempSensor.E_Reset();

	return false;
}

void Manager::M_SendMeasurements(void) {
	wifiModule.E_WiFiSend("temperature=23.5");
}

void Manager::M_WiFiReceivingInterupt(void) {
	wifiModule.E_WiFiReceivingInterupt();
}

void Manager::M_WiFiCounterInterupt(void) {
	wifiModule.E_WiFiCounterInterupt();
}

