/**
 * aht21.h
 *
 * Created: 11/26/2024 11:33:07 PM
 *  Author: kasmi
 */ 


#ifndef AHT21_H_
#define AHT21_H_

/// \cond
#include <stdint.h>
/// \endcond

/**
 * Provides the twi_read, twi_write functions etc.
 * May need to make more generic later for portability.
 */
#include "twi_interface/mcc_twi_interface.h"

#define write twi_write
#define read twi_read


typedef struct AHTOBJ ahtObj_t;
struct AHTOBJ {
	uint8_t address;
	uint8_t send[4];
	uint8_t rec[7];
	uint32_t humd_raw;
	uint32_t temp_raw;
	float humd_float;
	float temp_float;
	char humd_str[6];
	char temp_str[6];
	void (*getdata)(ahtObj_t* ahtObj);
};


void AHT_init(ahtObj_t * ahtObj, uint8_t address);


#endif /* AHT21_H_ */