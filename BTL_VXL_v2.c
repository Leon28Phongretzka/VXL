#include "stm32f10x.h"                  // Device header
#include "stm32f10x_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO
#include "stm32f10x_rcc.h"              // Keil::Device:StdPeriph Drivers:RCC
#include "RTE_Components.h"             // Component selection

#define CLOCK       GPIO_Pin_0
#define DATA        GPIO_Pin_1
#define LOCK_DATA 	GPIO_Pin_2

static int mang[9] = {0X00, 0X01, 0X03, 0X07, 0X0F, 0X1F, 0X3F, 0X7F, 0XFF};
int i;

void Config_gpio(void);
void delay(uint16_t vr_Time);
void Send_1_Byte(int dulieu);
void Send_4_Byte(int dulieu1, int dulieu2, int dulieu3, int dulieu4);

int main()
{
	Config_gpio();
	
	while(1)
	{
		for(i=0; i<9; i++)
		{
			Send_4_Byte(mang[i],0X00, 0X00, 0X00);
			delay(100);
		}
		for(i=1; i<9; i++)
		{
			Send_4_Byte(0XFF, mang[i], 0X00, 0X00);
			delay(100);
		}
		for(i=1; i<9; i++)
		{
			Send_4_Byte(0XFF, 0XFF, mang[i], 0X00);
			delay(100);
		}
		for(i=1; i<9; i++)
		{
			Send_4_Byte(0XFF, 0XFF, 0XFF, mang[i]);
			delay(100);
		}
		
		for(i=8; i>=0; i--)
		{
			Send_4_Byte(0XFF, 0XFF, 0XFF, mang[i]);
			delay(100);
		}
		for(i=7; i>=0; i--)
		{
			Send_4_Byte(0XFF, 0XFF, mang[i], 0X00);
			delay(100);
		}
		for(i=7; i>=0; i--)
		{
			Send_4_Byte(0XFF, mang[i], 0X00, 0X00);
			delay(100);
		}
		for(i=7; i>=0; i--)
		{
			Send_4_Byte(mang[i], 0X00, 0X00, 0X00);
			delay(100);
		}		
	}
}

void Config_gpio(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin   = CLOCK|DATA|LOCK_DATA;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void delay(uint16_t vr_Time)
{
	while(vr_Time)
	{
		for(int i = 0; i < 0x2aff; i++);
	}
}

void Send_1_Byte(int dulieu)
{
	int k, tach[8], dich=0X01;
	
	for(k=0; k<8; k++) // tach du lieu dau vao thanh cac bits
	{
		if(dulieu&dich) tach[i] = 1;
		else tach[i] = 0;
		dich = dich << 1;
	}
	for(k=7; k>=0; k--) // Ghi va dich du lieu
	{
//		Data = tach[i];
		GPIO_WriteBit(GPIOA, DATA, tach[k]);
//		Xung = 0;
//		Xung = 1;
		GPIO_WriteBit(GPIOA, CLOCK, 0);
		GPIO_WriteBit(GPIOA, CLOCK, 1);
	}
//	Chot = 0;
//	Chot = 1;
		GPIO_WriteBit(GPIOA, LOCK_DATA, 0);
		GPIO_WriteBit(GPIOA, LOCK_DATA, 1);
}

void Send_4_Byte(int dulieu1, int dulieu2, int dulieu3, int dulieu4)
{
	Send_1_Byte(dulieu4);
	Send_1_Byte(dulieu3);
	Send_1_Byte(dulieu2);
	Send_1_Byte(dulieu1);
}

