#include "Board.h"

void setVoltage(float duty) // задать направление движения двигателю
{
if(duty > 1)  duty = 1.0;
if(duty < -1) duty = -1.0;
if(duty > 0)
{
    *MOTOR1_CCR = (int32_t)( MAX_PWM - (duty * MAX_PWM) );
    set_pin(MOTOR1_DIR_PIN);
}
else
{
    *MOTOR1_CCR = (int32_t) ( duty * MAX_PWM );
    reset_pin(MOTOR1_DIR_PIN);
}
}

void setPWM(float duty) // просто установить ШИМ на выходе
{
if(duty > 1) duty = 1.0;
if(duty < 0) duty = 0.0;
 *MOTOR1_CCR = (int32_t)( duty * MAX_PWM);
}

void add_ext_interrupt( unsigned char pin, char edge ) // добавить прерывание
{
    config_af_exti(pin);
    EXTI->IMR |= (1<<(pin&0xf));

 switch (edge)
 	{
		case EXTI_FALLING_EDGE:
		  {
		  	 EXTI->FTSR |= (1<<(pin&0xf));
		  	 EXTI->RTSR &= ~(1<<(pin&0xf));
        break;
		  }

		case EXTI_RISING_EDGE:
		  {
             EXTI->FTSR &= ~(1<<(pin&0xf));
		  	 EXTI->RTSR |= (1<<(pin&0xf));
			 break;
		  }

		case EXTI_BOTH_EDGES:
		  {
		  	 EXTI->RTSR |= (1<<(pin&0xf));
			 EXTI->FTSR |= (1<<(pin&0xf));
			 break;
		  }
	}
	 EXTI->PR = EXTI_PR_PR0;
}

void timEncoderConfigure(TIM_TypeDef * TIM)
{
  TIM->PSC   = 0x0;
  TIM->ARR   = 0xFFFF;
  TIM->CR1   = TIM_CR1_ARPE     | TIM_CR1_CEN;
  TIM->SMCR  = TIM_SMCR_SMS_0   | TIM_SMCR_SMS_1|TIM_SMCR_ETF_0|TIM_SMCR_ETF_1|TIM_SMCR_ETF_2|TIM_SMCR_ETF_3;
  TIM->CCMR1 = TIM_CCMR1_CC1S_0 | TIM_CCMR1_CC2S_0;
  TIM->CNT   = 0;
}

void timPWMConfigure(TIM_TypeDef * TIM, uint16_t prescaler, uint16_t autoReset,
                     char ch1, char ch2, char ch3, char ch4)
{
  if(ch1)
  {
    TIM->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1FE;
    TIM->CCER  |= TIM_CCER_CC1E;
  }
  if(ch2)
  {
    TIM->CCMR1 |= TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2FE;
    TIM->CCER  |= TIM_CCER_CC2E;
  }
  if(ch3)
  {
    TIM->CCMR2 |= TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3FE;
    TIM->CCER  |= TIM_CCER_CC3E;
  }
  if(ch4)
  {
    TIM->CCMR2 |= TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4FE;
    TIM->CCER  |= TIM_CCER_CC4E;
  }

  TIM->PSC  = prescaler;
  TIM->ARR  = autoReset;
  TIM->CR1  = TIM_CR1_ARPE  | TIM_CR1_CEN | TIM_CR1_URS;
  TIM->DIER = TIM_DIER_UIE;
  TIM->BDTR = TIM_BDTR_MOE  | TIM_BDTR_AOE;

 // TIM->BDTR = TIM_BDTR_MOE  | TIM_BDTR_AOE;
  TIM->CCR1 = 0x00;
  TIM->CCR2 = 0x00;
  TIM->EGR  = TIM_EGR_UG;
}

////////////////////////////////////////////////////////////////////////////////
void timPIDConfigure(TIM_TypeDef * TIM, uint16_t prescaler, uint16_t autoReset)
{
  TIM->CNT   = 0;
  TIM->PSC   = prescaler;
  TIM->ARR   = autoReset;
  TIM->DIER |= TIM_DIER_UIE;
  TIM->CR1   = TIM_CR1_ARPE | TIM_CR1_CEN;
}

void initAll(void) // инициализация портов
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
   PWR->CR|=PWR_CR_DBP;
   __disable_irq();
   SysTick_Config(72000);

  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC, ENABLE);   ///Включаем общее тактирование

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); /// Включаем тактирование PORTA
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); /// Включаем тактирование PORTB
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); /// Включаем тактирование PORTC
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,  ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,  ENABLE); /// TIM1
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,  ENABLE); /// TIM2
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,  ENABLE); /// TIM3
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,  ENABLE); /// TIM4
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1,  ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,  ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

AFIO->MAPR |= AFIO_MAPR_SWJ_CFG_JTAGDISABLE; /// Отключаем JTAG для работы порта PB3 на вход
//------------------------------------------PWM-----------------------------------------------

conf_pin(MOTOR1_PWM_PIN,OUTPUT_10MHz,ALTERNATE_PUSH_PULL,NO_PULL_UP);
conf_pin(MOTOR1_DIR_PIN,OUTPUT_10MHz,GENERAL_PUSH_PULL,NO_PULL_UP);

//-----------------------------------------BUTTONS---------------------------------------------

conf_pin(ENCODER1A_PIN,INPUT,ALTERNATE_PUSH_PULL,PULL_UP);
conf_pin(ENCODER1B_PIN,INPUT,ALTERNATE_PUSH_PULL,PULL_UP);

//-----------------------------------------BUTTONS---------------------------------------------

conf_pin(BUTTON_UP,INPUT,PU_PD,PULL_DOWN);
conf_pin(BUTTON_DOWN,INPUT,PU_PD,PULL_DOWN);

conf_pin(TYPE_1,INPUT,PU_PD,PULL_DOWN);
conf_pin(TYPE_2,INPUT,PU_PD,PULL_DOWN);

//------------------------------------------ADC------------------------------------------------

conf_pin(POT_PIN,INPUT,ANALOG,NO_PULL_UP);

//-----------------------------------------LED-------------------------------------------------

conf_pin(LED_RED,OUTPUT_50MHz,GENERAL_PUSH_PULL,NO_PULL_UP);
conf_pin(LED_GREEN,OUTPUT_50MHz,GENERAL_PUSH_PULL,NO_PULL_UP);

//----------------------------------------SYNCHRO----------------------------------------------

conf_pin(HEAD_PIN14,INPUT,PU_PD,NO_PULL_UP);
conf_pin(MUSCLE_PIN,OUTPUT_10MHz,GENERAL_PUSH_PULL,NO_PULL_UP);

//-------------------------------------EXTI_CONF------------------------------------------------

//add_ext_interrupt(EXTI4_UNZERO,EXTI_RISING_EDGE);
//add_ext_interrupt(EXTI5_ZERO, EXTI_RISING_EDGE);
//add_ext_interrupt(HEAD_PIN14,EXTI_FALLING_EDGE);
//add_ext_interrupt(BUTTON15_EMERG, EXTI_RISING_EDGE);

//-------------------------------------TIM_CONF------------------------------------------------

timPWMConfigure( TIM1 , 1    , MAX_PWM , 1 , 0 , 0 , 0 );
timPIDConfigure( TIM2 , 7200 , 1000);                           // 10Hz
timPWMConfigure( TIM3 , 240  , 1000, 0 , 0 , 0 , 0 );
timEncoderConfigure(TIM4);

NVIC_EnableIRQ( TIM2_IRQn );
NVIC_EnableIRQ( TIM3_IRQn );

//NVIC_EnableIRQ( EXTI4_IRQn     );
//NVIC_EnableIRQ( EXTI9_5_IRQn   );
//NVIC_EnableIRQ( EXTI15_10_IRQn );

__enable_irq();
}
