/*
 * RA_ds18b20.hpp
 *
 *  Created on: Mar 20, 2024
 *      Author: Ola
 */

#ifndef INC_RA_DS18B20_HPP_
#define INC_RA_DS18B20_HPP_

#include <onewire.h>



class ds18b20 {
	public:
		/*
		 * @brief	The method is used to initialize the DS18B20 sensor.
		 */
		ds18b20(void);

		/*
		 * @brief	The method is used to deinit the DS18B20 sensor and its components.
		 * 			It set pin to Hi-Z state.
		 */
		~ds18b20(void);

		/*
		 * @brief	The method is used to read temperature values from the DS18B20 sensor.
		 * @retval	Binary notation of temperature value.
		 * 			-1 indicates a reading error.
		 */
		int RA_DS18B20_Read(void);

		/*
		 * Type of temperature measurement resolution.
		 * The resolution determines the precision of the measurement and the maximum conversion time.
		 */
		typedef enum {
			DS18B20_RESOLUTION_9BITS,	// precision = 0,5°C, max conversion time = 93,75 ms
			DS18B20_RESOLUTION_10BITS,	// precision = 0,25°C, max conversion time = 187,5 ms
			DS18B20_RESOLUTION_11BITS,	// precision = 0,125°C, max conversion time = 375 ms
			DS18B20_RESOLUTION_12BITS	// precision = 0,06125°C, max conversion time = 750 ms
		} DS18B20_resolution;

	private:
		/*
		 * Object responsible for OneWire communication.
		 * Communication with the sensor takes place via the OneWire network.
		 */
		OneWire_t onewire;

		/*
		 * @brief	The method is used to set resolution.
		 * @retval	The resolution to be set.
		 */
		void DS18B20_SetResolution(DS18B20_resolution resolution);

		/*
		 * @brief	The method is used to start ROM device.
		 * 			OneWire commands that  are sent before established with the DS18B20.
		 * 			No feedback messages will be received.
		 */
		void DS18B20_Start(void);

		/*
		 * @brief	The method used to read bit from device.
		 * @param	target		Pointer to return data form scratchpad.
		 * @retval	Reading status, checked on the basis of the CRC.
		 * 			true	The CRC at the end of the reading match.
		 * 			false	The CRC at the end of the reading does not match.
		 */
		bool DS18B20_ReadScratchpad(uint8_t *target);
};

#endif /* INC_RA_DS18B20_HPP_ */
