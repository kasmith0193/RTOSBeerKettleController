/**
 * mcc_twi_interface.h
 *
 * Created: 11/26/2024 10:48:53 PM
 *  Author: kasmi
 */ 


#ifndef MCC_TWI_INTERFACE_H_
#define MCC_TWI_INTERFACE_H_
/// \cond
#include <stdint.h>
/// \endcond

#include "mcc/twi.h"


// These could be converted to RT style code
// if we jump into the .c file we can see that
// that i have opted to complete the twi task
// at the time of execution.

// The c file also needs error propagation


void twi_write(uint8_t address7Bit, uint8_t * data_ptr, uint8_t size);
void twi_read (uint8_t address7Bit, uint8_t * data_ptr, uint8_t size);
void twi_writeread(uint8_t address7Bit, uint8_t * write_ptr, uint8_t write_size, uint8_t* read_ptr, uint8_t read_size );


#endif /* MCC_TWI_INTERFACE_H_ */