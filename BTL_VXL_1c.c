#include "stm32f10x.h"                  // Device header
#include "stm32f10x_tim.h"
#define CLOCK_A     GPIO_Pin_0
#define DATA_A      GPIO_Pin_1
#define DATA_LOCK_A   GPIO_Pin_2

#define CLOCK_B     GPIO_Pin_6
#define DATA_B      GPIO_Pin_7
#define DATA_LOCK_B   GPIO_Pin_8


int mang[9] = {0X00, 0X01, 0X03, 0X07, 0X0F, 0X1F, 0X3F, 0X7F, 0XFF};
int mang_2[9] = {0X00, 0X80, 0XC0, 0XE0, 0XF0, 0XF8, 0XFC, 0XFE, 0XFF};
int snake_eff[9]={0X00, 0X01, 0X02, 0X04, 0X08, 0X10, 0X20, 0X40, 0X80};
int butterfly_eff1[9]={0X00, 0X01, 0X03, 0X07, 0X0F, 0X1F, 0X3F, 0X7F, 0XFF};
int butterfly_eff2[9]={0X00, 0X80, 0XC0, 0XE0, 0XF0, 0XF8, 0XFC, 0XFE, 0XFF};
int i;

void Config(void);
void Delay(uint16_t Time);
void Send_1_Byte_A(int dulieu);
void Send_1_Byte_B(int dulieu);
void Send_4_Byte_A(int dulieu1, int dulieu2, int dulieu3, int dulieu4);
void Send_4_Byte_B(int dulieu1, int dulieu2, int dulieu3, int dulieu4);
void Write_4byte(uint32_t CMD);
void Timer_32led(void);
int main()
{
	Config();
	while(1)
	{
		// Sang dan va tat dan tu den dau tien toi den cuoi cung
		for(i=0; i<9; i++)
		{
			Send_4_Byte_A(mang[i],0X00, 0X00, 0X00);
			Delay(100);
		}
		for(i=1; i<9; i++)
		{
			Send_4_Byte_A(0XFF, mang[i], 0X00, 0X00);
			Delay(100);
		}
        for(i=0; i<9; i++)
		{
			Send_4_Byte_B(mang[i], 0X00, 0X00, 0X00);
			Delay(100);
		}
		for(i=1; i<9; i++)
		{
			Send_4_Byte_B(0XFF,mang[i], 0X00, 0X00);
			Delay(100);
		}
		Send_4_Byte_A(0X00, 0X00, 0X00, 0X00);
		Send_4_Byte_B(0X00, 0X00, 0X00, 0X00);
		Delay(100);
    }
}

void Config(void)
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
void Delay(uint16_t Time)
{
	int i = 0;
	while(Time--)
	{
		for(i = 0 ; i < 0x2aff; i++);
	}
}


void Send_1_Byte_A(int dulieu)
{
	int k;
	for(k=1; k <= 8; k++ )// Ghi va dich du lieu
	{
		GPIO_WriteBit(GPIOA,DATA_A,(dulieu >> (8 - k)) & 1);
		GPIO_WriteBit(GPIOA,CLOCK_A,0);
		GPIO_WriteBit(GPIOA,CLOCK_A,1);
	}
		GPIO_WriteBit(GPIOA,DATA_LOCK_A,0);
		GPIO_WriteBit(GPIOA,DATA_LOCK_A,1);
}

void Send_4_Byte_A(int dulieu1, int dulieu2, int dulieu3, int dulieu4)
{
	Send_1_Byte_A(dulieu4);
	Send_1_Byte_A(dulieu3);
	Send_1_Byte_A(dulieu2);
	Send_1_Byte_A(dulieu1);
}
void Send_1_Byte_B(int dulieu)
{
	int k;
	for(k=1; k <= 8; k++ )// Ghi va dich du lieu
	{
		GPIO_WriteBit(GPIOB,DATA_B,(dulieu >> (8 - k)) & 1); // dich phai 8-k bit
		GPIO_WriteBit(GPIOB,CLOCK_B,0); // xuat xung xuong
		GPIO_WriteBit(GPIOB,CLOCK_B,1); // xuat xung len
	}
		GPIO_WriteBit(GPIOB,DATA_LOCK_B,0); // xuat xung xuong
		GPIO_WriteBit(GPIOB,DATA_LOCK_B,1); // xuat xung len
}

void Send_4_Byte_B(int dulieu1, int dulieu2, int dulieu3, int dulieu4)
{
	Send_1_Byte_B(dulieu4);
	Send_1_Byte_B(dulieu3);
	Send_1_Byte_B(dulieu2);
	Send_1_Byte_B(dulieu1);
}
