# PWM

Este módulo assume que a configuração de clock está definida para utilizar o DCO (***Digital Controlled Oscillator***) em 24 MHz.



Este trecho de código determina a frequência do PWM, utilizando como fonte de clock (SMCLK/8). Note que o duty cycle será determinado por ***dt/PWM_PERIOD***.

```C
// Para frequência de 1kHz	PWM_PERIOD = (SMCLK/8)-1
#define PWM_PERIOD			3000-1

/**
 * @brief Seta o duty cycle do PWM
 * @param channel: Canal do PWM
 * @param dt: duty cycle
 */
void set_pwm_dt(pwm_channel_t channel, uint16_t dt);
```

<img src="/home/guilherme/Documentos/IFSC/Microcontroladores/pwm/TEK0000.JPG" alt="TEK0000" style="zoom: 67%;" />