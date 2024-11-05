#include <stdint.h>
#include <stdio.h>

uint8_t volatile button_press = 0;
uint32_t button_count = 0;
// Declare register addresses
uint32_t *pClkCtrlReg           = (uint32_t*)(0x40021000 + 0x00);   // RCC AHB2 Enable Register (GPIOC)
uint32_t *pClkCtrlRegApb2       = (uint32_t*)(0x40021000 + 0x60);   // RCC APB2 Enable Register (SYSCFG)
uint32_t *pGPIOCModeReg         = (uint32_t*)(0x48000800 + 0x00);   // GPIOC mode register
uint32_t *pGPIOCPullUpReg       = (uint32_t*)(0x48000800 + 0x0C);   // GPIOC Pull-up/Pull-down Register
uint32_t *pEXTIMaskReg          = (uint32_t*)(0x40010400 + 0x00);   // EXTI Interrupt Mask Register
uint32_t *pEXTTIEdgeCtrlReg     = (uint32_t*)(0x40010400 + 0x0C);   // EXTI Falling Trigger Selection Register (for EXTI13)
uint32_t *pSYSCFG_EXTICR4       = (uint32_t*)(0x40010000 + 0x14);   // SYSCFG External Interrupt Configuration Register 4
uint32_t *pNVICIRQEnReg         = (uint32_t*)(0xE000E104);          // NVIC ISER1 (for IRQ 32-63)
uint32_t *pEXTTIPendReg         = (uint32_t*)(0x40010400 + 0x14);   // EXTI Pending Register



int main(void) {
	 *pClkCtrlReg |= (1 << 2);   // GPIOC clock enable

	    // 2. Enable the clock for SYSCFG (APB2 peripheral)
	    *pClkCtrlRegApb2 |= (1 << 0);  // SYSCFG clock enable

	    // 3. Set PC13 as input (reset state is already input, but let's ensure it)
	    *pGPIOCModeReg &= ~(3 << (13 * 2));  // Set PC13 to input mode

	    // 4. Enable internal pull-up for PC13 (prevent floating state)
	    *pGPIOCPullUpReg |= (1 << 13);  // Enable pull-up for PC13

	    // 5. Configure EXTI13 to be triggered by PC13 in SYSCFG_EXTICR4
	    *pSYSCFG_EXTICR4 &= ~(0xF << 4);   // Clear EXTI13 field (bits [7:4])
	    *pSYSCFG_EXTICR4 |= (2 << 4);      // Set PC13 as source for EXTI13 (2 is the code for GPIOC)

	    // 6. Configure EXTI13 for falling edge trigger (button press detection)
	    *pEXTTIEdgeCtrlReg |= (1 << 13);   // Falling edge trigger for EXTI13

	    // 7. Unmask EXTI13 (enable interrupt)
	    *pEXTIMaskReg |= (1 << 13);        // Unmask EXTI13

	    // 8. Enable EXTI15_10_IRQn in NVIC (EXTI13 is handled by EXTI15_10 interrupt)
	    *pNVICIRQEnReg |= (1 << 8);
    while(1) {
        // Disable interrupt temporarily
        *pEXTIMaskReg &= ~(1 << 13);   // Mask EXTI13

        if (button_press) {
            // Debounce delay
            for (uint32_t volatile i = 0; i < 500000 / 2; i++);

            // Increment button press count
            button_count++;
            printf("Button pressed: %lu\n", button_count);  // SWV or debugger required for this

            // Clear the button press flag
            button_press = 0;
        }

        // Re-enable EXTI13
        *pEXTIMaskReg |= (1 << 13);    // Unmask EXTI13
    }
}

// Interrupt service routine for EXTI13 (handled by EXTI15_10 interrupt)
void EXTI15_10_IRQHandler(void) {
    // Confirm the ISR is triggered
    printf("Interrupt Triggered\n");

    // Set the button press flag
    button_press = 1;

    // Clear the pending interrupt for EXTI13
    *pEXTTIPendReg |= (1 << 13);
}
