/*
 * E_WiFiModule.hpp
 *
 *  Created on: May 30, 2024
 *      Author: Ola
 */


#ifndef APPLICATION_USER_WIFIMODULE_H_
#define APPLICATION_USER_WIFIMODULE_H_

#include <RA_esp_01s.hpp>

class WiFiModule {
	public:
		esp01s module;

		/*
		 *
		 */
		WiFiModule(void);

		/*
		 *
		 */
		void E_WiFiInit(void);

		/*
		 *
		 */
		void E_WiFiSend(const char *message);
};

#endif /* APPLICATION_USER_WIFIMODULE_H_ */
