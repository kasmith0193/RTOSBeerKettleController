/*
 * input.h
 *
 * Created: 2/20/2025 7:51:20 PM
 *  Author: kasmi
 */ 

#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#include <stdint.h>


#ifndef INPUT_H_
#define INPUT_H_



typedef struct inputArgs{
	SemaphoreHandle_t twi_mutex;

	SemaphoreHandle_t  liqd_temp_mutex;
	float liqd_temp;
	
	SemaphoreHandle_t unit_temp_mutex;
	float unit_temp;
	float unit_humd;
	
	SemaphoreHandle_t time_count_mutex;
	uint16_t time_count;
	

	// push button vars and semaphore
	// encoder vars and smaphore
}inputTaskArgs_t;

void inputTaskArgsInit(inputTaskArgs_t*);

void inputTask(inputTaskArgs_t*);






#endif /* INPUT_H_ */