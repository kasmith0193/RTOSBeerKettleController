/**
  * TWI Generated Driver File
  *
  * @file twi.c
  *
  * @ingroup i2c_host
  *
  * @brief This file contains the API implementations for the TWI module.
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

#include "../twi.h"
#include <stdbool.h>
#include <stdlib.h>
#include "../../system/utils/compiler.h"

#define STATUS_BIT_MASK_VALUE 0xF8

static void TWI_Close(void);
static void TWI_ReadStart(void);
static void TWI_WriteStart(void);
static void TWI_EventHandler(void);
static void TWI_DefaultCallback(void);

/* I2C Internal API's */
static uint8_t TWI_GetRxData(void);
static void TWI_SendTxData(uint8_t data);
static inline void TWI_ResetBus(void);
static inline void TWI_EnableRestart(void);
static inline void TWI_DisableRestart(void);
static inline void TWI_SendStop(void);
static inline void TWI_ClearErrorFlags(void);
static inline void TWI_EnableInterrupts(void);
static inline void TWI_DisableInterrupts(void);
static inline void TWI_ClearInterrupts(void);
static inline void TWI_HostSendAck(void);
static inline void TWI_HostSendNack(void);

/* Host */
/* TWI interfaces */
static i2c_event_states_t I2C_EVENT_IDLE(void);
static i2c_event_states_t I2C_EVENT_SEND_ADR_READ(void);   
static i2c_event_states_t I2C_EVENT_SEND_ADR_WRITE(void);
static i2c_event_states_t I2C_EVENT_TX(void);
static i2c_event_states_t I2C_EVENT_RX(void);
static i2c_event_states_t I2C_EVENT_SEND_START_READ(void);
static i2c_event_states_t I2C_EVENT_SEND_START_WRITE(void);
static i2c_event_states_t I2C_EVENT_SEND_RESTART(void);
static i2c_event_states_t I2C_EVENT_SEND_STOP(void);
static i2c_event_states_t I2C_EVENT_RX_ACK(void);
static i2c_event_states_t I2C_EVENT_TX_ACK(void);
static i2c_event_states_t I2C_EVENT_NACK_STOP(void);
static i2c_event_states_t I2C_EVENT_NACK_RESTART(void);
static i2c_event_states_t I2C_EVENT_RESET(void);
static i2c_event_states_t I2C_EVENT_ADDRESS_NACK(void);
static i2c_event_states_t I2C_EVENT_BUS_ERROR(void);

/**
  Section: Driver Interface
*/
const i2c_host_interface_t I2C0_Host = {
  .Initialize = TWI_Initialize,
  .Deinitialize = TWI_Deinitialize,
  .Write = TWI_Write,
  .Read = TWI_Read,
  .WriteRead = TWI_WriteRead,
  .TransferSetup = NULL,
  .ErrorGet = TWI_ErrorGet,
  .IsBusy = TWI_IsBusy,
  .CallbackRegister = TWI_CallbackRegister,
  .Tasks = TWI_Tasks
};

/**
 Section: Private Variable Definitions
 */

// I2C Event Callback List
typedef enum {
    I2C_DATA_COMPLETE = 0,
    I2C_WRITE_COLLISION,
    I2C_ADDRESSNACK,
    I2C_DATA_NACK,
    I2C_TIMEOUT,
    I2C_NULL
} I2C_callbackIndex_t;

static void (*TWI_Callback)(void) = NULL;
volatile i2c_event_status_t twi_Status = {0};

typedef i2c_event_states_t (*twieventHandler)(void);
const twieventHandler twi_eventTable[] = {
    I2C_EVENT_IDLE,     
    I2C_EVENT_SEND_ADR_READ,    
    I2C_EVENT_SEND_ADR_WRITE,
    I2C_EVENT_TX,
    I2C_EVENT_RX,
    I2C_EVENT_SEND_START_READ,
    I2C_EVENT_SEND_START_WRITE,
    I2C_EVENT_SEND_RESTART,
    I2C_EVENT_SEND_STOP,
    I2C_EVENT_RX_ACK,
    I2C_EVENT_TX_ACK,
    I2C_EVENT_NACK_STOP,
    I2C_EVENT_NACK_RESTART,
    I2C_EVENT_RESET,
    I2C_EVENT_ADDRESS_NACK,
    I2C_EVENT_BUS_ERROR
};

void TWI_Initialize(void)
{   
    //TWPS 1; TWS 0x0; 
    TWSR = 0x0;
    //TWA 0x0; TWGCE disabled; 
    TWAR = 0x0;
    //TWDR 0; 
    TWDR = 0x0;
    //TWEA disabled; TWEN disabled; TWIE disabled; TWINT disabled; TWSTA disabled; TWSTO disabled; TWWC disabled; 
    TWCR = 0x0;
    //TWAM 0x0; 
    TWAMR = 0x0;

    //Host Baud Rate Control
    TWBR = (uint8_t)TWI_BAUD(100000, 8000000, 1);
    
    
    
    TWI_CallbackRegister(TWI_DefaultCallback);
}

void TWI_Deinitialize(void)
{  
    //TWPS 1; TWS 0x0; 
    TWSR = 0x00;
    //TWA 0x0; TWGCE disabled; 
    TWAR = 0x00;
    //TWDR 0; 
    TWDR = 0x00;
    //TWEA disabled; TWEN disabled; TWIE disabled; TWINT disabled; TWSTA disabled; TWSTO disabled; TWWC disabled; 
    TWCR = 0x00;
    //TWAM 0x0; 
    TWAMR = 0x00;

    //Host Baud Rate Control
    TWBR = (uint8_t)TWI_BAUD(100000, 8000000, 1);

    
    
    TWI_CallbackRegister(TWI_DefaultCallback);
}

bool TWI_Write(uint16_t address, uint8_t *data, size_t dataLength)
{
    bool retStatus = false;
    if (!TWI_IsBusy())
    {
        twi_Status.busy = true;
        twi_Status.address = address;
        twi_Status.switchToRead = false;
        twi_Status.writePtr = data;
        twi_Status.writeLength = dataLength;
        twi_Status.readPtr = NULL;
        twi_Status.readLength = 0;
        twi_Status.errorState = I2C_ERROR_NONE;
        TWI_WriteStart();
        retStatus = true;
    }
    return retStatus;
}

bool TWI_Read(uint16_t address, uint8_t *data, size_t dataLength)
{
    bool retStatus = false;
    if (!TWI_IsBusy())
    {
        twi_Status.busy = true;
        twi_Status.address = address;
        twi_Status.switchToRead = false;
        twi_Status.readPtr = data;
        twi_Status.readLength = dataLength;
        twi_Status.writePtr = NULL;
        twi_Status.writeLength = 0;
        twi_Status.errorState = I2C_ERROR_NONE;
        TWI_ReadStart();
        retStatus = true;
    }
    return retStatus;
}

bool TWI_WriteRead(uint16_t address, uint8_t *writeData, size_t writeLength, uint8_t *readData, size_t readLength)
{
    bool retStatus = false;
    if (!TWI_IsBusy())
    {
        twi_Status.busy = true;
        twi_Status.address = address;
        twi_Status.switchToRead = true;
        twi_Status.writePtr = writeData;
        twi_Status.writeLength = writeLength;
        twi_Status.readPtr = readData;
        twi_Status.readLength = readLength;
        twi_Status.errorState = I2C_ERROR_NONE;
        TWI_WriteStart();
        retStatus = true;
    }
    return retStatus;
}

i2c_host_error_t TWI_ErrorGet(void)
{
    i2c_host_error_t retErrorState = twi_Status.errorState;
    twi_Status.errorState = I2C_ERROR_NONE;
    return retErrorState;
}

bool TWI_IsBusy(void)
{
    return (twi_Status.busy);
}

void TWI_CallbackRegister(void (*callbackHandler)(void))
{
    if (callbackHandler != NULL)
    {
        TWI_Callback = callbackHandler;
    }
}

void TWI_Tasks(void)
{
    
    bool retStatus = TWI_IsBusy();
    if (retStatus)
    {
        if(twi_Status.errorState == I2C_ERROR_NONE)
        {
            if (TWCR & (1 << TWINT))
            {
                TWI_EventHandler();
            }
        }
    }
}

/**
 Section: Private Interfaces
 */
static void TWI_StartSend(void)
{
    //Enable TWI Start
    TWCR |= ((1 << TWSTA) | (1 << TWINT) | (1 << TWEN));
}

static inline void TWI_ClearStart(void)
{
    //Clear TWI Start
    TWCR  &= ~(1 << TWSTA);
}

static void TWI_ReadStart(void)
{
    twi_Status.state = I2C_EVENT_SEND_START_READ();
}

static void TWI_WriteStart(void)
{
    twi_Status.state = I2C_EVENT_SEND_START_WRITE();
}

static void TWI_Close(void)
{
    twi_Status.busy = false;
    twi_Status.address = 0xFF;
    twi_Status.writePtr = NULL;
    twi_Status.readPtr = NULL;
    twi_Status.state = I2C_STATE_IDLE;
    TWI_ClearInterrupts();
    TWI_DisableInterrupts();
}

static void TWI_EventHandler(void)
{
    twi_Status.state = twi_eventTable[twi_Status.state]();
}

static uint8_t TWI_GetStatus(void)
{
    return TWSR & STATUS_BIT_MASK_VALUE;
}

static void TWI_DefaultCallback(void)
{
    // Default Callback for Error Indication
}

/* I2C Event interfaces */
static i2c_event_states_t I2C_EVENT_RESET(void)
{
    TWI_ResetBus();
    twi_Status.busy = false;
    twi_Status.errorState = I2C_ERROR_NONE;
    return I2C_STATE_RESET;
}

static i2c_event_states_t I2C_EVENT_IDLE(void)
{
    //TWI_ResetBus();
    twi_Status.busy = false;
    twi_Status.errorState = I2C_ERROR_NONE;
    return I2C_STATE_IDLE;
}

static i2c_event_states_t I2C_EVENT_SEND_START_READ(void)
{
    TWI_StartSend();
    return I2C_STATE_SEND_ADR_READ;
}

static i2c_event_states_t I2C_EVENT_SEND_START_WRITE(void)
{
    TWI_StartSend();
    return I2C_STATE_SEND_ADR_WRITE;
}

static i2c_event_states_t I2C_EVENT_SEND_RESTART(void)
{
    TWI_StartSend();
    return I2C_EVENT_SEND_START_READ();
}

static i2c_event_states_t I2C_EVENT_SEND_STOP(void)
{
    TWI_SendStop();
    TWI_Close();
    return I2C_STATE_IDLE;
}

static i2c_event_states_t I2C_EVENT_ADDRESS_NACK(void)
{
    twi_Status.errorState = I2C_ERROR_FAIL;
    
	return I2C_EVENT_SEND_STOP();
}

static i2c_event_states_t I2C_EVENT_SEND_ADR_READ(void)
{
    // Check if START or REPSTART was successfully sent
	if (!(((TWI_GetStatus() == 0x08) || (TWI_GetStatus() == 0x10))))
		return I2C_EVENT_RESET();

	TWI_SendTxData((twi_Status.address << 1) | 1);
	
    // Clear Start bit
	TWI_ClearStart();

	// Clearing INT flag starts operation
	TWI_ClearInterrupts();

	return I2C_STATE_RX_ACK;
}

static i2c_event_states_t I2C_EVENT_SEND_ADR_WRITE(void)
{
    // Check if START or REPSTART was successfully sent
	if (!(((TWI_GetStatus() == 0x08) || (TWI_GetStatus() == 0x10))))
		return I2C_EVENT_RESET();

	TWI_SendTxData(twi_Status.address << 1);
	
    // Clear Start bit
	TWI_ClearStart();

	// Clearing INT flag starts operation
	TWI_ClearInterrupts();

	return I2C_STATE_TX_ACK;
}

static i2c_event_states_t I2C_EVENT_RX_ACK(void)
{
    if (twi_Status.readLength == 1)
        TWI_HostSendAck();
    else
        TWI_HostSendNack();

	return I2C_STATE_RX;
}

static i2c_event_states_t I2C_EVENT_TX_ACK(void)
{
    // Check if SLA+W received NACK
	//if (!((TWI_GetStatus() == 0x18)))
	//	return I2C_EVENT_ADDRESS_NACK();
        
	return I2C_STATE_TX;
}

static i2c_event_states_t I2C_EVENT_NACK_STOP(void)
{
	TWI_SendStop();
	return I2C_STATE_IDLE;
}

static i2c_event_states_t I2C_EVENT_NACK_RESTART(void)
{
	TWI_StartSend();
	return I2C_EVENT_SEND_START_READ();
}

static i2c_event_states_t I2C_EVENT_TX(void)
{
    if (((TWI_GetStatus() == 0x30) || (TWI_GetStatus() == 0x48) || (TWI_GetStatus() == 0x20))) // Slave replied with NACK
	{

		return I2C_EVENT_SEND_STOP();
	} 
    else
    {
        if((twi_Status.writeLength)--)
        {
            TWI_SendTxData(*twi_Status.writePtr++);
            // Clearing INT flag starts operation
            TWI_ClearInterrupts();
            return I2C_STATE_TX;
        }
        else
        {
            if(twi_Status.switchToRead) 
            {
                twi_Status.switchToRead = false;
                return I2C_EVENT_SEND_START_READ();
            }
            else
                return I2C_EVENT_SEND_STOP();
        }
	}
}

static i2c_event_states_t I2C_EVENT_RX(void)
{
	if ((TWI_GetStatus() != 0x50) && (TWI_GetStatus() != 0x58))
		return I2C_EVENT_RESET();

	if (--twi_Status.readLength) 
    {
		*twi_Status.readPtr = TWI_GetRxData();
		twi_Status.readPtr++;
		// Clearing INT flag starts operation
	    TWI_ClearInterrupts();
		return I2C_EVENT_RX();
	} 
    else 
    {
		*twi_Status.readPtr = TWI_GetRxData();
		twi_Status.readPtr++;
		TWI_HostSendNack();
        return I2C_EVENT_SEND_STOP();
	}
}

static i2c_event_states_t I2C_EVENT_BUS_ERROR(void)
{
    TWI_ResetBus();
    twi_Status.busy = false;
    twi_Status.errorState = I2C_ERROR_FAIL;
    return I2C_EVENT_RESET();
}

/**
 Section: Register Level Interfaces
 */

static uint8_t TWI_GetRxData(void)
{
    return TWDR;
}

static void TWI_SendTxData(uint8_t data)
{
    TWDR = data;
}

static inline void TWI_ResetBus(void)
{
    //Set Clear Buffer Flag
    TWCR = ((1 << TWSTO) | (1 << TWINT));
}

static inline void TWI_EnableRestart(void)
{
    //Enable TWI Restart
    TWCR |= ((1 << TWSTA)| (1 << TWINT));
}

static inline void TWI_DisableRestart(void)
{
    /*
    //Disable TWI Restart
    TWCR  &= ~(1 << TWSTA);
    */
}

static inline void TWI_SendStop(void)
{
    //Clear Start Bit
    TWCR |= ((1 << TWSTO) | (1 << TWINT) | (1 << TWEN));
}

static inline void TWI_ClearErrorFlags(void)
{
    TWCR &= ~(1 << TWEA);
}

static inline void TWI_HostSendAck(void)
{
    TWCR &= ~(1 << TWEA);
}

static inline void TWI_HostSendNack(void)
{
    TWCR |= (1 << TWEA);
}

static inline void TWI_EnableInterrupts(void)
{
    TWCR |= (1 << TWIE);
}

static inline void TWI_DisableInterrupts(void)
{
    TWCR &= ~(1 << TWIE);
}

static inline void TWI_ClearInterrupts(void)
{
    TWCR |= (1 << TWINT);
}