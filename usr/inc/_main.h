#ifndef __MAIN_H
#define __MAIN_H

#ifdef STM32F407xx
#include "stm32f4xx_hal.h"
#endif
#ifdef STM32F743xx
#include "stm32f7xx_hal.h"
#endif
#ifdef STM32H743xx
#include "stm32h7xx_hal.h"
#endif
#include "main.h"

typedef int32_t  s32;
typedef int16_t s16;
typedef int8_t  s8;

typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;

typedef __IO uint32_t  vu32;
typedef __IO uint16_t vu16;
typedef __IO uint8_t  vu8;

extern ADC_HandleTypeDef hadc1;
extern DMA_HandleTypeDef hdma_adc1;
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim8;
extern SRAM_HandleTypeDef hsram1;
extern UART_HandleTypeDef huart1;
extern DMA_HandleTypeDef hdma_memtomem_dma2_stream1;

void mainInitialize();
void mainCycle();

void SWO_Send(uint8_t* buf);
#define DEBUG_SWO

#ifdef DEBUG_SWO
#define DBG_Send(buf) SWO_Send(buf)
#elif DEBUG_UART
#define DBG_Send(buf) HAL_UART_Transmit(&huart1, buf, (uint16_t)strlen(buf), 0xFFFF)
#endif

#endif //__MAIN_H
