#include <_main.h>
#include "generator.h"

uint32_t tim1Prescaler = 107;
uint32_t tim1Period = 99;
uint32_t tim1Pulse = 30;

void GEN_step(int16_t step) {
    GEN_setParams();
}

void GEN_setFreq() {
    GEN_setParams();
}

void GEN_setParams() {
    TIM_OC_InitTypeDef sConfigOC;

    htim1.Instance = TIM1;
    htim1.Init.Prescaler = tim1Prescaler;
    htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim1.Init.Period = tim1Period;
    htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim1.Init.RepetitionCounter = 0;
//    htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
    if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
        Error_Handler();

    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = tim1Pulse;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
    sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
    if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
        Error_Handler();
}
