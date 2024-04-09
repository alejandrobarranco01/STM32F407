#include <stdint.h>

// Define the base address of RCC (Reset and Clock Control) peripheral and its offset for AHB1 (Advanced High-performance Bus 1)
#define RCC_BASE_ADDRESS 0x40023800
#define RCC_AHB1_OFFSET 0x30

// Define the base address of GPIO (General Purpose Input/Output) port D and its mode and output register offsets
#define GPIOD_BASE_ADDRESS 0x40020C00
#define GPI_PORT_MODE_REGISTER_OFFSET 0x00 // Register used to control mode of GPIO pins
#define GPI_PORT_OUTPUT_DATA_REGISTER_OFFSET 0x14 // Register used to write data to GPIO pins

int main(void) {
	// Pointers to access RCC and GPIOD registers
	uint32_t *pClockControlRegister = (uint32_t*) (RCC_BASE_ADDRESS
			+ RCC_AHB1_OFFSET); // Pointer to RCC register
	uint32_t *pPortDModeReg = (uint32_t*) (GPIOD_BASE_ADDRESS
			+ GPI_PORT_MODE_REGISTER_OFFSET); // Pointer to GPIO port D mode register
	uint32_t *pPortDOutReg = (uint32_t*) (GPIOD_BASE_ADDRESS
			+ GPI_PORT_OUTPUT_DATA_REGISTER_OFFSET); // Pointer to GPIO port D output data register

	// Set the third bit of the RCC_AHB1_OFFSET register to enable clock for GPIOD
	*pClockControlRegister |= (1 << 3);

	// Configure the mode of the IO pin as output
	// Clear the 24th and 25th bit position

	*pPortDModeReg &= ~(3 << 24);
	*pPortDModeReg |= (1 << 24); // Set the pin D12 to general-purpose output mode in the port D mode register


	while (1) {
		// Turn on the 12th bit in the GPIO port output data register to set pin D12 to high
		*pPortDOutReg |= (1 << 12);

		// Delay here
		for (uint32_t i = 0; i < 400000; i++);

		// turn off led
		*pPortDOutReg &= ~(1 << 12);
		for (uint32_t i = 0; i < 400000; i++);
	}
}
