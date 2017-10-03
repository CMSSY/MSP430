//*****************************************************************************
//
// Copyright (C) 2014 Texas Instruments Incorporated - http://www.ti.com/
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//
//  Redistributions of source code must retain the above copyright
//  notice, this list of conditions and the following disclaimer.
//
//  Redistributions in binary form must reproduce the above copyright
//  notice, this list of conditions and the following disclaimer in the
//  documentation and/or other materials provided with the
//  distribution.
//
//  Neither the name of Texas Instruments Incorporated nor the names of
//  its contributors may be used to endorse or promote products derived
//  from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//****************************************************************************
#include <stdbool.h>
#include <stdint.h>
#include <msp430.h>
#include "i2c.h"

//*****************************************************************************
//
// Global Data
//
//*****************************************************************************
volatile eUSCI_status ui8Status;

uint8_t  *globalData;
uint8_t  ui8DummyRead;
uint32_t g_ui32ByteCount;
bool     burstMode = false;

/* Debugging variables */
uint16_t count_NACK = 0;
uint16_t count_INT = 0;
uint16_t count_START = 0;
uint16_t count_STOP = 0;
uint16_t count_REC = 0;
uint16_t count_TRANS = 0;

void initI2C(void)
{
    /* Select I2C function for P1.7(SCL) & P1.6(SDA) */
    GPIO_setAsPeripheralModuleFunctionOutputPin(I2C_PORT, I2C_PIN_SDA | I2C_PIN_SCL,
            GPIO_PRIMARY_MODULE_FUNCTION);

}

bool writeI2C(uint8_t p_addr, uint8_t p_reg, uint8_t *p_data,
			  uint8_t p_byteCount, EUSCI_B_I2C_initMasterParam* p_params)
{
	/* Wait until ready to write */
    while (EUSCI_B_I2C_isBusBusy(EUSCI_B0_BASE));

	/* Assign Data to local Pointer */
	globalData = p_data;

    /* Disable I2C module to make changes */
	EUSCI_B_I2C_disable(EUSCI_B0_BASE);

	/* Setup the number of bytes to transmit + 1 to account for the register byte */
	p_params->byteCounterThreshold = p_byteCount + 1;
	EUSCI_B_I2C_initMaster(EUSCI_B0_BASE, (const EUSCI_B_I2C_initMasterParam *)p_params);

	/* Load device slave address */
	EUSCI_B_I2C_setSlaveAddress(EUSCI_B0_BASE, p_addr);

    /* Enable I2C Module to start operations */
	EUSCI_B_I2C_enable(EUSCI_B0_BASE);

  	/* Enable master STOP, TX and NACK interrupts */
	EUSCI_B_I2C_enableInterrupt(EUSCI_B0_BASE, EUSCI_B_I2C_STOP_INTERRUPT +
    		EUSCI_B_I2C_NAK_INTERRUPT + EUSCI_B_I2C_TRANSMIT_INTERRUPT0);

    /* Set our local state to Busy */
    ui8Status = eUSCI_BUSY;

	/* Send start bit and register */
    EUSCI_B_I2C_masterSendMultiByteStart(EUSCI_B0_BASE, p_reg);

  	/* Enable master interrupt for the remaining data */
    //! \TODO check if this works
    EUSCI_B_I2C_enableInterrupt(EUSCI_B0_BASE, 0xFFFF);

	// NOW WAIT FOR DATA BYTES TO BE SENT
	while(ui8Status == eUSCI_BUSY)
	{
//#ifdef USE_LPM
//		MAP_PCM_gotoLPM0();
//#else
//		__no_operation();
//#endif
	}

	/* Disable interrupts */
	EUSCI_B_I2C_disableInterrupt(EUSCI_B0_BASE, EUSCI_B_I2C_STOP_INTERRUPT +
			EUSCI_B_I2C_NAK_INTERRUPT + EUSCI_B_I2C_TRANSMIT_INTERRUPT0);
//    MAP_Interrupt_disableInterrupt(INT_EUSCIB1);

	if(ui8Status == eUSCI_NACK)
	{
		return(false);
	}
	else
	{
		return(true);
	}
}


bool readI2C(uint8_t p_addr, uint8_t p_reg, uint8_t *p_data,
			 uint8_t p_byteCount, EUSCI_B_I2C_initMasterParam* p_params)
{
	/* \TODO put a delay */
	/* Wait until ready */
    while (EUSCI_B_I2C_isBusBusy(EUSCI_B0_BASE));

	/* Assign Data to local Pointer */
	globalData = p_data;

    /* Disable I2C module to make changes */
	EUSCI_B_I2C_disable(EUSCI_B0_BASE);

  	/* Setup the number of bytes to receive */
	p_params->byteCounterThreshold = p_byteCount;
	p_params->autoSTOPGeneration = EUSCI_B_I2C_SEND_STOP_AUTOMATICALLY_ON_BYTECOUNT_THRESHOLD;
	EUSCI_B_I2C_initMaster(EUSCI_B0_BASE, (const EUSCI_B_I2C_initMasterParam *)p_params);

	/* Load device slave address */
	EUSCI_B_I2C_setSlaveAddress(EUSCI_B0_BASE, p_addr);

    /* Enable I2C Module to start operations */
	EUSCI_B_I2C_enable(EUSCI_B0_BASE);

  	/* Enable master STOP and NACK interrupts */
	EUSCI_B_I2C_enableInterrupt(EUSCI_B0_BASE, EUSCI_B_I2C_STOP_INTERRUPT +
    		EUSCI_B_I2C_NAK_INTERRUPT);

    /* Set our local state to Busy */
    ui8Status = eUSCI_BUSY;

  	/* Send start bit and register */
    EUSCI_B_I2C_masterSendMultiByteStart(EUSCI_B0_BASE, p_reg);

  	/* Enable master interrupt for the remaining data */
    //! \TODO check if this works
    EUSCI_B_I2C_enableInterrupt(EUSCI_B0_BASE, 0xFFFF);

  	/* NOTE: If the number of bytes to receive = 1, then as target register is being shifted
  	 * out during the write phase, UCBxTBCNT will be counted and will trigger STOP bit prematurely
  	 * If count is > 1, wait for the next TXBUF empty interrupt (just after reg value has been
  	 * shifted out
  	 */
	while(ui8Status == eUSCI_BUSY)
	{
		if(EUSCI_B_I2C_getInterruptStatus(EUSCI_B0_BASE, EUSCI_B_I2C_TRANSMIT_INTERRUPT0))
		{
			ui8Status = eUSCI_IDLE;
		}
	}

	ui8Status = eUSCI_BUSY;

  	/* Turn off TX and generate RE-Start */
	EUSCI_B_I2C_masterReceiveStart(EUSCI_B0_BASE);

  	/* Enable RX interrupt */
	EUSCI_B_I2C_enableInterrupt(EUSCI_B0_BASE, EUSCI_B_I2C_RECEIVE_INTERRUPT0);

	/* Wait for all data be received */
	while(ui8Status == eUSCI_BUSY)
	{
//
//#ifdef USE_LPM
//		MAP_PCM_gotoLPM0();
//#else
//		__no_operation();
//#endif
	}

	/* Disable interrupts */
	EUSCI_B_I2C_disableInterrupt(EUSCI_B0_BASE, EUSCI_B_I2C_STOP_INTERRUPT +
			EUSCI_B_I2C_NAK_INTERRUPT + EUSCI_B_I2C_RECEIVE_INTERRUPT0);
//    MAP_Interrupt_disableInterrupt(INT_EUSCIB1);

	if(ui8Status == eUSCI_NACK)
	{
		return(false);
	}
	else
	{
		return(true);
	}
}


bool readBurstI2C(uint8_t p_addr, uint8_t p_reg, uint8_t *p_data,
				  uint32_t p_byteCount, EUSCI_B_I2C_initMasterParam* p_params)
{
	/* Todo: Put a delay */
	/* Wait until ready */
    while (EUSCI_B_I2C_isBusBusy(EUSCI_B0_BASE));

	/* Assign Data to local Pointer */
	globalData = p_data;

    /* Disable I2C module to make changes */
	EUSCI_B_I2C_disable(EUSCI_B0_BASE);

  	/* Setup the number of bytes to receive */
    p_params->autoSTOPGeneration = EUSCI_B_I2C_NO_AUTO_STOP;
    g_ui32ByteCount = p_byteCount;
    burstMode = true;
    EUSCI_B_I2C_initMaster(EUSCI_B0_BASE, (const EUSCI_B_I2C_initMasterParam *)p_params);

	/* Load device slave address */
    EUSCI_B_I2C_setSlaveAddress(EUSCI_B0_BASE, p_addr);

    /* Enable I2C Module to start operations */
    EUSCI_B_I2C_enable(EUSCI_B0_BASE);

  	/* Enable master STOP and NACK interrupts */
    EUSCI_B_I2C_enableInterrupt(EUSCI_B0_BASE, EUSCI_B_I2C_STOP_INTERRUPT +
    		EUSCI_B_I2C_NAK_INTERRUPT);

    /* Set our local state to Busy */
    ui8Status = eUSCI_BUSY;

  	/* Send start bit and register */
    EUSCI_B_I2C_masterSendMultiByteStart(EUSCI_B0_BASE, p_reg);

  	/* Enable master interrupt for the remaining data */
    //! \TODO check if this works
    EUSCI_B_I2C_enableInterrupt(EUSCI_B0_BASE, 0xFFFF);

  	/* NOTE: If the number of bytes to receive = 1, then as target register is being shifted
  	 * out during the write phase, UCBxTBCNT will be counted and will trigger STOP bit prematurely
  	 * If count is > 1, wait for the next TXBUF empty interrupt (just after reg value has been
  	 * shifted out
  	 */
	while(ui8Status == eUSCI_BUSY)
	{
		if(EUSCI_B_I2C_getInterruptStatus(EUSCI_B0_BASE, EUSCI_B_I2C_TRANSMIT_INTERRUPT0))
		{
			ui8Status = eUSCI_IDLE;
		}
	}

	ui8Status = eUSCI_BUSY;

  	/* Turn off TX and generate RE-Start */
	EUSCI_B_I2C_masterReceiveStart(EUSCI_B0_BASE);

  	/* Enable RX interrupt */
	EUSCI_B_I2C_enableInterrupt(EUSCI_B0_BASE, EUSCI_B_I2C_RECEIVE_INTERRUPT0);

	/* Wait for all data be received */
	while(ui8Status == eUSCI_BUSY)
	{

//#ifdef USE_LPM
//		MAP_PCM_gotoLPM0();
//#else
//		__no_operation();
//#endif
	}

	/* Disable interrupts */
	EUSCI_B_I2C_disableInterrupt(EUSCI_B0_BASE, EUSCI_B_I2C_STOP_INTERRUPT +
			EUSCI_B_I2C_NAK_INTERRUPT + EUSCI_B_I2C_RECEIVE_INTERRUPT0);
//    MAP_Interrupt_disableInterrupt(INT_EUSCIB1);

	if(ui8Status == eUSCI_NACK)
	{
		return(false);
	}
	else
	{
		return(true);
	}
}

/***********************************************************
  Function: EUSCIB0_IRQHandler
 */
void EUSCIB0_IRQHandler(void)
{
    uint_fast16_t status;

    status = EUSCI_B_I2C_getInterruptStatus(EUSCI_B0_BASE, 0xFFFF);
    EUSCI_B_I2C_clearInterrupt(EUSCI_B0_BASE, status);

    count_INT++;

    if (status & EUSCI_B_I2C_NAK_INTERRUPT)
    {
    	/* Generate STOP when slave NACKS */
    	EUSCI_B_I2C_masterSendMultiByteStop(EUSCI_B0_BASE);

        count_NACK++;

    	/* Clear any pending TX interrupts */
        EUSCI_B_I2C_clearInterrupt(EUSCI_B0_BASE, EUSCI_B_I2C_TRANSMIT_INTERRUPT0);

        /* Set our local state to NACK received */
        ui8Status = eUSCI_NACK;
    }

    if (status & EUSCI_B_I2C_START_INTERRUPT)
    {
    	count_START++;
        /* Change our local state */
        ui8Status = eUSCI_START;
    }

    if (status & EUSCI_B_I2C_STOP_INTERRUPT)
    {
    	count_STOP++;
        /* Change our local state */
        ui8Status = eUSCI_STOP;
    }

    if (status & EUSCI_B_I2C_RECEIVE_INTERRUPT0)
    {
    	count_REC++;
    	/* RX data */
    	*globalData++ = EUSCI_B_I2C_masterReceiveMultiByteNext(EUSCI_B0_BASE);
    	ui8DummyRead= EUSCI_B_I2C_masterReceiveMultiByteNext(EUSCI_B0_BASE);

    	if (burstMode)
    	{
    		g_ui32ByteCount--;
    		if (g_ui32ByteCount == 1)
    		{
    			burstMode = false;

    			/* Generate STOP */
    			EUSCI_B_I2C_masterSendMultiByteStop(EUSCI_B0_BASE);
    		}
    	}
    }

    if (status & EUSCI_B_I2C_TRANSMIT_INTERRUPT0)
    {
    	count_TRANS++;
    	/* Send the next data */
    	EUSCI_B_I2C_masterSendMultiByteNext(EUSCI_B0_BASE, *globalData++);
    }

#ifdef USE_LPM
    MAP_Interrupt_disableSleepOnIsrExit();
#endif
}

