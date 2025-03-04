/*
 * LCD.c
 *
 * Created: 9/8/2024 11:15:17 PM
 *  Author: kasmi
 */ 
//#include <avr/io.h>
#include "./include/LCD_structs.h"
#include <stdbool.h>
#include <stdint-gcc.h>
////////////////////////////////////////////
#define D7 7
#define D6 6
#define D5 5
#define D4 4
#define D3 3
#define D2 2
#define D1 1
#define D0 0

//databus functions
#define CLEAR D0

#define DISP_RETURN D1

#define SHIFT_MODES D2
#define SHIFT_MODE_CURS D1  // 1 shift right, 0 shift left
#define SHIFT_MODE_DISPLAY D0 // 1 moves, 0 doesn't

#define DISP_CURS_MODES D3
#define DISP_CURS_MODES_DISP_ON D2 //disp on
#define DISP_CURS_MODES_CURS_ON D1 //cursor on
#define DISP_CURS_MODES_CURS_BLINK D0 //curs blink on

#define DISP_CURS_SHIFT D4
#define DISP_CURS_SHIFT_SELECT D3 // 0 display, 1 cursor
#define DISP_CURS_SHIFT_DIR D2 // 0 right, 1 left

#define FUNC_MODE D5
#define FUNC_MODE_4_BIT D4 //4 bit data length, 0 4-bit, 1 8bit
#define FUNC_MODE_DISPLAY_LINES D3 //0 one line, 1 two lines
#define FUNC_MODE_FONT D2 //0 = 5X8 font, 1 = 5X10 font

//no function for this yet
#define CGRAM_SET D6 //custom character address

#define DDRAM_SET D7 //display data location/cursor location

//control pins
#define RNW_READ 1
#define RNW_WRITE 0

#define REG_SEL_FUNC 0
#define REG_SEL_RAM 1 

#define ENABLE_FALLING 0
#define ENABLE_RISING 1

/*
///////////////////Notes////////////////////
 values 0b0010 to 0b01111111 are ascii.
 
*/



//disp func
LCD_inputs_t * disp_clear(LCD_inputs_t* inputs){
	inputs->databus = (1 << CLEAR);
	return inputs;
}

LCD_inputs_t * disp_return(LCD_inputs_t* inputs){
	inputs->databus = (1 << DISP_RETURN);
	return inputs;
}

//display controls
LCD_inputs_t * disp_curs_mode(LCD_inputs_t* inputs, bool dispOn, bool cursOn, bool cursBlinkOn ){
	inputs->databus  = ((1 << DISP_CURS_MODES) | (dispOn << DISP_CURS_MODES_DISP_ON) | (cursOn << DISP_CURS_MODES_CURS_ON) | (cursBlinkOn <<  DISP_CURS_MODES_CURS_BLINK ));
	return inputs;
}

//cursor and display shift func
LCD_inputs_t * cursor_shift(LCD_inputs_t * inputs, bool cursorLeft0Right1, bool displayDont0Do1){
	inputs->databus |= ((1 << SHIFT_MODES) | (cursorLeft0Right1 << SHIFT_MODE_CURS));
	return inputs;
}

//func modes
LCD_inputs_t * func_mode(LCD_inputs_t * inputs, bool func4Bit0_8Bit1, bool func1Line0_2Line1, bool font8Bit0_10Bit1){
	inputs->databus = ((1 << FUNC_MODE) | (func4Bit0_8Bit1 << FUNC_MODE_4_BIT) | (func1Line0_2Line1 << FUNC_MODE_DISPLAY_LINES) | (font8Bit0_10Bit1 << FUNC_MODE_FONT ));
	return inputs;
}

//set ddram address to display
LCD_inputs_t * goto_ddram(LCD_inputs_t* inputs, uint8_t locaiton){
	inputs->databus = ((1 <<DDRAM_SET) | (locaiton));
	return inputs;
}

//write ascii char
LCD_inputs_t * write_char(LCD_inputs_t * inputs, uint8_t character){
	inputs->databus = character;
	inputs->reg_sel = 1;
	return inputs;
}










