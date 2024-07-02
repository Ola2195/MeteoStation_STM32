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
		esp01s esp;

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

		/*
		 *
		 */
		void E_WiFiReceivingInterupt(void);

		/*
		 *
		 */
		void E_WiFiCounterInterupt(void);
};

#endif /* APPLICATION_USER_WIFIMODULE_H_ */
