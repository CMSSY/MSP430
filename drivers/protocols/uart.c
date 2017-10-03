#include "uart.h"

/* DriverLib Includes */
#include "driverlib.h"

void initUART()
{
    /* Select UART function for P3.2(RX) and P3.3(TX) */
	GPIO_setAsPeripheralModuleFunctionOutputPin(UART_PORT,
			UART_PIN_TX | UART_PIN_RX, GPIO_PRIMARY_MODULE_FUNCTION);
}

bool writeUART(uint8_t p_data, uint32_t p_length, EUSCI_A_UART_initParam* p_config)
{
    /* Configuring UART Module */
//    EUSCI_A_UART_init(EUSCI_A1_BASE, &p_config);

    /* Enable UART module */
//    EUSCI_A_UART_enable(EUSCI_A1_BASE);

	(void) p_length;
	uint_fast8_t byteToTransmit = p_data;

	while (!(UCA1IFG & UCTXIFG));
	EUSCI_A_UART_transmitData(EUSCI_A1_BASE, byteToTransmit);
	EUSCI_A_UART_clearInterrupt(EUSCI_A1_BASE, EUSCI_A_UART_TRANSMIT_INTERRUPT_FLAG);

	return true;
}


bool readUART(uint8_t* p_data, uint32_t p_length, EUSCI_A_UART_initParam* p_config)
{
    /* Configuring UART Module */
//    EUSCI_A_UART_init(EUSCI_A1_BASE, &p_config);

    /* Enable UART module */
//    EUSCI_A_UART_enable(EUSCI_A1_BASE);

	return false;
}
