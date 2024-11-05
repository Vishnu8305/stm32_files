#include <stdint.h>

int main(void)
{
    // 1. Enable clock for GPIOA by writing to RCC_AHB2ENR
    uint32_t *pClkCtrlReg = (uint32_t*)0x4002104C;    // Address of RCC AHB2ENR
    *pClkCtrlReg |= (1 << 0);                         // Set bit 0 to enable GPIOA clock

    // 2. Set GPIOA Pin 1 (PA1) as output
    uint32_t *pPortAModeReg = (uint32_t*)0x48000000;  // Address of GPIOA MODER
    *pPortAModeReg &= ~(3 << 30);                      // Clear mode bits 2 and 3 for PA1
    *pPortAModeReg &= ~(3 << 0);
    *pPortAModeReg |= (1 << 30);                       // Set PA1 to output mode (01)
    *pPortAModeReg |= (1 << 0);
    // 3. Set PA1 (connected to the LED) to high
    uint32_t *pPortAOutReg = (uint32_t*)0x48000014;   // Address of GPIOA ODR
    *pPortAOutReg |= (1 << 15);                        // Set bit 1 to turn on the LED (PA1 high)
    *pPortAOutReg |= (1 << 0);
    while(1);  // Infinite loop to keep the LED on
}






