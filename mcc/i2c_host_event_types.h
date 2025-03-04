/**
 * TWI Generated Driver API Header File
 *
 * @file {moduleGroupNameLowerCase}_host_event_types.h
 *
 * @defgroup twi_host_event TWI_HOST_EVENT
 *
 * @brief This header file provides the API prototypes for the TWI driver.
 *
 * @version TWI Driver Version 1.0.0
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

#ifndef I2C_HOST_EVENT_TYPES_H
#define	I2C_HOST_EVENT_TYPES_H

#include "i2c_host_types.h"

/**
 * @ingroup twi_host_event
 * @typedef enum i2c_event_states_t
 * @brief Enumeration for I2C states.
 */
typedef enum
{
    I2C_STATE_IDLE,     
    I2C_STATE_SEND_ADR_READ,    
    I2C_STATE_SEND_ADR_WRITE,
    I2C_STATE_TX,
    I2C_STATE_RX,
    I2C_STATE_SEND_START_READ,
    I2C_STATE_SEND_START_WRITE,
    I2C_STATE_SEND_RESTART,
    I2C_STATE_SEND_STOP,
    I2C_STATE_RX_ACK,
    I2C_STATE_TX_ACK,
    I2C_STATE_NACK_STOP,
    I2C_STATE_NACK_RESTART,
    I2C_STATE_RESET,
    I2C_STATE_ADDRESS_NACK,
    I2C_STATE_BUS_ERROR
} i2c_event_states_t;

/**
 * @ingroup twi_host_event
 * @typedef struct i2c_event_status_t
 * @brief I2C Event Status Structure.
 */
typedef struct
{
    bool busy;
    uint8_t address;
    uint8_t *writePtr;
    size_t writeLength;
    uint8_t *readPtr;
    size_t readLength;
    bool switchToRead;
    i2c_host_error_t errorState; 
    i2c_event_states_t state;
} i2c_event_status_t;

#endif // end of I2C_HOST_EVENT_TYPES_H
