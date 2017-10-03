#ifndef DRIVERS_ST7735SD_H_
#define DRIVERS_ST7735SD_H_

#include "driverlib.h"

//****************************************************************************
//
// \brief Provides functions to interface SD card on ST7735
//
// \TODO add read functions
//
//****************************************************************************

//*****************************************************************************
//
// Definitions
//
//*****************************************************************************

#define ST7735SD_PORT_CS GPIO_PORT_P2
#define ST7735SD_PIN_CS GPIO_PIN7
#define ST7735SD_FREQ 1000000

//*****************************************************************************
//
// Prototypes
//
//*****************************************************************************

//! Initialize SPI communication to the SD card breakout on ST7735
void initST7735SD();


/*!
 * Transmit a byte to the ST7735
 *
 * \param[in] p_byte byte to transmit
 *
 * \return true if transmit successful
 *
 * \note this should be called only after calling initST7735SD
 *
 * \TODO change arguments to SPI function calls to match prototype
 */
void transmitByteST7735SD(uint8_t p_byte);


/*!
 * Transmit a byte array to the ST7735
 *
 * \param[in] p_array array to transmit
 * \param[in] p_size size of array to transmit
 *
 * \return true if transmit successful
 *
 * \note this should be called only after calling initST7735SD
 */
void transmitArrayST7735SD(uint8_t* p_array, uint32_t p_size);


#endif // DRIVERS_ST7735SD_H_
