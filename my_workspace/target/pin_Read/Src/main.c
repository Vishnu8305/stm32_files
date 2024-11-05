#include <stdint.h>
#include <stdio.h>

int main(void)
{
	uint32_t *PAddress = (uint32_t*)0x4002104C;  // Peripheral address (Clock enable register)
    uint32_t *PMode = (uint32_t*)0x48000000;     // GPIO Mode Register for Port A
    uint32_t *PIn = (uint32_t*)0x48000010;       // GPIO Input Data Register for Port A
    uint32_t *POut = (uint32_t*)0x48000014;

    // Enable clock for GPIO port A
    *PAddress |= (1 << 0);  // Enable GPIOA clock (assuming bit 0 is for GPIOA)

    // Configure PA0 as input
    *PMode &= ~(3 << 0);    // Clear mode bits for PA0 (two bits per pin, setting 00 for input mode)
    *PMode &= ~(3 << 2);
    *PMode |= (1 << 2);



    *POut &= ~(1 << 1);

    while (1)
    {
        uint8_t current_state = (uint8_t)(*PIn & 0x1);  // Read PA0 state

        // Detect rising edge: button press (from 0 to 1)
        if (current_state == 0)
        {
        	*POut |= (1 << 1);
        }

        else{
        	*POut &= ~(1 << 1);
        }
    }

    return 0;
}
