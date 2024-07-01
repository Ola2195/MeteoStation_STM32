/*
 * utilites.h
 *
 *  Created on: Apr 25, 2024
 *      Author: Ola
 */

#ifndef THIRD_PARTY_UTILITES_HPP_
#define THIRD_PARTY_UTILITES_HPP_

#include <main.h>
#include <string.h>
#include <stdio.h>
#include "stdlib.h"
#include "stm32f3xx_hal.h"

extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;
extern TIM_HandleTypeDef htim4;


#define PRINTF_LEN 1024
static char buf_printf[PRINTF_LEN];

// Sends to console
#define printfx(f_, ...) snprintf(buf_printf, PRINTF_LEN, (f_), ##__VA_ARGS__); \
HAL_UART_Transmit(&huart2, (uint8_t*)buf_printf, strlen(buf_printf), 1000);


// Sends to WiFi and to console
#define printwifi(f_, ...) snprintf(buf_printf, PRINTF_LEN-6, (f_), ##__VA_ARGS__); \
HAL_UART_Transmit(&huart3, (uint8_t *)buf_printf, strlen(buf_printf), 1000);


static void Delay_us(uint32_t us) {
	__HAL_TIM_SET_COUNTER(&htim4, 0);
	while (__HAL_TIM_GET_COUNTER(&htim4) < us) {}
}

#endif /* THIRD_PARTY_UTILITES_HPP_ */
