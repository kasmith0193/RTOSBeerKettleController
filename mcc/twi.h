/**
 * TWI Generated Driver API Header File
 *
 * @file twi.h
 *
 * @defgroup i2c_host TWI_HOST
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

#ifndef TWI_H
#define TWI_H

/**
  Section: Included Files
*/

/// \cond
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
/// \endcond
#include "i2c_host_types.h"
#include "i2c_host_interface.h"
#include "i2c_host_event_types.h"


/**
 Section: Data Type Definitions
*/

#define i2c0_host_host_interface I2C0_Host


#define I2C0_Host_Initialize TWI_Initialize
#define I2C0_Host_Deinitialize TWI_Deinitialize
#define I2C0_Host_Write TWI_Write
#define I2C0_Host_Read TWI_Read
#define I2C0_Host_WriteRead TWI_WriteRead
#define I2C0_Host_ErrorGet TWI_ErrorGet
#define I2C0_Host_IsBusy TWI_IsBusy
#define I2C0_Host_CallbackRegister TWI_CallbackRegister
#define I2C0_Host_Tasks TWI_Tasks

extern const i2c_host_interface_t I2C0_Host;

#define TWI_BAUD(F_SCL, CLK_PER, PRESCALE)    \
    (((CLK_PER / F_SCL) - 16) / (2 * PRESCALE))

/**
 * @ingroup i2c_host
 * @brief Initializes the I2C0_Host driver.
 * @param None.
 * @return None.
 */ 
void TWI_Initialize(void);

/**
 * @ingroup i2c_host
 * @brief Deinitializes the I2C0_Host driver. It disables the I2C0_Host module.
 * @param None.
 * @return None.
 */
void TWI_Deinitialize(void);

/**
 * @ingroup i2c_host
 * @brief Writes the data to a Client on the bus.
 * @param[in] uint16_t address  - 7-bit/10-bit Client address.
 * @param[in] uint8_t *data     - pointer to source data buffer that contains the data to be transmitted.
 * @param[in] size_t dataLength - length of data buffer in number of bytes to be written.
 * @return True  - The request was placed successfully and the bus activity was initiated.
 * @return False - The request fails, if there was already a transfer in progress when this function was called.
 */
bool TWI_Write(uint8_t address, uint8_t *data, size_t dataLength);

/**
 * @ingroup i2c_host
 * @brief Reads the data from a client on the bus.
 * @param[in] uint16_t address  - 7-bit/10-bit Client address.
 * @param[out] uint8_t *data    - pointer to destination data buffer that contains the data to be received.
 * @param[in] size_t dataLength - length of data buffer in number of bytes to be read.
 * @return True  - The request was placed successfully and the bus activity was initiated.
 * @return False - The request fails, if there was already a transfer in progress when this function was called.
 */
bool TWI_Read(uint16_t address, uint8_t *data, size_t dataLength);

/**
 * @ingroup i2c_host
 * @brief Writes data from the writeData to the bus and then reads data from the Client 
 *        and stores the received in the readData.
 * @param[in]  uint16_t address    - 7-bit/10-bit Client address.
 * @param[out] uint8_t *writeData  - pointer to the write data buffer.
 * @param[in]  size_t writeLength  - write the data length in bytes.
 * @param[in]  uint8_t *readData   - pointer to the read data buffer.
 * @param[in]  size_t readLength   - read the data length in bytes.
 * @return True  - The request was placed successfully and the bus activity was initiated.
 * @return False - The request fails, if there was already a transfer in progress when this function was called.
 */
bool TWI_WriteRead(uint16_t address, uint8_t *writeData, size_t writeLength, uint8_t *readData, size_t readLength);

/**
 * @ingroup i2c_host
 * @brief Gets the error that occurred during the I2C Transmit and Receive. 
 * @param None.
 * @return i2c_host_error_t - I2C error code staus.
 */
i2c_host_error_t TWI_ErrorGet(void);

/**
 * @ingroup i2c_host
 * @brief Checks if I2C is busy.
 * @param None.
 * @return True  - I2C is busy.
 * @return False - I2C is free.
 */
bool TWI_IsBusy(void);

/**
 * @ingroup i2c_host
 * @brief This is polling function for non interrupt mode.
 * @param None.
 * @return None.
 */
void TWI_Tasks(void);

/**
 * @ingroup i2c_host
 * @brief Setter function for I2C interrupt callback. It is called when an error occurs.
 * @param void *CallbackHandler - Pointer to custom callback.
 * @return None.
 */
void TWI_CallbackRegister(void (*callbackHandler)(void));

#endif //TWI_H
