#include <stdint.h>

#define RCC_AHB1_BA 0x40023800 // Base address for the Reset and Clock Control (RCC) Peripheral's AHB1
#define RCC_AHB1ENR_OS 0x30 // Offset for the RCC AHB1 enable register within the RCC peripheral (we need to set 3rd bit to 1 to enable IO Port D)

#define GPIOD_AHB1_BA 0x40020C00 // Base address for the General-Purpose Input/Output (GPIO) Port D Peripheral's AHB1
#define GPIOx_MODER_OS 0x00 // Offset for the GPIO port mode register within the GPIO peripheral (we need to set 24 and 25th bits to 01)

#define GPIOx_ODR 0x14 // Offset for the GPIO port output data register within the GPIO peripheral (we need to set 12th bit to 1 for green LED)

#define GPIOA_AHB1_BA 0x40020000 // Base address for the General-Purpose Input/Output (GPIO) Port D Peripheral's AHB1
#define GPIOx_IDR 0x10 // Offset for the GPIO port input data register within the GPIO peripheral (we need to read from 0th bit)

int main(void) {

	uint32_t* pRCC_AHB1_ENABLE_REGISTER = (uint32_t*) (RCC_AHB1_BA + RCC_AHB1ENR_OS); // RCC enables the clock for the AHB1 bus
	uint32_t* pGPIOD_PORT_MODE_REGISTER = (uint32_t*) (GPIOD_AHB1_BA + GPIOx_MODER_OS); // Points to the GPIO Port D mode register
	uint32_t* pGPIOD_PORT_OUTPUT_DATA_REGISTER = (uint32_t*) (GPIOD_AHB1_BA + GPIOx_ODR); // Points to the GPIO Port D output data register

	uint32_t* pGPIOA_PORT_MODE_REGISTER = (uint32_t*) (GPIOA_AHB1_BA + GPIOx_MODER_OS); // Points to the GPIO Port A mode register
	uint32_t* pGPIOA_PORT_INPUT_DATA_REGISTER = (uint32_t*) (GPIOA_AHB1_BA + GPIOx_IDR); // Points to the GPIO Port A input data register


	*pRCC_AHB1_ENABLE_REGISTER |= (1 << 3); // Set 3rd bit to 1 to enable clock for IO Port D
	*pRCC_AHB1_ENABLE_REGISTER |= (1 << 0); // Set 3rd bit to 1 to enable clock for IO Port A

	// 3 in binary is 11 so this clears 24th and 25th bits, and then set 24th bit to 1
	*pGPIOD_PORT_MODE_REGISTER = (*pGPIOD_PORT_MODE_REGISTER & ~(3 << 24)) | (1 << 24); // Set to 01 for General purpose output mode

	// 3 in binary 11 11 so this clears 0th and 1st bits)
	*pGPIOA_PORT_MODE_REGISTER &= ~(3 << 0); // Set to 00 for Input mode

	while(1) {
		// Read the pin status (first bit) (this clears the rest of the bits [1:7])
		uint8_t pinStatus = (uint8_t)(*pGPIOA_PORT_INPUT_DATA_REGISTER & 0x01);

		// If it's a 1, then turn on the LED
		if (pinStatus) {
			*pGPIOD_PORT_OUTPUT_DATA_REGISTER |= (1 << 12); // Set 12th bit to 1 to turn on the green LED
		} else {
			*pGPIOD_PORT_OUTPUT_DATA_REGISTER &= ~(1 << 12); // Clear 12th bit to 0 to turn off the green LED
		}
	}
}
