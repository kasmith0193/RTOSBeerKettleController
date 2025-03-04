/**
 * LCD_interface.h
 *
 * Created: 9/10/2024 8:10:28 PM
 *  Author: kasmi
 */ 



/// \cond
#include <stdint.h>
#include <stdbool.h>
/// \endcond

/**
 * Provides the twi_read, twi_write functions etc.
 * May need to make more generic later for portability.
 */
#include "twi_interface/mcc_twi_interface.h"

/*
 * Macros
 */

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
 * Data Structure
 */

typedef struct LCDOBJ LCDObj_t;
struct LCDOBJ {
	uint8_t i2c_address;
	uint8_t databus;
	uint8_t data[4];
	bool enable;
	bool rnw;
	bool reg_sel;
	bool light;

	void (*writeStringAt)(LCDObj_t*, char* string, uint8_t size, uint8_t address);
	void (*clear)(LCDObj_t* lcdObj);
};
/*
 *
 */

// Does this need to be moved up??
#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_
void LCD_Init(LCDObj_t*, uint8_t, bool);

//void writeStringAt(uint8_t * string, uint8_t size, uint8_t address);
//void read( uint8_t address7Bit, uint8_t * data_ptr, uint8_t size);
#endif /* LCD_INTERFACE_H_ */