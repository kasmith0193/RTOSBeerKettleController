/*
 * display.h
 *
 * Created: 2/20/2025 9:42:24 PM
 *  Author: kasmi
 */ 

#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"


#ifndef DISPLAY_H_
#define DISPLAY_H_

/* ----------Display queue structure elements---------- */
typedef enum displayQueueItemType{
	UNIT_TEMP,
	UNIT_HUMD,
	LIQD_TEMP,
	TIMER_VAL,
	MOVEMENT,
	// Might be more once the wifi is added
}displayQueueItemType_t;

typedef union displayQueueData{
	float fvalue;
	uint8_t i8value;
	uint16_t i16value;
}displayQueueData_t;

typedef struct displayQueueItem{
	displayQueueItemType_t type;
	displayQueueData_t data;
	
} displayQueueItem_t;

/* ----------Display task args---------- */
typedef struct displayTaskArgs{
	QueueHandle_t inToDisplay;
	SemaphoreHandle_t twi_mutex;
} displayTaskArgs_t;



void displayArgsInit(displayTaskArgs_t* args);

void displayTask(displayTaskArgs_t* task_args);



#endif /* DISPLAY_H_ */