 /**
 * MAIN Generated Driver File
 * 
 * @file main.c
 * 
 * @defgroup main MAIN
 * 
 * @brief This the main application code.
 *
 * @version MAIN Driver Version 1.0.0
*/



/*--------------------------------------------------------------
 * Includes
 *--------------------------------------------------------------*/

/* options.h must be the first include */
#include "options.h"

/* avr-libc */
/// \cond
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
/// \endcond

/* freeRTOS */
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"

#include "task.h"
#include "semphr.h"
#include "queue.h"

/*mcc generated libs*/
#include "mcc/system.h"


/*custom libs*/
#include "LCD_controller/LCD_controller.h"
#include "AHT21_controller/AHT21_contrller.h"

/*tasks*/
#include "app/app.h"


bool powerOnReset;




int main(void){

	/* MCC Init */
	SYSTEM_Initialize();
	
	/* Application task */
	static appTaskArgs_t app_task_args;
	appTaskArgsInit(&app_task_args);
	TaskHandle_t app_task_handle;
	xTaskCreate(appTask, "app_task", 80, &app_task_args, 1, &app_task_handle);
	
	vTaskStartScheduler();
	
	
}