/*
 * E_WiFiModule.cpp
 *
 *  Created on: May 30, 2024
 *      Author: Ola
 */


#include <E_WiFiModule.hpp>
#include "config.h"


WiFiModule::WiFiModule() : wifiStatus(false) {

}

void WiFiModule::E_WiFiInit(void) {
	  if(!esp.atStatus || esp.resetState)
		  esp.AT_Init();
	  if(esp.atStatus && !esp.wifiStatus && !esp.resetState)
		  esp.WiFi_Init();
	  if(esp.wifiStatus && !esp.serverStatus)
		  esp.RA_ConnectToServer(IP_ADDRESS, APACHE_PORT);
	  if(esp.serverStatus) {
		  wifiStatus = true;
	  } else {
		  wifiStatus = false;
	  }
}

void WiFiModule::E_WiFiSend(const char *message) {
	if(esp.serverStatus) {
		esp.RA_SendMessage(message, IP_ADDRESS, APACHE_PORT);
	}
}

void WiFiModule::E_WiFiReceivingInterupt(void) {
	esp.RA_ESP_Interrupt();
}

void WiFiModule::E_WiFiCounterInterupt(void) {
	esp.RA_ESP_Counter();
}
