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
		for(i=0; i<9; i++)
		{
			Write_4_Byte(mang[i],0X00, 0X00, 0X00);
			Delay(100);
		}
		for(i=1; i<9; i++)
		{
			Write_4_Byte(0XFF, mang[i], 0X00, 0X00);
			Delay(100);
		}
		for(i=1; i<9; i++)
		{
			Write_4_Byte(0XFF, 0XFF, mang[i], 0X00);
			Delay(100);
		}
		for(i=1; i<9; i++)
		{
			Write_4_Byte(0XFF, 0XFF, 0XFF, mang[i]);
			Delay(100);
		}
		
		for(i=8; i>=0; i--)
		{
			Write_4_Byte(0XFF, 0XFF, 0XFF, mang[i]);
			Delay(100);
		}
		for(i=7; i>=0; i--)
		{
			Write_4_Byte(0XFF, 0XFF, mang[i], 0X00);
			Delay(100);
		}
		for(i=7; i>=0; i--)
		{
			Write_4_Byte(0XFF, mang[i], 0X00, 0X00);
			Delay(100);
		}
		for(i=7; i>=0; i--)
		{
			Write_4_Byte(mang[i], 0X00, 0X00, 0X00);
			Delay(100);
		}		
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
