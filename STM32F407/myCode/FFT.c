#include "FFT.h"
arm_rfft_fast_instance_f32 fftInstance; // FFT实例
float32_t fftinput[FFT_LENGTH];         // FFT输入数组
float32_t fftoutput[FFT_LENGTH * 2];    // FFT输出数组
float32_t output[FFT_LENGTH / 2 + 1];   // 输出数组
extern uint32_t *adc_value_buffer_u32;
extern uint32_t adc_value_u32[];

void FFT_Init(void)
{
  // 初始化实数FFT
  arm_rfft_fast_init_f32(&fftInstance, FFT_LENGTH);
}

void FFT_Process(float32_t *fftinput, float32_t *output)
{
  // 执行实数FFT
  arm_rfft_fast_f32(&fftInstance, fftinput, fftoutput, 0);
  arm_cmplx_mag_f32(fftoutput, output, FFT_LENGTH / 2 + 1);
}
/**
 * @brief  FFT
 * @param  Freq 频率
 * @retval 0 成功, 1 失败
 */
uint32_t FFT_App(float *Freq)
{
  float max = 0;
  uint32_t index = 0;
  if (OSC_Config.OSC_Fs == 7200000)
  {
    for (uint16_t i = 0; i < FFT_LENGTH; i++)
    {
      fftinput[i] = (float)adc_value_u32[i];
    }
  }
  else
  {
    for (uint16_t i = 0; i < FFT_LENGTH; i++)
    {
      fftinput[i] = (float)adc_value_buffer_u32[i];
    }
  }
  FFT_Process(fftinput, output);
  output[0] = 0;
  arm_max_f32(output, FFT_LENGTH / 2 + 1, &max, &index);
  *Freq = index * ((float)OSC_Config.OSC_Fs / (FFT_LENGTH));
  return 0;
}
