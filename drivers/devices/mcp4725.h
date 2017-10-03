#ifndef DRIVERS_MCP4725_H_
#define DRIVERS_MCP4725_H_

#include "driverlib.h"

//****************************************************************************
//
// \brief Provides functions to interface MCP4725 DAC
//
//****************************************************************************

//*****************************************************************************
//
// Definitions
//
//*****************************************************************************

#define MCP4725_ADDR 0x60

//*****************************************************************************
//
// Prototypes
//
//*****************************************************************************

//! Initialize I2C communication to the MCP4725 DAC
void initMCP4725();


/*!
 * Transmit a byte to the MCP4725
 *
 * \param[in] p_byte byte to transmit
 *
 * \return true if transmit successful
 *
 * \note this should be called only after calling initMCP4725
 *
 * \TODO change arguments to I2C function calls to match prototype
 */
void transmitByteMCP4725(uint8_t p_byte);


/*!
 * Transmit a byte array to the MCP4725
 *
 * \param[in] p_array array to transmit
 * \param[in] p_size size of array to transmit
 *
 * \return true if transmit successful
 *
 * \note this should be called only after calling initMCP4725
 */
void transmitArrayMCP4725(uint8_t* p_array, uint32_t p_size);


#endif // DRIVERS_MCP4725_H_
