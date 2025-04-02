/**
 * sensor.c
 *
 * Created: 2/19/2025 3:55:01 PM
 *  Author: kasmi
 */ 

#include "options.h"
#include "sensor.h"

#include <stdbool.h>

#include "AHT21_controller/AHT21_contrller.h"

void sensorTaskArgsInit(sensorTaskArgs_t* args){
	args->twi_mutex = xSemaphoreCreateMutex();
}

void sensorTask(sensorTaskArgs_t* task_args){

	/* Init */
	static ahtObj_t myAHTObj;
	AHT_init(&myAHTObj, 0x38);
	
	for( ;; ){
		/* Get AHT22 data (unit temp)*/
		//i2c mutex needed
		myAHTObj.getdata(&myAHTObj);
		//send via the queue
		
		vTaskDelay(500/portTICK_PERIOD_MS);
	}
	vTaskDelete( NULL );
}


