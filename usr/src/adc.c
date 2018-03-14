#include <_main.h>
#include <dwt.h>
#include <graph.h>
#include <DataBuffer.h>
#include "adc.h"


struct ADC_param {
    uint32_t ADC_Prescaler;
    uint32_t ADC_SampleTime;
    float SampleTime;    // microseconds
    float ScreenTime;    // microseconds
};
typedef struct ADC_param ADC_PARAM;

#define GEN_Parameters_Size 31
const ADC_PARAM ADC_Parameters[GEN_Parameters_Size] = {
        {ADC_CLOCK_SYNC_PCLK_DIV2, ADC_SAMPLETIME_3CYCLES,   0.2619048f,  83.80952f},
        {ADC_CLOCK_SYNC_PCLK_DIV4, ADC_SAMPLETIME_3CYCLES,   0.5238095f,  167.61905f},
        {ADC_CLOCK_SYNC_PCLK_DIV2, ADC_SAMPLETIME_15CYCLES,  0.5476190f,  175.23810f},
        {ADC_CLOCK_SYNC_PCLK_DIV6, ADC_SAMPLETIME_3CYCLES,   0.7857143f,  251.42857f},
        {ADC_CLOCK_SYNC_PCLK_DIV2, ADC_SAMPLETIME_28CYCLES,  0.8571429f,  274.28571f},
        {ADC_CLOCK_SYNC_PCLK_DIV8, ADC_SAMPLETIME_3CYCLES,   1.0476190f,  335.23810f},
        {ADC_CLOCK_SYNC_PCLK_DIV4, ADC_SAMPLETIME_15CYCLES,  1.0952381f,  350.47619f},
        {ADC_CLOCK_SYNC_PCLK_DIV2, ADC_SAMPLETIME_56CYCLES,  1.5238095f,  487.61905f},
        {ADC_CLOCK_SYNC_PCLK_DIV6, ADC_SAMPLETIME_15CYCLES,  1.6428571f,  525.71429f},
        {ADC_CLOCK_SYNC_PCLK_DIV4, ADC_SAMPLETIME_28CYCLES,  1.7142857f,  548.57143f},
        {ADC_CLOCK_SYNC_PCLK_DIV2, ADC_SAMPLETIME_84CYCLES,  2.1904762f,  700.95238f},
        {ADC_CLOCK_SYNC_PCLK_DIV6, ADC_SAMPLETIME_28CYCLES,  2.5714286f,  822.85714f},
        {ADC_CLOCK_SYNC_PCLK_DIV2, ADC_SAMPLETIME_112CYCLES, 2.8571429f,  914.28571f},
        {ADC_CLOCK_SYNC_PCLK_DIV4, ADC_SAMPLETIME_56CYCLES,  3.0476190f,  975.23810f},
        {ADC_CLOCK_SYNC_PCLK_DIV8, ADC_SAMPLETIME_28CYCLES,  3.4285714f,  1097.14286f},
        {ADC_CLOCK_SYNC_PCLK_DIV2, ADC_SAMPLETIME_144CYCLES, 3.6190476f,  1158.09524f},
        {ADC_CLOCK_SYNC_PCLK_DIV4, ADC_SAMPLETIME_84CYCLES,  4.3809524f,  1401.90476f},
        {ADC_CLOCK_SYNC_PCLK_DIV6, ADC_SAMPLETIME_56CYCLES,  4.5714286f,  1462.85714f},
        {ADC_CLOCK_SYNC_PCLK_DIV4, ADC_SAMPLETIME_112CYCLES, 5.7142857f,  1828.57143f},
        {ADC_CLOCK_SYNC_PCLK_DIV8, ADC_SAMPLETIME_56CYCLES,  6.0952381f,  1950.47619f},
        {ADC_CLOCK_SYNC_PCLK_DIV6, ADC_SAMPLETIME_84CYCLES,  6.5714286f,  2102.85714f},
        {ADC_CLOCK_SYNC_PCLK_DIV4, ADC_SAMPLETIME_144CYCLES, 7.2380952f,  2316.19048f},
        {ADC_CLOCK_SYNC_PCLK_DIV6, ADC_SAMPLETIME_112CYCLES, 8.5714286f,  2742.85714f},
        {ADC_CLOCK_SYNC_PCLK_DIV8, ADC_SAMPLETIME_84CYCLES,  8.7619048f,  2803.80952f},
        {ADC_CLOCK_SYNC_PCLK_DIV6, ADC_SAMPLETIME_144CYCLES, 10.8571429f, 3474.28571f},
        {ADC_CLOCK_SYNC_PCLK_DIV8, ADC_SAMPLETIME_112CYCLES, 11.4285714f, 3657.14286f},
        {ADC_CLOCK_SYNC_PCLK_DIV2, ADC_SAMPLETIME_480CYCLES, 11.6190476f, 3718.09524f},
        {ADC_CLOCK_SYNC_PCLK_DIV8, ADC_SAMPLETIME_144CYCLES, 14.4761905f, 4632.38095f},
        {ADC_CLOCK_SYNC_PCLK_DIV4, ADC_SAMPLETIME_480CYCLES, 23.2380952f, 7436.19048f},
        {ADC_CLOCK_SYNC_PCLK_DIV6, ADC_SAMPLETIME_480CYCLES, 34.8571429f, 11154.28571f},
        {ADC_CLOCK_SYNC_PCLK_DIV8, ADC_SAMPLETIME_480CYCLES, 46.4761905f, 14872.380951f}
};

uint32_t ADC_Prescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
uint32_t ADC_SampleTime = ADC_SAMPLETIME_3CYCLES;

uint16_t ScreenTime = 0;      // index in ScreenTimes
uint16_t ScreenTime_adj = 0;  // 0-9 shift in ScreenTime
const float ScreenTimes[] = {100, 200, 500, 1000, 2000, 5000, 10000, 20000};  // sweep screen, microseconds

uint32_t ADCStartTick;         // time when start ADC buffer fill
uint32_t ADCHalfElapsedTick;   // the last time half buffer fill
uint32_t ADCElapsedTick;       // the last time buffer fill

/**
 * Copy of MX_ADC1_Init()
 */
void ADC_setParams() {

    ADC_ChannelConfTypeDef sConfig;

    /**Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
    */
    hadc1.Instance = ADC1;
    hadc1.Init.ClockPrescaler = ADC_Prescaler;
    hadc1.Init.Resolution = ADC_RESOLUTION_8B;
    hadc1.Init.ScanConvMode = ENABLE;
    hadc1.Init.ContinuousConvMode = ENABLE;
    hadc1.Init.DiscontinuousConvMode = DISABLE;
    hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
    hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
    hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    hadc1.Init.NbrOfConversion = 1;
    hadc1.Init.DMAContinuousRequests = ENABLE;
    hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
    if (HAL_ADC_Init(&hadc1) != HAL_OK)
        Error_Handler();

    /**Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
    */
    sConfig.Channel = ADC_CHANNEL_3;
    sConfig.Rank = 1;
    sConfig.SamplingTime = ADC_SampleTime;
    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
        Error_Handler();

    HAL_ADC_Start_DMA(&hadc1, (uint32_t *) samplesBuffer, BUF_SIZE);

    ADCStartTick = DWT_Get_Current_Tick();
}


void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc) {
    firstHalf = 0;
}


void HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef *hadc) {
    firstHalf = 1;
}


void ADC_step_up() {
    if (ScreenTime_adj < 9)
        ScreenTime_adj++;
    else if (ScreenTime < sizeof(ScreenTimes) / sizeof(ScreenTimes[0]) - 2) // last value forbidden to assign
        ScreenTime_adj = 0, ScreenTime++;
}


void ADC_step_down() {
    if (ScreenTime_adj > 0)
        ScreenTime_adj--;
    else if (ScreenTime > 0)
        ScreenTime_adj = 9, ScreenTime--;
}


float ADC_getTime() {
    float time = ScreenTimes[ScreenTime];
    // next time always exist because last forbidden to assign
    float adj = (ScreenTimes[ScreenTime + 1] - time) * ScreenTime_adj / 10;
    time += adj;
    return time;
}

s16 sStep;
float time;
int ii;

void ADC_step(int16_t step) {
    if (step == 0) return;
    if (step > 0) ADC_step_up();
    else ADC_step_down();
    sStep = step;

    time = ADC_getTime(); // get screen sweep time

    // looking last parameters set with ScreenTime less than required time
    int i = 1;
    while (ADC_Parameters[i].ScreenTime < time) {
        i++;
        if (i >= GEN_Parameters_Size) break;
    }

    i--;
    ii = i;
    ADC_Prescaler = ADC_Parameters[i].ADC_Prescaler;
    ADC_SampleTime = ADC_Parameters[i].ADC_SampleTime;

    // set X scale
    scaleX = ADC_Parameters[i].ScreenTime / time;

    ADC_setParams();
}

/*uint16_t ICount = 0;

// dma2 stream 0 irq handler
void DMA2_Stream0_IRQHandler() {
    ICount++;
    // Test on DMA Stream HalfTransfer Complete interrupt
    if (DMA_GetITStatus(DMA2_Stream0, DMA_IT_HTIF0)) {
        // Clear Stream0 HalfTransfer
        DMA_ClearITPendingBit(DMA2_Stream0, DMA_IT_HTIF0);

        // count time for half circle
        ADCHalfElapsedTick = DWT_Elapsed_Tick(ADCStartTick);
        half = 0;
    }

    // Test on DMA Stream Transfer Complete interrupt
    if (DMA_GetITStatus(DMA2_Stream0, DMA_IT_TCIF0)) {
        // Clear Stream0 Transfer Complete
        DMA_ClearITPendingBit(DMA2_Stream0, DMA_IT_TCIF0);

        // count time for one circle
        ADCElapsedTick = DWT_Elapsed_Tick(ADCStartTick);
        ADCStartTick = DWT_Get_Current_Tick();
        half = 1;
    }
} //*/
