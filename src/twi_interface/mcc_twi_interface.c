/**
 * mcc_twi_interface.c
 *
 * Created: 11/26/2024 10:32:31 PM
 *  Author: kasmi
 */ 

#include "twi_interface/mcc_twi_interface.h"




void twi_write(uint8_t address7Bit, uint8_t * data_ptr, uint8_t size){
	
	if(I2C0_Host.Write(address7Bit, data_ptr,size)){
		while(I2C0_Host.IsBusy()){
			I2C0_Host.Tasks();
		}
		i2c_host_error_t i2c_error = I2C0_Host.ErrorGet();
		if (i2c_error == I2C_ERROR_NONE){
			//success
			asm("nop");
			}else{
			//error
			asm("nop");
		}
	}
	
}

void twi_read( uint8_t address7Bit, uint8_t * data_ptr, uint8_t size){
	
	if(I2C0_Host.Read(address7Bit, data_ptr,size)){
		while(I2C0_Host.IsBusy()){
			I2C0_Host.Tasks();
			//_delay_ms(5000);
		}
		i2c_host_error_t i2c_error = I2C0_Host.ErrorGet();
		if (i2c_error == I2C_ERROR_NONE){
			//success
			asm("nop");
			}else{
			//error
			asm("nop");
		}
	}
	
}

void twi_writeread(uint8_t address7Bit, uint8_t * write_ptr, uint8_t write_size, uint8_t* read_ptr, uint8_t read_size ){
	if(I2C0_Host.WriteRead(address7Bit, write_ptr, write_size, read_ptr, read_size)){
		while(I2C0_Host.IsBusy()){
			I2C0_Host.Tasks();
		}
		i2c_host_error_t i2c_error = I2C0_Host.ErrorGet();
		if (i2c_error == I2C_ERROR_NONE){
			//success
			asm("nop");
			}else{
			//error
			asm("nop");
		}
	}
	
}