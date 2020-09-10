#include "stm32f4xx.h"



void delay (int a)
{
    volatile int i,j;

    for (i=0 ; i < a ; i++)
    {
        j++;
    }

    return;
}


int main()
{
	int time = 1000000;
	int i=0;
RCC->AHB1ENR|=RCC_AHB1ENR_GPIODEN; //Enable GPIOD
RCC -> APB1ENR |= RCC_APB1ENR_TIM4EN; //Enable TIM4  


GPIOD -> MODER = (0b10 << 24);                          // PWM output on PD12
GPIOD -> OSPEEDR = (0xFF000000 << 24);                  // High Speed on PD12
GPIOD -> AFR[1] |= (0x2 << 16);                         // AFRH12[3:0] selected AF2(TIM3..5)


TIM4 -> CCMR1 |= (0x7 << 5) | (0x1 << 3);               // PWM Mode 2, channel 1 output compare preload enabled
TIM4 -> CCR1 = 0x0012;                                  // 1.2% duty cycle
TIM4 -> PSC = 0x0000;                                   // No pre-scaler
TIM4 -> ARR = 0x1000;                                   // Reload at 0x1000
TIM4->CCER |= TIM_CCER_CC1E;                          // Enable CH1 output
TIM4->CR1 |= (0x2 << 8) | TIM_CR1_ARPE | TIM_CR1_CEN; // Divide clock by 4, auto-reload, and start timer

while(1)
{
	i++;
	if (i==1) { TIM4 -> CCR1 = 0x0012; delay(time); }
	if (i==2) { TIM4 -> CCR1 = 0x0025; delay(time); }
	if (i==3) { TIM4 -> CCR1 = 0x0121; delay(time); }
	if (i==4) { TIM4 -> CCR1 = 0x0901; delay(time); }
	if (i==5) { TIM4 -> CCR1 = 0x0121; delay(time); }
	if (i==6) { TIM4 -> CCR1 = 0x0025; i=0; delay(time); }
}

return(1);
}
