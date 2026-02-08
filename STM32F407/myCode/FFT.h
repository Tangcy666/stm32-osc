#ifndef FFT_H
#define FFT_H
#include "arm_math.h"
#include "arm_const_structs.h"
#include "config.h"
#include "ADC_DMA.h"

#define FFT_LENGTH 1024 // FFT点数，必须是2的幂
// #define SAMPLE_FREQ 10000 // 你的采样频率，例如10kHz

extern arm_rfft_fast_instance_f32 fftInstance; // FFT实例
extern float32_t fftinput[FFT_LENGTH];
extern float32_t fftoutput[FFT_LENGTH * 2];
extern float32_t output[FFT_LENGTH / 2 + 1];

void FFT_Init(void);
void FFT_Process(float32_t *fftinput, float32_t *output);

uint32_t FFT_App(float *Freq);

#endif // FFT_H