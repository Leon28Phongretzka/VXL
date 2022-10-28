#include "stm32f10x.h"                  // Device header

#define CLOCK      GPIO_Pin_0
#define DATA       GPIO_Pin_1
#define DATA_LOCK  GPIO_Pin_2


int i = 0;

void Config(void);
void Delay(uint16_t Time);
void Write_4byte(uint32_t CMD);

int main(void)
{
	Config();
	while(1)
	{
	Write_4byte(0xAAAAAAAA);
		Delay(100);
	Write_4byte(0x55555555);		
		Delay(100);
	}
	return 0;
}

void Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void Delay(uint16_t Time)
{
	int i = 0;
	while(Time--)
	{
		for(i = 0 ; i < 0x2aff; i++);
	}
}

void Write_4byte(uint32_t CMD)
{
	int k;
	for(k=1; k <= 32; k++ )// Ghi va dich du lieu
	{
		GPIO_WriteBit(GPIOA,DATA,(CMD >> (32 - k)) & 1);
		GPIO_WriteBit(GPIOA,CLOCK,0);
		GPIO_WriteBit(GPIOA,CLOCK,1);
	}
		GPIO_WriteBit(GPIOA,DATA_LOCK,0);
		GPIO_WriteBit(GPIOA,DATA_LOCK,1);	
}
