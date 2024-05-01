#ifndef FM_GPIO_H
#define FM_GPIO_H



#ifdef __cplusplus
extern "C" {
#endif

#if defined				(	STM32F103_XX	 )
#include 					<stm32f1xx_hal.h>
#endif

#if defined 			(	STM32F411_XX 	)
#include 					<stm32f4xx_hal.h>
#include 					<stm32f411xe.h>
#endif

#define 			GPIO_PIN_DIR_LOW  					(0UL)
#define 			GPIO_PIN_DIR_HIGH					(1UL)


#define 			GPIO_PIN_LEVEL_0					(0UL)
#define 			GPIO_PIN_LEVEL_1					(1UL)
#define 			GPIO_PIN_LEVEL_2					(2UL)
#define 			GPIO_PIN_LEVEL_3					(3UL)

/*
 * viec su dung ham fm_gpio trong du an bam dam co dung dung chan config tren STM32 ung voi tung loai
 * khi dem qua chip khac dam bao du nhu the nao van lap vao duoc neu du chan
 */
typedef enum
{
	FM_GPIO_PIN_SET_LOW 	= GPIO_PIN_DIR_LOW,
	FM_GPIO_PIN_SET_HIGH 	= GPIO_PIN_DIR_HIGH,
	FM_GPIO_PIN_DIR_NOSENSE = GPIO_PIN_LEVEL_3
} FM_Set_Logic_Pin_t;

typedef struct {
	  uint32_t Pin;
	  uint32_t Mode;
	  uint32_t Pull;
	  uint32_t Speed;
	  uint32_t Alternate;
}fm_gpio_port_t;


__STATIC_INLINE void Fm_Gpio_Pin_Unlock	(uint32_t 	Pin_Number, fm_gpio_port_t* fm_port);
__STATIC_INLINE void Fm_Gpio_Pin_Lock	(uint32_t 	Pin_Number, fm_gpio_port_t* fm_port);


__STATIC_INLINE void Fm_GPIO_Pin_Write	(uint32_t 	Pin_Number, GPIO_TypeDef  *GPIOx, \
										fm_gpio_port_t* fm_port);
__STATIC_INLINE void Fm_GPIO_Pin_Clear	(uint32_t 	Pin_Number, GPIO_TypeDef  *GPIOx, \
										fm_gpio_port_t* fm_port);

__STATIC_INLINE void Fm_GPIO_Pin_Read	(uint32_t 	pin_number, GPIO_TypeDef  *GPIOx, \
										fm_gpio_port_t* fm_port);

__STATIC_INLINE void Fm_Gpio_Pin_Writeport(fm_gpio_port_t* fm_port );
__STATIC_INLINE void Fm_Gpio_Pin_Clearport(fm_gpio_port_t* fm_port );

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
