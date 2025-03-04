/**
 * Generated Pins Header File
 * 
 * @file pins.h
 * 
 * @defgroup  pinsdriver Pins Driver
 * 
 * @brief This file contains the API prototypes and function macros for the Pins driver.
 *
 * @version Driver Version  1.0.0
*/ 

/*
© [2024] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

#ifndef PINS_H_INCLUDED
#define PINS_H_INCLUDED

/// \cond
#include <avr/io.h>
/// \endcond
#include "./port.h"
/**  
 * @ingroup  pinsdriver
 * @name Pin Function Macros
 * Macros for the individual pin functions.
 * @note These sets of macros are generated for all the selected pins in the Pins module.
 */
 ///@{

//get/set IO_PC5 aliases
#define IO_PC5_SetHigh() do { PORTC |= 0x20; } while(0)
#define IO_PC5_SetLow() do { PORTC &= ~0x20; } while(0)
#define IO_PC5_Toggle() do { PINC |= 0x20; } while(0)
#define IO_PC5_GetValue() (PINC & (0x1 << 5))
#define IO_PC5_SetDigitalInput() do { DDRC &= ~0x20; } while(0)
#define IO_PC5_SetDigitalOutput() do { DDRC |= 0x20; } while(0)
#define IO_PC5_SetPullUp() do { PORTC |= 0x20; } while(0)
#define IO_PC5_ResetPullUp() do { PORTC &= ~0x20; } while(0)

//get/set IO_PC4 aliases
#define IO_PC4_SetHigh() do { PORTC |= 0x10; } while(0)
#define IO_PC4_SetLow() do { PORTC &= ~0x10; } while(0)
#define IO_PC4_Toggle() do { PINC |= 0x10; } while(0)
#define IO_PC4_GetValue() (PINC & (0x1 << 4))
#define IO_PC4_SetDigitalInput() do { DDRC &= ~0x10; } while(0)
#define IO_PC4_SetDigitalOutput() do { DDRC |= 0x10; } while(0)
#define IO_PC4_SetPullUp() do { PORTC |= 0x10; } while(0)
#define IO_PC4_ResetPullUp() do { PORTC &= ~0x10; } while(0)
///@}

/**
 * @ingroup  pinsdriver
 * @brief Initializes the General Purpose Input/Output (GPIO), peripheral I/O pins and related registers.
 * @param None.
 * @return None.
 */
void PIN_MANAGER_Initialize();

#endif /* PINS_H_INCLUDED */
