#include "stm32f10x.h"                  // Device header
#include "stm32f10x_tim.h"              // Keil::Device:StdPeriph Drivers:TIM
#define CLOCK_A     GPIO_Pin_0
#define DATA_A      GPIO_Pin_1
#define DATA_LOCK_A   GPIO_Pin_2

#define CLOCK_B     GPIO_Pin_6
#define DATA_B      GPIO_Pin_7
#define DATA_LOCK_B   GPIO_Pin_8           

#define timeDelay 500		//  10 <=> 1ms

uint16_t arr[18] = {999};		// thoi gian pha cao trong 1 chu ki ( f=1khz, T = 1ms)
uint8_t flag[18] = {1};		// cho phep led sang
int mang[9] = {0X00, 0X01, 0X03, 0X07, 0X0F, 0X1F, 0X3F, 0X7F, 0XFF};
int mang_2[9] = {0X00, 0X80, 0XC0, 0XE0, 0XF0, 0XF8, 0XFC, 0XFE, 0XFF};
int snake_eff[9]={0X00, 0X01, 0X02, 0X04, 0X08, 0X10, 0X20, 0X40, 0X80};
int butterfly_eff1[9]={0X00, 0X01, 0X03, 0X07, 0X0F, 0X1F, 0X3F, 0X7F, 0XFF};
int butterfly_eff2[9]={0X00, 0X80, 0XC0, 0XE0, 0XF0, 0XF8, 0XFC, 0XFE, 0XFF};
uint8_t i, k;
int8_t j;

void ConfigGPIO(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB,ENABLE);
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin   = CLOCK_A|DATA_A|DATA_LOCK_A;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin   = CLOCK_B|DATA_B|DATA_LOCK_B;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void configTIM()	
{
	/* Config TIM2 */
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure_2;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    TIM_TimeBaseStructure_2.TIM_Period = 1000-1;		// 1ms
    TIM_TimeBaseStructure_2.TIM_Prescaler = 72-1;		// 1us
    TIM_TimeBaseStructure_2.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure_2.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure_2);
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
    TIM_Cmd(TIM2, ENABLE);
	
	/* config TIM 3 */  
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure_3;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    TIM_TimeBaseStructure_3.TIM_Period = 1000-1;		// 1ms
    TIM_TimeBaseStructure_3.TIM_Prescaler = 72-1;		// 1us
    TIM_TimeBaseStructure_3.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure_3.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure_3);
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
    TIM_Cmd(TIM3, ENABLE);

}


void control(uint8_t x, uint8_t n)	// bat tat LEDx, n=1 bat, n=0 tat
{
    if(x<16)
    {
        if(n==0) GPIO_ResetBits(GPIOA, 1<<x);
        else GPIO_SetBits(GPIOA, 1<<x);
    }
    else
    {
        if(n==0) GPIO_ResetBits(GPIOB, 1<<(x-16));
        else GPIO_SetBits(GPIOB, 1<<(x-16));
    }
}

void PWM()
{
    // 32 led
    for( int i=0; i<32; i++)
    {
        // if counter timer 2  < arr[i]*flag[i] turn led on
        if( TIM_GetCounter(TIM2) < arr[i]*flag[i] )
        {
            control(i,1);
        }
        else
        {
            control(i,0);
        }
        

    }
}

void setup()	// do sang led tang dan tu led 0 -> led 31
{
	for( j = 0; j<32; j++) arr[j] = 11*(j+1);
}


int main()
{
	configTIM();
	ConfigGPIO();
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
