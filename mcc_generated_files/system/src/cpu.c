/**
  * CPU Generated Driver File
  *
  * @file cpu.c
  *
  * @ingroup cpu
  *
  * @brief This file contains the API implemenatation for the CPU driver.
  *
  * @version CPU Driver Version 1.0.0
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

#include <avr/io.h>
#include "../cpu.h"

void CPU_Initialize (void)
{
    //PRADC disabled; PRSPI disabled; PRTIM0 disabled; PRTIM1 disabled; PRTIM2 disabled; PRTWI disabled; PRUSART0 disabled; 
    PRR = 0x0;

    //CLKPCE disabled; CLKPS 1; 
    CLKPR = 0x0;

    //SE disabled; SM IDLE; 
    SMCR = 0x0;

    //BODS disabled; BODSE disabled; IVCE disabled; IVSEL disabled; PUD disabled; 
    MCUCR = 0x0;

}

void CPU_EnableSleep(void)
{
	SMCR |= (1 << SE);
}

void CPU_DisableSleep(void)
{
	SMCR &= ~(1 << SE);
}

void CPU_SetSleepMode(uint8_t mode)
{
	SMCR = mode | (SMCR & ~((1 << SM0) | (1 << SM1) | (1 << SM2)));
}

void CPU_EnableLowPower(void)
{
	/* On AVR devices all peripherals are enabled from power on reset, this
	 * disables all peripherals to save power. Driver shall enable
	 * peripheral if used */

	  PRR = (1 << PRTWI) | (1 << PRTIM2) | (1 << PRTIM0) | (1 << PRTIM1) | (1 << PRSPI) | (1 << PRUSART0) | (1 << PRADC);
}



/**
 End of File
*/