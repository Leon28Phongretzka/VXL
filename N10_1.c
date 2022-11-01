#include "stm32f10x.h"                  // Device header
#include "stm32f10x_tim.h"              // Keil::Device:StdPeriph Drivers:TIM
#define PERIOD    255
#define PRESCCLER 72       

#define timeDelay 100		//  10 <=> 1ms

uint16_t arr[32] = {999};		// thoi gian pha cao trong 1 chu ki ( f=1khz, T = 1ms)
uint8_t flag[32] = {1};		// cho phep led sang
int mang[9] = {0X00, 0X01, 0X03, 0X07, 0X0F, 0X1F, 0X3F, 0X7F, 0XFF};
int mang_2[9] = {0X00, 0X80, 0XC0, 0XE0, 0XF0, 0XF8, 0XFC, 0XFE, 0XFF};
int snake_eff[9]={0X00, 0X01, 0X02, 0X04, 0X08, 0X10, 0X20, 0X40, 0X80};
int butterfly_eff1[9]={0X00, 0X01, 0X03, 0X07, 0X0F, 0X1F, 0X3F, 0X7F, 0XFF};
int butterfly_eff2[9]={0X00, 0X80, 0XC0, 0XE0, 0XF0, 0XF8, 0XFC, 0XFE, 0XFF};
uint8_t i, k;
int8_t j;

void PWM2_Init(void)
{
	/*Config TIM2*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	TIM_TimeBaseInitTypeDef TIM_InitStructure;
	TIM_InitStructure.TIM_ClockDivision      = 0;
	TIM_InitStructure.TIM_CounterMode        = TIM_CounterMode_Up;
	TIM_InitStructure.TIM_Period             = PERIOD - 1;
	TIM_InitStructure.TIM_Prescaler          = PRESCCLER -1;
	TIM_InitStructure.TIM_RepetitionCounter  = 0;
	TIM_TimeBaseInit(TIM2, &TIM_InitStructure);
	TIM_Cmd(TIM2, ENABLE);
	
	/*Config GPIO*/
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_All;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/*Config PWM*/
	TIM_OCInitTypeDef PWM_InitStructure;
	PWM_InitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	PWM_InitStructure.TIM_OutputState = TIM_OutputState_Enable;
	PWM_InitStructure.TIM_Pulse =100;
	PWM_InitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC1Init(TIM2, &PWM_InitStructure);
	TIM_OC2Init(TIM2, &PWM_InitStructure);
	TIM_OC3Init(TIM2, &PWM_InitStructure);
	TIM_OC4Init(TIM2, &PWM_InitStructure);
	TIM_CtrlPWMOutputs(TIM2, ENABLE);
}
void PWM3_Init(void)
{
	/*Config TIM3*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	TIM_TimeBaseInitTypeDef TIM_InitStructure;
	TIM_InitStructure.TIM_ClockDivision      = 0;
	TIM_InitStructure.TIM_CounterMode        = TIM_CounterMode_Up;
	TIM_InitStructure.TIM_Period             = PERIOD - 1;
	TIM_InitStructure.TIM_Prescaler          = PRESCCLER -1;
	TIM_InitStructure.TIM_RepetitionCounter  = 0;
	TIM_TimeBaseInit(TIM3, &TIM_InitStructure);
	TIM_Cmd(TIM3, ENABLE);
	
	/*Config GPIO*/
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	/*Config PWM*/
	TIM_OCInitTypeDef PWM_InitStructure;
	PWM_InitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	PWM_InitStructure.TIM_OutputState = TIM_OutputState_Enable;
	PWM_InitStructure.TIM_Pulse =100;
	PWM_InitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC1Init(TIM3, &PWM_InitStructure);
	TIM_OC2Init(TIM3, &PWM_InitStructure);
	TIM_OC3Init(TIM3, &PWM_InitStructure);
	TIM_OC4Init(TIM3, &PWM_InitStructure);
	TIM_CtrlPWMOutputs(TIM3, ENABLE);	
}
void Delay(uint16_t Time)
{
	int i = 0;
	while(Time--)
	{
		for(i = 0 ; i < 0x2aff; i++);
	}
}

void control(uint8_t x, uint8_t n)	// bat tat LEDx, n=1 bat, n=0 tat
{
    if(x<16)
    {
        if(n==0) GPIO_ResetBits(GPIOA, 1<<x);
        else GPIO_SetBits(GPIOA, 1<<x);
        Delay(timeDelay);

    }
    else
    {
        if(n==0) GPIO_ResetBits(GPIOB, 1<<(x-16));
        else GPIO_SetBits(GPIOB, 1<<(x-16));
        Delay(timeDelay);
    }
}

void setup()	// do sang led tang dan tu led 0 -> led 31
{
	for(i = 0; i<32; i++)
	{

		if( TIM_GetCounter(TIM2) < arr[i]*flag[i]) // neu thoi gian hien tai nho hon thoi gian pha cao thi bat led
		{
			control(i, 1);
		} else
		{
			control(i, 0);
		}
		
	}
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
		PWM2_Init();
        PWM3_Init();
		if(TIM_GetCounter(TIM3) > timeDelay)		// hieu ung sang dan tu led 0 -> led 32
		{
			if(k==0) // hieu ung sang dan tu led 0 -> led 32
			{
				flag[++j] = 1;
			} else		// hieu ung tat dan tu led 32 -> led 0
			{
				flag[--j] = 0;
			}
			if(j > 31) k = 1;
			if(j < 0) k = 0;
			TIM_SetCounter(TIM3, 0); // reset counter timer 3
		} 
		
	}
}
