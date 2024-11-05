/*
 * stm32l4xx_gpio_driver.h
 *
 *  Created on: Oct 18, 2024
 *      Author: kunfu
 */

#ifndef INC_STM32L4XX_GPIO_DRIVER_H_
#define INC_STM32L4XX_GPIO_DRIVER_H_
#include "stm32l4xx.h"

typedef struct
{
	uint8_t GPIO_PinNumber;   		/*  GPIO Pin Number 		*/
	uint8_t GPIO_PinMode;			/*  GPIO Mode   			*/
	uint8_t GPIO_PinSpeed;			/*  GPIO Speed				*/
	uint8_t GPIO_PinPuPdControl;	/*  GPIO Output type		*/
	uint8_t GPIO_PinOPType;			/*  GPIO Pullup-Pulldown	*/
	uint8_t GPIO_PinAllFunMode;		/*	GPIO Alt.function Mode	*/

}GPIO_PinConfig_t;


typedef struct
{
	GPIO_RegDef_t *pGPIOx;				/*  these holds the base address of the gpio port to which the pin belongs  */
	GPIO_PinConfig_t GPIO_PinConfig;	/*THESE HOLDS THE PIN CONFIG */
}GPIO_Handel_t;
/*
 * GPIO PIN CONFIG
 */
#define GPIO_PIN_NO_0		0
#define GPIO_PIN_NO_1		1
#define GPIO_PIN_NO_2		2
#define GPIO_PIN_NO_3		3
#define GPIO_PIN_NO_4		4
#define GPIO_PIN_NO_5		5
#define GPIO_PIN_NO_6		6
#define GPIO_PIN_NO_7		7
#define GPIO_PIN_NO_8		8
#define GPIO_PIN_NO_9		9
#define GPIO_PIN_NO_10		10
#define GPIO_PIN_NO_11		11
#define GPIO_PIN_NO_12		12
#define GPIO_PIN_NO_13		13
#define GPIO_PIN_NO_14		14
#define GPIO_PIN_NO_15		15



/*
 * GPIO MODE CONFIG
 */

#define GPIO_MODE_IN		0
#define GPIO_MODE_OUT		1
#define GPIO_MODE_ALTFN		2
#define GPIO_MODE_ANALOG	3

/*
 * INTEREPT MODES
 */

#define GPIO_MODE_IT_FT		4
#define	GPIO_MODE_IT_RT		5
#define GPIO_MODE_IT_RFT	6
/*
 * GPIO OUTPUT TYPE CONFIG
 */


#define GPIO_OP_TYPE_PP		0
#define	GPIO_OP_TYPE_OD		1
/*
 * GPIO SPEED CONFIG
 */


#define GPIO_SPEED_LOW		0
#define GPIO_SPEED_MEDIUM 	1
#define GPIO_SPEED_FAST		2
#define GPIO_SPEED_HIGH		3
/*
 * GPIO PULL UP AND PULL DOWN  CONFIG
 */


#define GPIO_NO_PUPD		0
#define GPIO_PU				1
#define GPIO_PD				2


/*
 * peripheral clock setup
 */

void GPIO_PeriCLockControl(GPIO_RegDef_t *pGPIOx,uint8_t EnorDi);


/*
 * init and deinit
 */
void GPIO_Init(GPIO_Handel_t *pGPIOHandle);
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx);


/*
 * data read and write
 */
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx ,uint8_t PinNumber);
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx );
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx ,uint8_t PinNumber, uint8_t Value);
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx , uint16_t Value);
void GPIO_ToggleOutPin(GPIO_RegDef_t *pGPIOx ,uint8_t PinNumber);
/*
 * IRQ config
 */

void GPIO_IRQInterruptConfig(uint8_t IRQNumber , uint8_t EnorDi);
void GPIO_IRQPriorityConfig(uint8_t IRQPriority);
void GPIO_IRQHandling(uint8_t PinNumber);


#endif /* INC_STM32L4XX_GPIO_DRIVER_H_ */
