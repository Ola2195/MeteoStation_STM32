/*
 * E_TemperatureSensor.hpp
 *
 *  Created on: Apr 18, 2024
 *      Author: Ola
 */

#ifndef SRC_E_TEMPERATURESENSOR_HPP_
#define SRC_E_TEMPERATURESENSOR_HPP_

#include <stdint.h>
#include "RA_ds18b20.hpp"


class TemperatureSensor {
	public:
		/*
		 * Temperature reading status type from the DS18B20 sensor.
		 */
		typedef enum {
			CORRECT_TEMP,	// Correct reading and temperature within normal range
			OVER_TEMP,		// Correct reading but temperature outside normal range
			WRONG_CRC_CODE	// Incorrect reading - wrong checksum
		} E_temperature_status_t;

		/*
		 * @brief	The method is used to initialize the DS18B20 sensor.
		 */
		TemperatureSensor(void);

		/*
		 * @brief	The method is used to deinit the DS18B20 sensor.
		 */
		virtual ~TemperatureSensor(void);

		/*
		 * @brief	The method is used to read the temperature from the sensor.
		 * @param 	floatTemperature		Pointer to return temperature float value.
		 * retval	Temperature reading status according to E_temperature_status_t type.
		 */
		E_temperature_status_t E_ReadTemperature(float *floatTemperature);

		/*
		 * @brief 	The method is used to reset the DS18B20 sensor.
		 * 			Deletes and re-adds ds18b20 object (Resource Access).
		 */
		void E_Reset(void);

	private:
		/*
		 * Object responsible for DS18B20 temperature sensor functionality.
		 */
		ds18b20* tempSensor = new ds18b20();

		/*
		 * @brief	The method to convert a fixed-position representation to a floating-position representation.
		 * @param	fixedPoint		Number in fixed-position representation.
		 * @retval	Number in floating-position representation.
		 */
		float FixedToFloat(int16_t fixedPoint);

};

#endif /* SRC_E_TEMPERATURESENSOR_HPP_ */
