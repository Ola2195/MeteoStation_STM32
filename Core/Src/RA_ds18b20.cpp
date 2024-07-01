/*
 * RA_ds18b20.c
 *
 *  Created on: Mar 20, 2024
 *      Author: Ola
 */

/* Includes */
#include "RA_ds18b20.hpp"

#include <cstring>
#include <cstdio>


#define DS18B20_Pin					DS_Pin
#define DS18B20_GPIO_Port			DS_GPIO_Port

#define DS18B20_SCRATCHPAD_SIZE    	9

#define DS18B20_ONEWIRE_FAMILY		0x28

/* DS18B20 Function Commands */
#define DS18B20_CONVERT_T          	0x44
#define DS18B20_WRITE_SCRATCHPAD	0x4E
#define DS18B20_READ_SCRATCHPAD		0xBE
#define DS18B20_COPY_SCRATCHPAD		0x48

/* Configuration bits in byte 4 */
#define DS18B20_RESOLUTION_R0		5
#define DS18B20_RESOLUTION_R1		6



//extern void Error_Handler(void);



void ds18b20::DS18B20_SetResolution(DS18B20_resolution resolution) {
	OneWire_Reset(&onewire);
	OneWire_WriteByte(&onewire, DS18B20_READ_SCRATCHPAD);

	/* Ignore first 2 bytes */
	OneWire_ReadByte(&onewire);
	OneWire_ReadByte(&onewire);

	/*
	 * Reading the current DS18B20 settings.
	 * Alarm registers unchanged, used only for reinsertion in EEPROM.
	 */
	uint8_t th = OneWire_ReadByte(&onewire);	// alarm high trigger register, used only for reinsertion in EEPROM.
	uint8_t tl = OneWire_ReadByte(&onewire);	// alarm low trigger register, used only for reinsertion in EEPROM.
	uint8_t configuration = OneWire_ReadByte(&onewire);	// configuration register

	switch(resolution) {
	case DS18B20_RESOLUTION_9BITS:
		configuration &= ~(1 << DS18B20_RESOLUTION_R1);
		configuration &= ~(1 << DS18B20_RESOLUTION_R0);
	case DS18B20_RESOLUTION_10BITS:
		configuration &= ~(1 << DS18B20_RESOLUTION_R1);
		configuration |= 1 << DS18B20_RESOLUTION_R0;
	case DS18B20_RESOLUTION_11BITS:
		configuration |= 1 << DS18B20_RESOLUTION_R1;
		configuration &= ~(1 << DS18B20_RESOLUTION_R0);
	default:
		configuration |= 1 << DS18B20_RESOLUTION_R1;
		configuration |= 1 << DS18B20_RESOLUTION_R0;
	}

	OneWire_Reset(&onewire);

	/* Write scratchpad with old th and tl, and new resolution configuration. */
	OneWire_WriteByte(&onewire, DS18B20_WRITE_SCRATCHPAD);
	OneWire_WriteByte(&onewire, th);
	OneWire_WriteByte(&onewire, tl);
	OneWire_WriteByte(&onewire, configuration);

	OneWire_Reset(&onewire);

	/* Copy scratchpad to EEPROM of DS18B20 */
	OneWire_WriteByte(&onewire, DS18B20_COPY_SCRATCHPAD);
}


ds18b20::ds18b20(void) {
	printfx("\r\nDS18B20 INIT\r\n");

	/* Initializes DWT Delay (with dwt library) */
	DwtInit();


	/* Set parameter for DS18B20 */
	onewire.DataPin = GPIO_PIN_3;
	onewire.DataPort = GPIOC;
	DS18B20_resolution resolution = DS18B20_RESOLUTION_11BITS;

	/* Initialize OneWire (with onewire library) */
	printfx("\r\nONEWIRE INIT\r\n");
	OneWire_Init(&onewire);

	printfx("\r\nSEARCHING ONEWIRE DEVICE\r\n");
	if(OneWire_Search(&onewire, ONEWIRE_CMD_SEARCHROM)) {
		/* Get device address */
		OneWire_GetDevRom(&onewire, onewire.RomByte);
		/* Set resolution */
		DS18B20_SetResolution(resolution);
	} else {
		while(1) {}
		//Error_Handler();
	}
}


ds18b20::~ds18b20(void) {
	//printfx("\r\nDEINIT\r\n");
	// Hi-Z state
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = onewire.DataPin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	HAL_GPIO_Init(onewire.DataPort, &GPIO_InitStruct);

	HAL_GPIO_WritePin(onewire.DataPort, onewire.DataPin, GPIO_PIN_SET);
}


void ds18b20::DS18B20_Start(void) {
	printfx("\r\nSTART\r\n");
	OneWire_Reset(&onewire);
	OneWire_WriteByte(&onewire, ONEWIRE_CMD_SKIPROM);
	OneWire_WriteByte(&onewire, DS18B20_CONVERT_T);
}


bool ds18b20::DS18B20_ReadScratchpad(uint8_t *destination) {
	printfx("\r\nREAD SCRATCHPAD\r\n");
	/* Wait until line is released, then coversion is completed */
	while(!OneWire_ReadBit(&onewire)) {};

	OneWire_Reset(&onewire);

	/* Select ROM number */
	OneWire_SelectWithPointer(&onewire, onewire.RomByte);

	OneWire_WriteByte(&onewire, DS18B20_READ_SCRATCHPAD);

	/* Read data, byte by byte */
	for (uint8_t i=0; i<DS18B20_SCRATCHPAD_SIZE; i++)
		destination[i] = OneWire_ReadByte(&onewire);

	/* Checking CRC */
	uint8_t crc = OneWire_CRC8(destination, DS18B20_SCRATCHPAD_SIZE-1);
	if(crc != destination[DS18B20_SCRATCHPAD_SIZE-1]) {
		return false;
	}
	return true;
}


int ds18b20::RA_DS18B20_Read(void) {
	printfx("\r\nREAD TEMPERATURE\r\n");
	uint8_t readingData[DS18B20_SCRATCHPAD_SIZE];
	uint16_t temperature;

	DS18B20_Start();

	bool readingStatus = DS18B20_ReadScratchpad(readingData);
	OneWire_Reset(&onewire);

	if(!readingStatus)
		return -1;

	/* First two bytes of scratchpad are temperature values */
	temperature = readingData[0] | (readingData[1] << 8);
	return (int)temperature;
}
