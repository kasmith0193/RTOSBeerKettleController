/**
 * input.c
 *
 * Created: 2/19/2025 3:55:01 PM
 *  Author: kasmi
 */ 

#include "options.h"
#include "input.h"

#include <stdbool.h>

#include "AHT21_controller/AHT21_contrller.h"

void inputTaskArgsInit(inputTaskArgs_t* args){
	
	args->liqd_temp_mutex = xSemaphoreCreateMutex();
	args->liqd_temp = 0.0;
	args->unit_temp_mutex = xSemaphoreCreateMutex();
	args->unit_temp = 0.0;
	args->unit_humd = 0.0;
	args->time_count_mutex = xSemaphoreCreateMutex();
	args->time_count = 0;
	// push button vars and semaphore
	// encoder vars and smaphore
}

void inputTask(inputTaskArgs_t* task_args){

	/* Init */
	static ahtObj_t myAHTObj;
	AHT_init(&myAHTObj, 0x38);
	
	for( ;; ){
		
		/* Get DS18B20 data (liquid temp) */
		//get data (need to build DS18B20 object)
		if(xSemaphoreTake(task_args->liqd_temp_mutex, (TickType_t)1) == pdTRUE){
			//updated when DS18B20 object
			task_args->liqd_temp = 150.2;
			xSemaphoreGive(task_args->liqd_temp_mutex);
		}
		else{
		}
		
		/* Get AHT22 data (unit temp)*/
		myAHTObj.getdata(&myAHTObj);
		if(xSemaphoreTake(task_args->unit_temp_mutex,(TickType_t)1) == pdTRUE){
			task_args->unit_temp = myAHTObj.temp_float;
			task_args->unit_humd = myAHTObj.humd_float;
			xSemaphoreGive(task_args->unit_temp_mutex);
		}
		else{
		
		}
	
		/* Check timer queue */
	
		/* check PB queue */
	
		/* check rotary encoder queue */
	
	}
	vTaskDelete( NULL );
}


