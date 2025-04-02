/*
 * app.c
 *
 * Created: 2/20/2025 9:38:52 PM
 *  Author: kasmi
 */ 
#include "options.h"
#include "app.h"
#include "../sensor/sensor.h"
#include "../HMI/HMI.h"


appTaskArgsInit(appTaskArgs_t* app_task_args){
	app_task_args->num = 1;
}

appTask(appTaskArgs_t* taskArgs){
	
	/* Shared Primitives */
	static SemaphoreHandle_t twi_mutex;
	twi_mutex = xSemaphoreCreateMutex();
	
	
	/* Sensor task */
	static sensorTaskArgs_t sensor_task_args;
	sensorTaskArgsInit(&sensor_task_args);
	static TaskHandle_t sensor_task_handle;
	xTaskCreate(sensorTask, "input task", 85, &sensor_task_args, 2, &sensor_task_handle);
	
	
	/* Display task */
	static HMITaskArgs_t HMI_task_args;
	HMIArgsInit(&HMI_task_args);
	static TaskHandle_t HMI_task_handle;
	xTaskCreate(HMITask, "HMI task", 85, &HMI_task_args, 3, &HMI_task_handle);
	
	/* Output Task */
	
	/* IoT Task */
	
	/* Timer Task */
	
	/* EEPROM Task */
	
	/* control loop */
	for(;;){
		//turn LED on and off
		PORTB ^= (1<<PORTB5);
		vTaskDelay(5000/portTICK_PERIOD_MS);
		
		//
	}
}