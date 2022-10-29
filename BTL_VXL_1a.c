#include "stm32f10x.h"                  // Device header

#define CLOCK      GPIO_Pin_0
#define DATA       GPIO_Pin_1
#define DATA_LOCK  GPIO_Pin_2


int mang[9] = {0X00, 0X01, 0X03, 0X07, 0X0F, 0X1F, 0X3F, 0X7F, 0XFF};
int mang_2[9] = {0X00, 0X80, 0XC0, 0XE0, 0XF0, 0XF8, 0XFC, 0XFE, 0XFF};
int snake_eff[9]={0X00, 0X01, 0X02, 0X04, 0X08, 0X10, 0X20, 0X40, 0X80};
int butterfly_eff1[9]={0X00, 0X01, 0X03, 0X07, 0X0F, 0X1F, 0X3F, 0X7F, 0XFF};
int butterfly_eff2[9]={0X00, 0X80, 0XC0, 0XE0, 0XF0, 0XF8, 0XFC, 0XFE, 0XFF};
int i;

void Config(void);
void Delay(uint16_t Time);

void Send_1_Byte(int dulieu);
void Send_4_Byte(int dulieu1, int dulieu2, int dulieu3, int dulieu4);
void Write_4byte(uint32_t CMD);

int main()
{
	Config();
	while(1)
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_0); Delay(100);
        GPIO_SetBits(GPIOA,GPIO_Pin_1); Delay(100);
        GPIO_SetBits(GPIOA,GPIO_Pin_2); Delay(100);
        GPIO_SetBits(GPIOA,GPIO_Pin_3); Delay(100);
        GPIO_SetBits(GPIOA,GPIO_Pin_4); Delay(100);
        GPIO_SetBits(GPIOA,GPIO_Pin_5); Delay(100);
        GPIO_SetBits(GPIOA,GPIO_Pin_6); Delay(100);
        GPIO_SetBits(GPIOA,GPIO_Pin_7); Delay(100);
        GPIO_SetBits(GPIOA,GPIO_Pin_8); Delay(100);
        GPIO_SetBits(GPIOA,GPIO_Pin_9); Delay(100);
        GPIO_SetBits(GPIOA,GPIO_Pin_10); Delay(100);
        GPIO_SetBits(GPIOA,GPIO_Pin_11); Delay(100);
        GPIO_SetBits(GPIOA,GPIO_Pin_12); Delay(100);
        GPIO_SetBits(GPIOA,GPIO_Pin_13); Delay(100);
        GPIO_SetBits(GPIOA,GPIO_Pin_14); Delay(100);
        GPIO_SetBits(GPIOA,GPIO_Pin_15); Delay(100);
        GPIO_SetBits(GPIOB,GPIO_Pin_0); Delay(100);
        GPIO_SetBits(GPIOB,GPIO_Pin_1); Delay(100);
        GPIO_SetBits(GPIOB,GPIO_Pin_2); Delay(100);
        GPIO_SetBits(GPIOB,GPIO_Pin_3); Delay(100);
        GPIO_SetBits(GPIOB,GPIO_Pin_4); Delay(100);
        GPIO_SetBits(GPIOB,GPIO_Pin_5); Delay(100);
        GPIO_SetBits(GPIOB,GPIO_Pin_6); Delay(100);
        GPIO_SetBits(GPIOB,GPIO_Pin_7); Delay(100);
        GPIO_SetBits(GPIOB,GPIO_Pin_8); Delay(100);
        GPIO_SetBits(GPIOB,GPIO_Pin_9); Delay(100);
        GPIO_SetBits(GPIOB,GPIO_Pin_10); Delay(100);
        GPIO_SetBits(GPIOB,GPIO_Pin_11); Delay(100);
        GPIO_SetBits(GPIOB,GPIO_Pin_12); Delay(100);
        GPIO_SetBits(GPIOB,GPIO_Pin_13); Delay(100);
        GPIO_SetBits(GPIOB,GPIO_Pin_14); Delay(100);
        GPIO_SetBits(GPIOB,GPIO_Pin_15); Delay(100);
        GPIO_ResetBits(GPIOA,GPIO_Pin_0); Delay(100);
        GPIO_ResetBits(GPIOA,GPIO_Pin_1); Delay(100);
        GPIO_ResetBits(GPIOA,GPIO_Pin_2); Delay(100);
        GPIO_ResetBits(GPIOA,GPIO_Pin_3); Delay(100);
        GPIO_ResetBits(GPIOA,GPIO_Pin_4); Delay(100);
        GPIO_ResetBits(GPIOA,GPIO_Pin_5); Delay(100);
        GPIO_ResetBits(GPIOA,GPIO_Pin_6); Delay(100);
        GPIO_ResetBits(GPIOA,GPIO_Pin_7); Delay(100);
        GPIO_ResetBits(GPIOA,GPIO_Pin_8); Delay(100);
        GPIO_ResetBits(GPIOA,GPIO_Pin_9); Delay(100);
        GPIO_ResetBits(GPIOA,GPIO_Pin_10); Delay(100);
        GPIO_ResetBits(GPIOA,GPIO_Pin_11); Delay(100);
        GPIO_ResetBits(GPIOA,GPIO_Pin_12); Delay(100);
        GPIO_ResetBits(GPIOA,GPIO_Pin_13); Delay(100);
        GPIO_ResetBits(GPIOA,GPIO_Pin_14); Delay(100);
        GPIO_ResetBits(GPIOA,GPIO_Pin_15); Delay(100);
        GPIO_ResetBits(GPIOB,GPIO_Pin_0); Delay(100);
        GPIO_ResetBits(GPIOB,GPIO_Pin_1); Delay(100);
        GPIO_ResetBits(GPIOB,GPIO_Pin_2); Delay(100);
        GPIO_ResetBits(GPIOB,GPIO_Pin_3); Delay(100);
        GPIO_ResetBits(GPIOB,GPIO_Pin_4); Delay(100);
        GPIO_ResetBits(GPIOB,GPIO_Pin_5); Delay(100);
        GPIO_ResetBits(GPIOB,GPIO_Pin_6); Delay(100);
        GPIO_ResetBits(GPIOB,GPIO_Pin_7); Delay(100);
        GPIO_ResetBits(GPIOB,GPIO_Pin_8); Delay(100);
        GPIO_ResetBits(GPIOB,GPIO_Pin_9); Delay(100);
        GPIO_ResetBits(GPIOB,GPIO_Pin_10); Delay(100);
        GPIO_ResetBits(GPIOB,GPIO_Pin_11); Delay(100);
        GPIO_ResetBits(GPIOB,GPIO_Pin_12); Delay(100);
        GPIO_ResetBits(GPIOB,GPIO_Pin_13); Delay(100);
        GPIO_ResetBits(GPIOB,GPIO_Pin_14); Delay(100);
        GPIO_ResetBits(GPIOB,GPIO_Pin_15); Delay(100);
	}		
}

void Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB,ENABLE);
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
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


void Send_1_Byte(int dulieu)
{
	int k;
	for(k=1; k <= 8; k++ )// Ghi va dich du lieu
	{
		GPIO_WriteBit(GPIOA,DATA,(dulieu >> (8 - k)) & 1);
		GPIO_WriteBit(GPIOA,CLOCK,0);
		GPIO_WriteBit(GPIOA,CLOCK,1);
	}
		GPIO_WriteBit(GPIOA,DATA_LOCK,0);
		GPIO_WriteBit(GPIOA,DATA_LOCK,1);
}

void Send_4_Byte(int dulieu1, int dulieu2, int dulieu3, int dulieu4)
{
	Send_1_Byte(dulieu4);
	Send_1_Byte(dulieu3);
	Send_1_Byte(dulieu2);
	Send_1_Byte(dulieu1);
}
