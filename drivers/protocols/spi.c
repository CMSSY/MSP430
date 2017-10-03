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

#include "spi.h"

/*!
 * Sets the chip select pin to high
 */
void assertCS(SPI_CS_INFO* p_csInfo)
{
	p_csInfo->m_port &= ~p_csInfo->m_pin;
}


/*!
 * Sets the chip select pin to low
 */
void deassertCS(SPI_CS_INFO* p_csInfo)
{
	p_csInfo->m_port |= p_csInfo->m_pin;
}

void spi_init(void)
{
    /* Selecting P2.2(SCK) P2.0(SIMO) and P2.1(SOMI) in SPI mode */
	GPIO_setAsPeripheralModuleFunctionInputPin(SPI_PORT,
			SPI_PIN_SIMO | SPI_PIN_SOMI | SPI_PIN_SCK, GPIO_PRIMARY_MODULE_FUNCTION);
}

bool writeSPI(uint8_t p_reg, uint8_t p_data, SPI_CS_INFO* p_csInfo,
			  EUSCI_A_SPI_initMasterParam* p_config)
{
    /* Configuring SPI in 3wire master mode */
	//EUSCI_A_SPI_initMaster(EUSCI_A0_BASE, (const EUSCI_A_SPI_initMasterParam *)&p_config);

	/* Enable SPI module */
	//EUSCI_A_SPI_enable(EUSCI_A0_BASE);

    assertCS(p_csInfo);

    while (!(UCA0IFG & UCTXIFG));
	UCB0TXBUF = p_reg;
	while (!(UCA0IFG & UCRXIFG));
	UCB0RXBUF;

	while (!(UCA0IFG & UCTXIFG));
	UCB0TXBUF = p_data;
	while (!(UCA0IFG & UCRXIFG));
	UCB0RXBUF;

    deassertCS(p_csInfo);

    return true;
}

bool readSPI(uint8_t p_reg, uint8_t* p_data, uint32_t p_length, SPI_CS_INFO* p_csInfo,
		  	 EUSCI_A_SPI_initMasterParam* p_config)
{
    /* Configuring SPI in 3wire master mode */
	//EUSCI_A_SPI_initMaster(EUSCI_A0_BASE, (const EUSCI_A_SPI_initMasterParam *)&p_config);

	/* Enable SPI module */
	//EUSCI_A_SPI_enable(EUSCI_A0_BASE);

    int i = 0;

    assertCS(p_csInfo);

    for (i = 0; i < p_length; i ++)
    {
        while (!(UCA0IFG & UCTXIFG));
        if(i >= 1) UCA0TXBUF = 0x00;	// send dummy byte if greater than 1
        else UCA0TXBUF = p_reg;	// send address if this is the first send
        while (!(UCA0IFG & UCRXIFG));
        if(i >= 1) p_data[i - 1] = UCA0RXBUF;	// store data if the address has already been sent
        else UCA0RXBUF;	// dont care about first byte sent from camera
    }

    deassertCS(p_csInfo);

    return true;
}


