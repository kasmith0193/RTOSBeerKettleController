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
#include "input/input.h"
#include "IoT/IoT.h"
#include "display/display.h"
#include "output/output.h"
#include "eeprom/eeprom.h"


bool powerOnReset;




int main(void){
	
	/* New Main Code */
	
	/* MCC Init */
	SYSTEM_Initialize();
	/* TWI Mutex */
	static SemaphoreHandle_t twi_mutex;
	twi_mutex = xSemaphoreCreateMutex();
	
	/* Input task */
	/*static inputTaskArgs_t input_task_args;
	inputTaskArgsInit(&input_task_args);
	static TaskHandle_t input_task_handle;
	xTaskCreate(inputTask, "input task", 85, &input_task_args, 2, &input_task_handle);
	*/
	
	/* Display task */
	static displayTaskArgs_t display_task_args;
	displayArgsInit(&display_task_args);
	static TaskHandle_t display_task_handle;
	xTaskCreate(displayTask, "display task", 85, &display_task_args, 2, &display_task_handle);
	
	/* Application task */
	//combine all args or something
	
	//static appTaskArgs_t app_task_args;
	//appTaskArgsInit(&app_task_args);
	//TaskHandle_t app_task_handle;
	//xTaskCreate(appTask, "app_task", 20, &app_task_args, 3, &app_task_handle)
	
	vTaskStartScheduler();
	
	/* Old Main code */
	
	LCDObj_t myLCDObj;
	ahtObj_t myAHTObj;

	
	/* Init */
	_delay_ms(200);
	/* Used to send external resets to lcd so it dosent re config */
	if(MCUSR & 0b00000001){
		powerOnReset = true;
		MCUSR ^= 0b00000001;
	}else{
		powerOnReset = false;
	}
	/* MCC init */
	
	/* My init */
	LCD_Init(&myLCDObj ,LCD_ADDRESS, powerOnReset);
	AHT_init(&myAHTObj, 0x38);
	/* Intigrated LED set output */
	DDRB |= (1 << DDB5);
	_delay_ms(200);
	/* End Init */
	
	// think about how the tasks are gonna be broken down
	// temperature task
	// menu ()
	

	
    while(1){
		//turn LED on and off
		PORTB ^= (1<<PORTB5);
		
		//We will need to find a way to split some of this out into its onw tasks
		myAHTObj.getdata(&myAHTObj);
		myLCDObj.writeStringAt(&myLCDObj, "Curnt Humi:", strlen("Curnt Humi:"), 0x00);
		myLCDObj.writeStringAt(&myLCDObj, myAHTObj.humd_str, strlen(myAHTObj.humd_str), 0x14-strlen(myAHTObj.humd_str));
		myLCDObj.writeStringAt(&myLCDObj, "Curnt Temp:", strlen("Curnt Temp:"), 0x40);
		myLCDObj.writeStringAt(&myLCDObj, myAHTObj.temp_str, strlen(myAHTObj.temp_str), 0x54-strlen(myAHTObj.temp_str));
		_delay_ms(1000);
		myLCDObj.clear(&myLCDObj);

    }    
}