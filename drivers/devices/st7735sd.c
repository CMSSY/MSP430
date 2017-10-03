#include "st7735sd.h"

/*! DriverLib includes */
#include "cs.h"
#include "eusci_a_spi.h"
#include "gpio.h"

/*! Protocol includes */
#include "../protocols/spi.h"


/*! SPI Master Configuration Parameter */
volatile EUSCI_A_SPI_initMasterParam ST7735SD_spiConfig =
{
		EUSCI_A_SPI_CLOCKSOURCE_SMCLK,          						// SMCLK Clock Source
		0,										      					// Wait to setup clock rate
		ST7735SD_FREQ,      						                    // Desired SPI clock of 1MHz
		EUSCI_A_SPI_MSB_FIRST,                                          // MSB First
		EUSCI_A_SPI_PHASE_DATA_CAPTURED_ONFIRST_CHANGED_ON_NEXT,    	// Phase
		EUSCI_A_SPI_CLOCKPOLARITY_INACTIVITY_LOW, 						// High polarity
		EUSCI_A_SPI_3PIN                           						// 3Wire SPI Mode
};


/*! SPI chip select for ST7735SD */
SPI_CS_INFO ST7735SD_csConfig =
{
		ST7735SD_PORT_CS,		// Chip select port
		ST7735SD_PIN_CS			// Chip select pin
};

void initST7735SD()
{
	// set clock rate for SPI master config
	ST7735SD_spiConfig.clockSourceFrequency = CS_getSMCLK();

	/* CS setup. */
    GPIO_setOutputLowOnPin(ST7735SD_PORT_CS, ST7735SD_PIN_CS);
    GPIO_setAsOutputPin(ST7735SD_PORT_CS, ST7735SD_PIN_CS);
}

void transmitByteST7735SD(uint8_t p_byte)
{
	writeSPI(p_byte, p_byte, &ST7735SD_csConfig, &ST7735SD_spiConfig);
}

void transmitArrayST7735SD(uint8_t* p_array, uint32_t p_size)
{
	uint32_t i = 0;
	for (i = 0; i < p_size; i++)
	{
		transmitByteST7735SD(p_array[i]);
	}
}
