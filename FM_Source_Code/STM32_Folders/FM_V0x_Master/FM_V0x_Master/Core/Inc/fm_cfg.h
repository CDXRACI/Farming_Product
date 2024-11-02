
#ifndef __FM_CFG_H
#define __FM_CFG_H

#ifdef __cplusplsus
extern "C" {
#endif   

#include "stm32f1xx.h"
#include "stm32f1xx_hal.h"
#include <stdio.h>
#include <stdbool.h> 


#define             FM_PUMP_GPIO_Pin                   GPIO_PIN_0
#define             FM_PUMP_GPIO_Port                  GPIOA

#define             FM_STR_GPIO_Pin                    GPIO_PIN_1
#define             FM_STR_GPIO_Port                   GPIOA

#define             FM_LIGHT_GPIO_Pin                  GPIO_PIN_4
#define             FM_LIGHT_GPIO_Port                 GPIOA

#define             FM_LED_STATE_GPIO_Pin              GPIO_PIN_8
#define             FM_LED_STATE_GPIO_Port             GPIOA

#define             FM_BUZZER_GPIO_Pin                 GPIO_PIN_5
#define             FM_BUZZER_GPIO_Port                GPIOA


#define DBG_OUT_RAW(fmt, ...)                           printf(fmt,__VA_ARGS__)
#define DBG_OUT_ERR(fmt, ...)                           printf(fmt,__VA_ARGS__)
#define DBG_OUT(fmt)                                    printf(fmt)


#define FM_FUNC_GPIO_LIGHT_LOW()                       HAL_GPIO_WritePin(GPIOA, FM_LIGHT_GPIO_Pin, GPIO_PIN_SET);
#define FM_FUNC_GPIO_LIGHT_HIGH()                      HAL_GPIO_WritePin(GPIOA, FM_LIGHT_GPIO_Pin, GPIO_PIN_RESET);

#define FM_FUNC_GPIO_STR_LOW()                         HAL_GPIO_WritePin(GPIOA, FM_STR_GPIO_Pin, GPIO_PIN_SET);
#define FM_FUNC_GPIO_STR_HIGH()                        HAL_GPIO_WritePin(GPIOA, FM_STR_GPIO_Pin, GPIO_PIN_RESET);

#define FM_FUNC_GPIO_PUMP_LOW()                        HAL_GPIO_WritePin(GPIOA, FM_PUMP_GPIO_Pin, GPIO_PIN_SET);
#define FM_FUNC_GPIO_PUMP_HIGH()                       HAL_GPIO_WritePin(GPIOA, FM_PUMP_GPIO_Pin, GPIO_PIN_RESET);

#define FM_FUNC_GPIO_BUZZER_LOW()                      HAL_GPIO_WritePin(GPIOA, FM_BUZZER_GPIO_Pin, GPIO_PIN_RESET);
#define FM_FUNC_GPIO_BUZZER_HIGH()                     HAL_GPIO_WritePin(GPIOA, FM_BUZZER_GPIO_Pin, GPIO_PIN_SET);

#define FM_FUNC_GPIO_LED_STATUS_LOW()                  HAL_GPIO_WritePin(GPIOA, FM_LED_STATE_GPIO_Pin, GPIO_PIN_RESET);
#define FM_FUNC_GPIO_LED_STATUS_HIGH()                 HAL_GPIO_WritePin(GPIOA, FM_LED_STATE_GPIO_Pin, GPIO_PIN_SET);
#define FM_FUNC_GPIO_LED_STATUS_TOGG()                 HAL_GPIO_TogglePin(GPIOA, FM_LED_STATE_GPIO_Pin);

#define FUNC_DELAY_MS(ms)                              HAL_Delay(ms)
#define FM_FUNC_DELAY_1S()                             HAL_Delay(1000)
#define FM_FUNC_DELAY_5S()                             HAL_Delay(5000)
#define FM_FUNC_DELAY_10S()                            HAL_Delay(10000)
#define FM_FUNC_DELAY_20S()                            HAL_Delay(20000)
#define FM_FUNC_DELAY_60S()                            HAL_Delay(60000)
#ifdef __cplusplus
}
#endif

#endif /* __FM_RTC_H */