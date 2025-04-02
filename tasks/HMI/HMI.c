/*
 * display.c
 *
 * Created: 2/20/2025 9:41:56 PM
 *  Author: kasmi
 */ 
#include "options.h"
#include "HMI.h"
#include "menu_structs.h"
#include "LCD_controller/LCD_controller.h"

#include <string.h>





void HMIArgsInit(HMITaskArgs_t* args){
	args->inToHMI = xQueueCreate(10, sizeof(displayQueueItem_t));
	
}

void mainMenuInit(menuItem_t* unit_item, menuItem_t* testt_item){
	setNextPrevPointers(unit_item, testt_item);
	setNextPrevPointers(testt_item, unit_item);
	
}


void HMITask(HMITaskArgs_t* task_args){
	
	/* init */
	uint8_t system_init = (EXTRF);
	// LCD interface
	volatile LCDObj_t lcd_obj;
	vTaskDelay(200/portTICK_PERIOD_MS);
	taskENTER_CRITICAL();
	//the init is strange because the half word creates an interlock unless peoperly handled
	// this need to be resloved some how. I'll look into that soon
	// there us a power on and external reset bit  PORF and EXTRF respectively
	// there is also a bown out detection that could be used
	// these should be used to fix any problems
	LCD_Init(&lcd_obj,LCD_ADDRESS, system_init);
	taskEXIT_CRITICAL();
	vTaskDelay(200/portTICK_PERIOD_MS);
		
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
	
	lcd_obj.writeStringAt(&lcd_obj, "Kevin Smith", strlen("Kevin Smith"), 0x00);
	
	/* Display RT Task */
	while(1){
		/* Check queue update data */
		/*if(xQueueReceive(task_args->inToHMI, &queue_local_buffer, (TickType_t)1) == pdTRUE){
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
		}*/

		
		taskENTER_CRITICAL();
		lcd_obj.writeStringCurrent(&lcd_obj, "!", strlen("!"));
		taskEXIT_CRITICAL();
		

		
		vTaskDelay(1000 / portTICK_PERIOD_MS);
		
	}
	vTaskDelete( NULL );
	
}