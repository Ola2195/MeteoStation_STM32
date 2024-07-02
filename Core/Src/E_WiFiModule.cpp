/*
 * E_WiFiModule.cpp
 *
 *  Created on: May 30, 2024
 *      Author: Ola
 */


#include <E_WiFiModule.hpp>

#define IP_ADDRESS		"192.168.18.5"
#define APACHE_PORT	"80"


WiFiModule::WiFiModule() {

}

void WiFiModule::E_WiFiInit(void) {
	  if(!module.atStatus || module.resetState)
		  module.AT_Init();
	  if(module.atStatus && !module.wifiStatus && !module.resetState)
		  module.WiFi_Init();
	  if(module.wifiStatus && !module.serverStatus)
		  module.RA_ConnectToServer(IP_ADDRESS, APACHE_PORT);
}

void WiFiModule::E_WiFiSend(const char *message) {
	if(module.serverStatus) {
		module.RA_SendMessage(message, IP_ADDRESS, APACHE_PORT);
	}
}
