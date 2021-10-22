#include "Interrupts.h"


BCRPstat status;

volatile uint32_t globalTime = 0;
volatile uint8_t seconds = 0;
volatile uint8_t minutes = 0;
volatile uint8_t hours = 0;
float testSpeed = 0;

void TIM2_IRQHandler(void) // регулятор ПИ
{

TIM2->SR = 0;
encoder_input();

if(status.pi_enabled) pi_calc(testSpeed);
//if(status.kinemen) ;
}

void TIM3_IRQHandler(void) 
{
TIM3->SR = 0;
}

void SysTick_Handler(void)
{
    globalTime++;
    seconds = globalTime / 1000;
    minutes = globalTime / 60000;

}


void EXTI4_Handler(void)
{
 EXTI->PR = EXTI_PR_PR4;
}

void EXTI9_5_IRQHandler(void)
{
    switch (EXTI->PR)
    {
    case EXTI_PR_PR5:
    {
        EXTI->PR = EXTI_PR_PR5;
    }
    break;
    case EXTI_PR_PR6:
    {
        EXTI->PR = EXTI_PR_PR6;
    }
    break;
    case EXTI_PR_PR7:
    {
        EXTI->PR = EXTI_PR_PR7;
    }
    break;
    case EXTI_PR_PR8:
    {
        EXTI->PR = EXTI_PR_PR8;
    }
    break;
    case EXTI_PR_PR9:
    {
        EXTI->PR = EXTI_PR_PR9;
    }
    break;
    }
}

void EXTI15_10_IRQHandler(void)
{
    switch (EXTI->PR)
    {
    case EXTI_PR_PR10:
    {
        EXTI->PR = EXTI_PR_PR10;
    }
    break;
    case EXTI_PR_PR11:
    {
        EXTI->PR = EXTI_PR_PR11;
    }
    break;
    case EXTI_PR_PR12:
    {
        EXTI->PR = EXTI_PR_PR12;
    }
    break;
    case EXTI_PR_PR13:
    {
        EXTI->PR = EXTI_PR_PR13;
    }
    break;
    case EXTI_PR_PR14:
    {
        EXTI->PR = EXTI_PR_PR14;
    }
    break;
    case EXTI_PR_PR15:
    {
        EXTI->PR = EXTI_PR_PR15;
    }
    break;
    }
}
