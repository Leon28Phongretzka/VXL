#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
void Delay(unsigned int time);
GPIO_InitTypeDef GPIO_Strtr;
int main()
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
    GPIO_Strtr.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_Strtr.GPIO_Pin=GPIO_Pin_12;
    GPIO_Strtr.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&GPIO_Strtr);
    while(1)
    {
        GPIO_SetBits(GPIOB,GPIO_Pin_12);
        Delay(150);
        GPIO_ResetBits(GPIOB,GPIO_Pin_12);
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
