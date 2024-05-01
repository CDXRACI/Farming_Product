#define STM32F411_XX 			(0UL)
#include"../Inc/fm_gpio.h"

__STATIC_INLINE void Fm_GPIO_Pin_Write	(uint32_t Pin_Number, GPIO_TypeDef  *GPIOx, \
										fm_gpio_port_t* fm_port)
{
	if( Pin_Number < 0 && Pin_Number > 16 != 0 ){
		return 0;
	}
	HAL_GPIO_WritePin(GPIOx, Pin_Number, GPIO_PIN_DIR_HIGH);
}


__STATIC_INLINE void Fm_GPIO_Pin_Clear	(uint32_t Pin_Number, GPIO_TypeDef  *GPIOx, \
										fm_gpio_port_t* fm_port)
{
	if( Pin_Number < 0 && Pin_Number > 16 != 0 ){
		return 0;
	}
	HAL_GPIO_WritePin(GPIOx, Pin_Number, GPIO_PIN_DIR_LOW);
}



/*
 * fm_gpio.c
 *
 *  Created on: Apr 29, 2024
 *      Author: CDP.Darkness
 */


