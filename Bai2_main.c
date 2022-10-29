#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
void Delay(unsigned int time);
GPIO_InitTypeDef GPIO_Struct;
int main()
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB,ENABLE);
    GPIO_Struct.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_Struct.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
    GPIO_Struct.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_Struct);
    
    GPIO_Struct.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_Struct.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
    GPIO_Struct.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&GPIO_Struct);
    while(1)
    {
        GPIO_SetBits(GPIOA,GPIO_Pin_1);
        GPIO_SetBits(GPIOA,GPIO_Pin_3);
        GPIO_SetBits(GPIOB,GPIO_Pin_1);
        GPIO_SetBits(GPIOB,GPIO_Pin_3);
        GPIO_ResetBits(GPIOA,GPIO_Pin_0);
        GPIO_ResetBits(GPIOA,GPIO_Pin_2);
        GPIO_ResetBits(GPIOB,GPIO_Pin_0);
        GPIO_ResetBits(GPIOB,GPIO_Pin_2);        
        Delay(150);
        GPIO_SetBits(GPIOA,GPIO_Pin_0);
        GPIO_SetBits(GPIOA,GPIO_Pin_2);
        GPIO_SetBits(GPIOB,GPIO_Pin_0);
        GPIO_SetBits(GPIOB,GPIO_Pin_2);
        GPIO_ResetBits(GPIOA,GPIO_Pin_1);
        GPIO_ResetBits(GPIOA,GPIO_Pin_3);
        GPIO_ResetBits(GPIOB,GPIO_Pin_1);
        GPIO_ResetBits(GPIOB,GPIO_Pin_3);
        Delay(150);

        
    }
}
void Delay(unsigned int time)
{
    unsigned int i,j;
    for(i=0;i<time;i++)
    {
        for(j=0;j<0x2AFF;j++);
    }
}
