#include "stm32f10x.h"                  // Device header
#include "stm32f10x_tim.h"              // Keil::Device:StdPeriph Drivers:TIM

#define timeDelay 500		//  10 <=> 1ms

uint16_t arr[18] = {999};		// thoi gian pha cao trong 1 chu ki ( f=1khz, T = 1ms)
uint8_t flag[18] = {1};		// cho phep led sang
uint8_t i, k;
int8_t j;

void configGPIO()	//A0->11	B01-56-89
{
	RCC->APB2ENR |= (3 << 2);		// ENABLE PORT A & B
	/* config port A */
	GPIOA->CRL   &= 0x00000000;
	GPIOA->CRL   |= 0x33333333;
	GPIOA->CRH	 &= 0xffff0000;
	GPIOA->CRH	 |= 0x00003333;
	
	/* config port B */
	GPIOB->CRL   &= 0xf00fff00;
	GPIOB->CRL   |= 0x03300033;
	GPIOB->CRH   &= 0xffffff00;
	GPIOB->CRH   |= 0x00000033;
	
}

void configTIM()	
{
	/* Config TIM2 */
	RCC->APB1ENR |= 0x01;		// kich hoat TIM2
	TIM2->ARR = 200-1;		// moi chu ki chia lam 200 buoc ( 75% thi 200*0.75 = 150 buoc HIGH, 200*0.25=50 buoc LOW) // f = 72Mhz / 72 (PSC) / 200 (buoc) = 5 KHz // chu ki T = 1 / 5 KHz = 0.2 ms
	TIM2->PSC = 72-1;		// chia tan 72Mhz -> 1Mhz
	TIM2->CR1 = 0x01;		// kich hoat bo dem, dem len
	TIM2->EGR = 0x01;		// su kien reload
	
	/* config TIM 3 */  
	RCC->APB1ENR |= (1 << 1);		// kich hoat TIM2
	TIM3->ARR = 0xFFFF;		// gia tri dem tran
	TIM3->PSC = 7200 - 1;		// chia tan 72MHz -> 10Khz
	TIM3->CR1 = 0x01;		// kich hoat bo dem, dem len
	TIM3->EGR = 0x01;		// su kien reload   
	
}


void control(uint8_t x, uint8_t n)	// bat tat LEDx, n=1 bat, n=0 tat
{
	if(x < 12)	// A0 -> A11
	{
		if(n==0)
		{
			GPIOA->ODR &= ~(1 << x);
		} else
		{
			GPIOA->ODR |= (1 << x);
		}	
	} else if (x < 14)	// B0 B1
	{
		if(n==0)
		{
			GPIOB->ODR &= ~(1 << (x-12));
		} else
		{
			GPIOB->ODR |= (1 << (x-12));
		}
	} else if (x < 16)	// B5 B6
	{
		if(n==0)
		{
			GPIOB->ODR &= ~(1 << (x-9));
		} else
		{
			GPIOB->ODR |= (1 << (x-9));
		}
	} else		// B8 B9
	{
		if(n==0)
		{
			GPIOB->ODR &= ~(1 << (x-8));
		} else
		{
			GPIOB->ODR |= (1 << (x-8));
		}
	}
}

void PWM()
{
	for(i = 0; i<18; i++)
	{
		if(TIM2->CNT < arr[i]*flag[i])
		{
			control(i,1);
		} else
		{
			control(i,0);
		}
	}
}

void setup()	// do sang led tang dan tu led 0 -> led 17
{
	for( j = 0; j<18; j++) arr[j] = 11*(j+1);
}


int main()
{
	configTIM();
	configGPIO();
	setup();
	j = -1;
	k = 0;
	while(1)
	{
		PWM();
		
		if(TIM3->CNT > timeDelay)		// hieu ung sang dan tu led 0 -> led 17
		{
			if(k==0) // hieu ung sang dan tu led 0 -> led 17
			{
				flag[++j] = 1;
			} else		// hieu ung tat dan tu led 17 -> led 0
			{
				flag[--j] = 0;
			}
			if(j > 17) k = 1;
			if(j < 0) k = 0;
			TIM3->CNT = 0;
		} 
		
	}
}
