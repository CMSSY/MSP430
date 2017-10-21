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
#define MCP4725_DAC_REG 0x40

//*****************************************************************************
//
// Prototypes
//
//*****************************************************************************

//! Initialize I2C communication to the MCP4725 DAC
void initMCP4725();


/*!
 * Transmit a 12-bit value to the MCP4725
 *
 * \param[in] p_byte byte to transmit
 *
 * \return true if transmit successful
 *
 * \note this should be called only after calling initMCP4725
 *
 */
void transmitValueMCP4725(uint16_t p_byte);


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
void transmitArrayMCP4725(uint16_t* p_array, uint32_t p_size);


#endif // DRIVERS_MCP4725_H_
