#ifndef FM_GPIO_H
#define FM_GPIO_H

#include <stm32f1xx_hal.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined			(STM32F103_XX )
#endif

#if defined 			(STM32F407G_XX)
#endif

#define 			GPIO_PIN_DIR_INPUT  				(0UL)
#define 			GPIO_PIN_DIR_OUTPUT					(1UL)

/*
 * viec su dung ham fm_gpio trong du an bam dam co dung dung chan config tren STM32 ung voi tung loai
 * khi dem qua chip khac dam bao du nhu the nao van lap vao duoc neu du chan
 */
typedef enum
{
	FM_GPIO_PIN_DIR_INPUT 	= GPIO_PIN_DIR_INPUT,
	FM_GPIO_PIN_DIR_OUTPUT 	= GPIO_PIN_DIR_OUTPUT
}; fm_gpio_pin_dir_t;


#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
