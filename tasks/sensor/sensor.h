/*
 * sensor.h
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



typedef struct sensorArgs{
	SemaphoreHandle_t twi_mutex;
}sensorTaskArgs_t;

void sensorTaskArgsInit(sensorTaskArgs_t*);
void sensorTask(sensorTaskArgs_t*);

#endif /* INPUT_H_ */