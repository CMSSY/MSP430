/*
 * ECE 511 - Semester Project - People Counter
 */

#include "driverlib.h"

/*! Device includes */
#include "drivers/devices/mcp4725.h"
#include "drivers/devices/st7735sd.h"

/*! Protocol includes */
#include "drivers/protocols/i2c.h"
#include "drivers/protocols/spi.h"
#include "drivers/protocols/uart.h"


/*!
 * Calls the init functions for the different hardware components
 */
void initDevices()
{
    // initialize the MCP4725 for I2C communication
    // initMCP4725();

    // initialize the SD card on the ST7735 SPI communication
    // initST7735SD();
}

/*!
 * Calls the init functions for the different serial protocols
 */
void initSerial()
{
    // initialize the I2C bus
    // initI2C();

    // initialize the SPI bus
    // initSPI();

    // initialize UART communication
    // initUART();
}

void main(void)
{
    // stop watchdog timer
    WDT_A_hold(WDT_A_BASE);

    // initialize serial communication
    initSerial();

    // initialize devices
    initDevices();

    while(1)
    {
    	_no_operation();
    }
}
