/*
 * display.c
 *
 * Created: 2/20/2025 9:41:56 PM
 *  Author: kasmi
 */ 
#include "options.h"
#include "display.h"
#include "menu_structs.h"
#include "LCD_controller/LCD_controller.h"

#include <string.h>





void displayArgsInit(displayTaskArgs_t* args){
	args->inToDisplay = xQueueCreate(10, sizeof(displayQueueItem_t));
	
}

void mainMenuInit(menuItem_t* unit_item, menuItem_t* testt_item){
	setNextPrevPointers(unit_item, testt_item);
	setNextPrevPointers(testt_item, unit_item);
	
}


void displayTask(displayTaskArgs_t* task_args){
	
	/* init */	
	// LCD interface
	LCDObj_t lcd_obj;
	LCD_Init(&lcd_obj,LCD_ADDRESS, 1);
	
	// Menu Items
	static menuItem_t * active_menu_pointer;
	static menuItem_t unit_temp_item;
	static menuItem_t test_item;
	mainMenuInit(&unit_temp_item, &test_item);
	strcpy(unit_temp_item.line1, "Kevin Smith");
	active_menu_pointer = &unit_temp_item;
	
	// Queue Object
	static displayQueueItem_t queue_local_buffer;
	
	// stack vars
	char buffer[20];
	
	/* Display RT Task */
	while(1){
		/* Check queue update data */
		if(xQueueReceive(task_args->inToDisplay, &queue_local_buffer, (TickType_t)1) == pdTRUE){
			switch(queue_local_buffer.type){
				case UNIT_TEMP:
					sprintf(buffer, "%3.2f", queue_local_buffer.data.fvalue);
					strncpy(unit_temp_item.line1+sizeof(unit_temp_item.line1)-strlen(buffer), buffer, strlen(buffer));
					strncpy(unit_temp_item.line1, "Curnt Temp:", strlen("Curnt Temp:"));
				break;
				
				case UNIT_HUMD:
				break;
				
				case LIQD_TEMP:
				break;
				
				case TIMER_VAL:
				break;
				
				case MOVEMENT:
				break;
			}
			
		}
		else{
			//error or empty
		}

		lcd_obj.writeStringAt(&lcd_obj, active_menu_pointer->line1, 20, 0x00);
		
	}
	vTaskDelete( NULL );
	
}