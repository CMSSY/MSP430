/*
 * Copyright (C) 2014 Texas Instruments Incorporated - http://www.ti.com/
 *
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
*/

#ifndef DRIVERS_SPI_H_
#define DRIVERS_SPI_H_

#include "driverlib.h"

//****************************************************************************
//
// \brief Provides functions to interface SPI device
//
//****************************************************************************

//****************************************************************************
//
// Types
//
//****************************************************************************

/*!
 * \brief Used in the writeSPI() and readSPI() functions to select/deselect device
 */
typedef struct SPI_CS_INFO
{
    //! Port for the CS select pin
    uint8_t m_port;
    //! Pin for CS
    uint8_t m_pin;
} SPI_CS_INFO;


//*****************************************************************************
//
// Definitions
//
//*****************************************************************************

#define SPI_PORT GPIO_PORT_P2
#define SPI_PIN_SIMO GPIO_PIN0
#define SPI_PIN_SOMI GPIO_PIN1
#define SPI_PIN_SCK GPIO_PIN2

//*****************************************************************************
//
// Prototypes
//
//*****************************************************************************

/*!
 * Sets up the pins for SPI bus
 */
void initSPI(void);


/*!
 * Write p_data to register p_addr of device specified by p_csInfo
 *
 * \param[in] p_csInfo Port and Pin for CS
 * \param[in] p_reg register address on SPI device to write to
 * \param[in] p_data data to write to register p_reg on SPI device
 *
 * \return true if data successfully written
 *
 * \TODO setup and enable SPI given p_config
 */
bool writeSPI(uint8_t p_reg, uint8_t p_data, SPI_CS_INFO* p_csInfo,
			  EUSCI_A_SPI_initMasterParam* p_config);

/*!
 * Read p_data from p_reg of device specified by p_csInfo
 *
 * \param[in] p_csInfo Port and Pin for CS
 * \param[in] p_reg register address on SPI device
 * \param[in] p_data pointer to data read from SPI device
 * \param[in] p_length length of data to read from SPI device
 *
 * \return true if data successfully read
 *
 * \TODO setup and enable SPI given p_config
 */
bool readSPI(uint8_t p_reg, uint8_t* p_data, uint32_t p_length, SPI_CS_INFO* p_csInfo,
		  	 EUSCI_A_SPI_initMasterParam* p_config);

#endif
