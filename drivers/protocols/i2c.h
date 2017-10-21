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

#ifndef DRIVERS_I2C_H_
#define DRIVERS_I2C_H_

#include "driverlib.h"

//****************************************************************************
//
// \brief Provides functions to interface I2C device
//
//****************************************************************************

//****************************************************************************
//
// Types
//
//****************************************************************************
typedef enum {
	eUSCI_IDLE = 0,
	eUSCI_SUCCESS = 0,
	eUSCI_BUSY = 1,
	eUSCI_NACK = 2,
	eUSCI_STOP,
	eUSCI_START
} eUSCI_status;

//*****************************************************************************
//
// Definitions
//
//*****************************************************************************

#define I2C_PORT GPIO_PORT_P1
#define I2C_PIN_SDA GPIO_PIN6
#define I2C_PIN_SCL GPIO_PIN7

//*****************************************************************************
//
// Prototypes
//
//*****************************************************************************

/*!
 * Sets up the pins for I2C bus
 */
void initI2C(void);


/*!
 * Write p_data to p_reg of device with I2C address p_addr
 *
 * \param[in] p_addr address of I2C device
 * \param[in] p_reg register address on I2C device
 * \param[in] p_data pointer to data to write to I2C device
 * \param[in] p_byteCount number of bytes to write
 * \param[in] p_params I2C master param to use for communication
 *
 * \return true if data successfully transferred
 *
 */
bool writeI2C(uint8_t p_addr, uint8_t p_reg, uint8_t *p_data,
			  uint8_t p_byteCount, EUSCI_B_I2C_initMasterParam* p_params);


/*!
 * Read p_data from p_reg of device with I2C address p_addr
 *
 * \param[in] p_addr address of I2C device
 * \param[in] p_reg register address on I2C device
 * \param[out] p_data pointer to data read from I2C device
 * \param[out] p_byteCount number of bytes to read
 * \param[in] p_params I2C master param to use for communication
 *
 * \return true if data successfully read
 *
 */
bool readI2C(uint8_t p_addr, uint8_t p_reg, uint8_t *p_data,
			 uint8_t p_byteCount, EUSCI_B_I2C_initMasterParam* p_params);


/*!
 * Read p_data from p_reg of device with I2C address p_addr in burst mode
 *
 * \param[in] p_addr address of I2C device
 * \param[in] p_reg register address on I2C device
 * \parma[out] pointer to data read from I2C device
 * \param[out] p_byteCount number of bytes to read
 * \param[in] p_params I2C master param to use for communication
 *
 * \return true if data successfully read
 *
 */
bool readBurstI2C(uint8_t p_addr, uint8_t p_reg, uint8_t *p_data,
				  uint32_t p_byteCount, EUSCI_B_I2C_initMasterParam* p_params);


#endif /* DRIVERS_I2C_H_ */
