/*
 * E_WiFiModule.cpp
 *
 *  Created on: May 30, 2024
 *      Author: Ola
 */


#include <E_WiFiModule.hpp>


WiFiModule::WiFiModule() {

}

void WiFiModule::E_WiFiInit(void) {
	  if(!module.atStatus || module.resetState)
		  module.AT_Init();
	  if(module.atStatus && !module.wifiStatus && !module.resetState)
		  module.WiFi_Init();
	  if(module.wifiStatus && !module.serverStatus)
		  module.RA_ConnectToServer("127.0.0.1", "1883");
}

void WiFiModule::E_WiFiSend(const char *message) {
	if(module.serverStatus) {
//		module.RA_SendMQTTMessage("sensors/data", message);
	}
}
