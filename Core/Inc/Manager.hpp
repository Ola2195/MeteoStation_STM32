/*
 * Manager.hpp
 *
 *  Created on: May 19, 2024
 *      Author: Ola
 */

#ifndef MANAGER_HPP_
#define MANAGER_HPP_

#include "E_TemperatureSensor.hpp"
#include "E_WiFiModule.hpp"

class Manager {
	public:
		struct measurements_t{
			float temperature;
			float lastTemperature;
		};

		/*
		 * Measurements structure.
		 */
		measurements_t M_measurements;

		/*
		 *
		 */
		WiFiModule esp;

		/*
		 *
		 */

		Manager(void);

		/*
		 * @brief	Periodic reading of measurements from all sensors.
		 * 			If the reading encounters an error, the measurement value is replaced by the last correct one.
		 */
		void M_PeriodicReadings(void);

		/*
		 * @brief	The method responsible for sending the collected measurements.
		 */
		void M_SendMeasurements(void);

	private:
		int tempReadFlag;

		/*
		 * Object responsible for temperature sensor functionality.
		 */
		TemperatureSensor tempSensor;

		/*
		 * @brief	The method is used to read the temperature.
		 * @param 	floatTemperature		Pointer to return temperature float value.
		 * @retval	Reading status
		 * 			true		Temperature readout correct
		 * 			false 		Reading error. If the reading error is repeated several times, the sensor reset is forced.
		 */
		bool M_GetTemperature(float *floatTemperature);
};

#endif /* MANAGER_HPP_ */
