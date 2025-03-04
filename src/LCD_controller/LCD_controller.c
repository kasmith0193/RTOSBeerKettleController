/**
 * LCD_interface.c
 *
 * Created: 9/9/2024 7:13:09 PM
 *  Author: kasmi
 */ 

// clean this to reduce the number of imports need
// Make the only libraries that should be imported are common
// or those that will be in every project

#include "LCD_controller/LCD_controller.h"
#include "options.h"

#include <util/delay.h>

/*
 * Structure
 */



/*
 * Private Declaration
 */
void convert(LCDObj_t * inputs);
void writeStringAt(LCDObj_t* lcdObj, char* string, uint8_t size, uint8_t address);
void clearDisplay(LCDObj_t * lcdObj);
void prep_func_mode_data(LCDObj_t * lcdObj, bool func4Bit0_8Bit1, bool func1Line0_2Line1, bool font8Bit0_10Bit1);
void prep_disp_curs_mode_data(LCDObj_t* lcdObj, bool dispOn, bool cursOn, bool cursBlinkOn );
void prep_goto_ddram_data(LCDObj_t * lcdObj, uint8_t locaiton);
void prep_write_char_data(LCDObj_t * lcdObj, uint8_t character);
void prep_disp_clear_data(LCDObj_t* lcdObj);

/*--------------------------------------------------------------
 * Public Definition
 *--------------------------------------------------------------*/
/**
 * /brief Brief description
 *		  Long Description
 */
void LCD_Init(LCDObj_t* lcdObj, uint8_t address7Bit, bool powerOn){
	
	//find a way to make recover from an unknown state
	lcdObj->light = true;
	lcdObj->i2c_address = address7Bit;
	
	//make this where twi.h does not need to be imported
	lcdObj->writeStringAt = writeStringAt;
	lcdObj->clear = clearDisplay;
	
	// first power up setting
	if(powerOn == true){
		prep_func_mode_data(lcdObj, 0, 1, 0);
		convert(lcdObj);
		twi_write(lcdObj->i2c_address, lcdObj->data , 2);
	}
	
	
	//4 bit , 2 line, 8 font
	prep_func_mode_data(lcdObj, 0 ,1 ,0);
	convert(lcdObj);
	twi_write(lcdObj->i2c_address,lcdObj->data, 4);

	
	//display on, cursor on, flash on
	prep_disp_curs_mode_data(lcdObj, 1, 0, 0);
	convert(lcdObj);
	twi_write(lcdObj->i2c_address, lcdObj->data , 4);

}

/*--------------------------------------------------------------
 * Structure Functions
 *--------------------------------------------------------------*/

void writeStringAt(LCDObj_t* lcdObj, char* string, uint8_t size, uint8_t address){
	// go to defined address
	prep_goto_ddram_data(lcdObj,address);
	convert(lcdObj);
	
	twi_write(lcdObj->i2c_address, lcdObj->data , 4);
	
	//write(i2c_address, convert(,data), 4);
	for(uint8_t i = 0; i < size; i++){
		prep_write_char_data(lcdObj, string[i]);
		convert(lcdObj);
		twi_write(lcdObj->i2c_address, lcdObj->data, 4);
	}
}

void clearDisplay(LCDObj_t * lcdObj){
	prep_disp_clear_data(lcdObj);
	convert(lcdObj);
	twi_write(lcdObj->i2c_address, lcdObj->data, 4);
	
}

/*--------------------------------------------------------------
 * Private functions
 *--------------------------------------------------------------*/

void convert(LCDObj_t * inputs){
	//                  split 1st and 2nd 4 bits                 light on/off         enable low   read/write			register select
	inputs->data[0] = ((0b11110000 & inputs->databus)         | (inputs->light << 3) | (1 << 2) | (inputs->rnw << 1) | (inputs->reg_sel << 0));
	inputs->data[1] = ((0b11110000 & inputs->databus)         | (inputs->light << 3)            | (inputs->rnw << 1) | (inputs->reg_sel << 0));
	inputs->data[2] = ((0b11110000 & (inputs->databus << 4 )) | (inputs->light << 3) | (1 << 2) | (inputs->rnw << 1) | (inputs->reg_sel << 0));
	inputs->data[3] = ((0b11110000 & (inputs->databus << 4 )) | (inputs->light << 3)            | (inputs->rnw << 1) | (inputs->reg_sel << 0));
	inputs->databus = 0x00;
	inputs->rnw = 0;
	inputs->reg_sel = 0;
	inputs->enable = 0;
}


//disp func
void prep_disp_clear_data(LCDObj_t* lcdObj){
	lcdObj->databus = (1 << CLEAR);
}

void prep_disp_return_data(LCDObj_t* lcdObj){
	lcdObj->databus = (1 << DISP_RETURN);
}

//display controls
void prep_disp_curs_mode_data(LCDObj_t* lcdObj, bool dispOn, bool cursOn, bool cursBlinkOn ){
	lcdObj->databus  = ((1 << DISP_CURS_MODES) | (dispOn << DISP_CURS_MODES_DISP_ON) | (cursOn << DISP_CURS_MODES_CURS_ON) | (cursBlinkOn <<  DISP_CURS_MODES_CURS_BLINK ));
}

//cursor and display shift func
void prep_cursor_shift_data(LCDObj_t * lcdObj, bool cursorLeft0Right1, bool displayDont0Do1){
	lcdObj->databus |= ((1 << SHIFT_MODES) | (cursorLeft0Right1 << SHIFT_MODE_CURS));
}

//func modes
void prep_func_mode_data(LCDObj_t * lcdObj, bool func4Bit0_8Bit1, bool func1Line0_2Line1, bool font8Bit0_10Bit1){
	lcdObj->databus = ((1 << FUNC_MODE) | (func4Bit0_8Bit1 << FUNC_MODE_4_BIT) | (func1Line0_2Line1 << FUNC_MODE_DISPLAY_LINES) | (font8Bit0_10Bit1 << FUNC_MODE_FONT ));
}

//set ddram address to display
void prep_goto_ddram_data(LCDObj_t * lcdObj, uint8_t locaiton){
	lcdObj->databus = ((1 <<DDRAM_SET) | (locaiton));
}

//write ascii char
void prep_write_char_data(LCDObj_t * lcdObj, uint8_t character){
	lcdObj->databus = character;
	lcdObj->reg_sel = 1;
}


