#ifndef DRIVERS_UART_H_
#define DRIVERS_UART_H_

#include "driverlib.h"

//****************************************************************************
//
// \brief Provides functions to interface UART device
//
//****************************************************************************

//*****************************************************************************
//
// Definitions
//
//*****************************************************************************

//! These pins are connected to LCD on MSP430FR6989 Launchpad, will need to change
#define UART_PORT GPIO_PORT_P3
#define UART_PIN_TX GPIO_PIN4
#define UART_PIN_RX GPIO_PIN5

//*****************************************************************************
//
// Prototypes
//
//*****************************************************************************

/*!
 * Sets up the pins for UART communication
 *
 * \TODO setup a clock (or timer) to get baud rate generation correct
 */
void initUART();

/*!
 * Write p_data to UART device
 *
 * \param[in] p_data data to write to UART device
 * \param[in] p_length length of data to write to UART device
 *
 * \return true if data successfully written
 *
 * \TODO change to use interrupts
 * \TODO add ability to write data of variable length
 * \TODO add code to init, enable UART based on p_config param
 */
bool writeUART(uint8_t p_data, uint32_t p_length, EUSCI_A_UART_initParam* p_config);


/*!
 * Read p_data from UART device
 *
 * \param[out] p_data pointer to data read from UART device
 * \param[out] p_length length of data to read
 *
 * \return true if data successfully read
 *
 * \TODO implement this function
 */
bool readUART(uint8_t* p_data, uint32_t p_length, EUSCI_A_UART_initParam* p_config);


#endif /* DRIVERS_UART_H_ */
