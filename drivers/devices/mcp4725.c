#include "mcp4725.h"

/*! DriverLib includes */
#include "cs.h"
#include "eusci_b_i2c.h"
#include "gpio.h"

/*! Protocol includes */
#include "../protocols/i2c.h"


/*! I2C Master Configuration Parameter */
volatile EUSCI_B_I2C_initMasterParam MCP4725_i2cConfig =
{
		EUSCI_B_I2C_CLOCKSOURCE_SMCLK,          						// SMCLK Clock Source
		0,																// Wait to setup clock rate
		EUSCI_B_I2C_SET_DATA_RATE_100KBPS,      						// Desired I2C Clock of 100khz
        0,                                      						// No byte counter threshold
        EUSCI_B_I2C_SEND_STOP_AUTOMATICALLY_ON_BYTECOUNT_THRESHOLD      // Autostop
};

void initMCP4725()
{
	// set clock rate for I2C master config
	MCP4725_i2cConfig.i2cClk = CS_getSMCLK();
}

void transmitByteMCP4725(uint8_t p_byte)
{
	writeI2C(MCP4725_ADDR, p_byte, &p_byte, 1, &MCP4725_i2cConfig);
}

void transmitArrayMCP4725(uint8_t* p_array, uint32_t p_size)
{
	uint32_t i = 0;
	for (i = 0; i < p_size; i++)
	{
		transmitByteMCP4725(p_array[i]);
	}
}
