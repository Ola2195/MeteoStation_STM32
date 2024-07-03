/*
 * Manager.cpp
 *
 *  Created on: May 19, 2024
 *      Author: Ola
 */

#include "Manager.hpp"
#include <string>

#define MAX_TEMPREAD_FLAG	3

Manager::Manager(void)  : wifiStatus(false) {
	M_measurements = { 0, 0 };
}

void Manager::M_ComponentInit(void) {
	wifiModule.E_WiFiInit();
	if(wifiModule.wifiStatus) {
		wifiStatus = true;
	} else {
		wifiStatus = false;
	}
}

void Manager::M_PeriodicReadings(void) {
	if(wifiModule.esp.serverStatus) {
		char printTemp[100];
		float currentTemperature;
		M_measurements.lastTemperature = M_measurements.temperature;
		bool tempStatus = M_GetTemperature(&currentTemperature);
		if(tempStatus)
			M_measurements.temperature = currentTemperature;
		sprintf(printTemp, "\r\n%.2f\r\n", M_measurements.temperature);
		printfx(printTemp);
	}
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
	char printTemp[100];
	sprintf(printTemp, "temperature=%.2f", M_measurements.temperature);
	wifiModule.E_WiFiSend(printTemp);
}

void Manager::M_WiFiReceivingInterupt(void) {
	wifiModule.E_WiFiReceivingInterupt();
}

void Manager::M_WiFiCounterInterupt(void) {
	wifiModule.E_WiFiCounterInterupt();
}

