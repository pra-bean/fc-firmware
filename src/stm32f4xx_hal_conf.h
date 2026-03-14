#ifndef STM32F4XX_HAL_CONF_H
#define STM32F4XX_HAL_CONF_H

/* Only enable the HAL modules you're actually using */
#define HAL_MODULE_ENABLED
#define HAL_CORTEX_MODULE_ENABLED
#define HAL_RCC_MODULE_ENABLED
#define HAL_GPIO_MODULE_ENABLED
#define HAL_UART_MODULE_ENABLED
#define HAL_SPI_MODULE_ENABLED
#define HAL_TIM_MODULE_ENABLED
#define HAL_DMA_MODULE_ENABLED

/* HSE on STM32F4 Discovery = 8 MHz */
#define HSE_VALUE    8000000U
#define HSI_VALUE    16000000U
#define HSE_STARTUP_TIMEOUT  100U
#define LSE_STARTUP_TIMEOUT  5000U
#define LSE_VALUE    32768U
#define TICK_INT_PRIORITY   0x0FU

#include "stm32f4xx_hal_cortex.h"
#include "stm32f4xx_hal_rcc.h"
#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_uart.h"
#include "stm32f4xx_hal_spi.h"
#include "stm32f4xx_hal_tim.h"
#include "stm32f4xx_hal_dma.h"

#endif /* STM32F4XX_HAL_CONF_H */