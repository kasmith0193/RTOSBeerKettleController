/**
 * aht21.c
 *
 * Created: 11/26/2024 11:09:19 PM
 *  Author: kasmi
 * \bug all delays should be replaced with RTOS delays
 */ 

#include "AHT21_controller/AHT21_contrller.h"
#include "options.h"

#include <util/delay.h>
#include <stdio.h>

void triggermeasure(ahtObj_t* ahtObj);

	
void AHT_init(ahtObj_t * ahtObj, uint8_t address){
	ahtObj->getdata = triggermeasure; 
	ahtObj->address = address;
	
	ahtObj->send[0] = 0xBE;
	ahtObj->send[1] = 0x08;
	ahtObj->send[2] = 0x00;
	
	twi_write(ahtObj->address, ahtObj->send, 3);
	_delay_ms(10);
}

void triggermeasure(ahtObj_t* ahtObj){
	ahtObj->send[0] = 0xAC;
	ahtObj->send[1] = 0x33;
	ahtObj->send[2] = 0x00;
	
	twi_write(ahtObj->address, ahtObj->send, 3);
	
	// Change to freeRTOS
	_delay_ms(80);
	
	twi_read(ahtObj->address, ahtObj->rec, 7);
	
	ahtObj->humd_raw = (uint32_t)(((uint32_t)ahtObj->rec[1] << 12) | (ahtObj->rec[2] << 4) | (ahtObj->rec[3] >> 4));
	ahtObj->humd_float = ((float)ahtObj->humd_raw/(1048576))*100;
	sprintf(ahtObj->humd_str, "%3.2f", ahtObj->humd_float);
	
	ahtObj->temp_raw = ( (0x000f0000 & ((uint32_t)ahtObj->rec[3]<<16)) | ((uint32_t)ahtObj->rec[4] << 8)  | (ahtObj->rec[5]) );
	ahtObj->temp_float = ((((float)ahtObj->temp_raw/(1048576))*360)-58);
	sprintf(ahtObj->temp_str, "%3.2f", ahtObj->temp_float);
}

