#ifndef _PINS_H_
#define _PINS_H_

#include "allheaders.h"


#define PORTA 0
#define PORTB 1
#define PORTC 2
#define PORTD 3
#define PORTE 4

#define AF0  0
#define AF1  1
#define AF2  2
#define AF3  3
#define AF4  4
#define AF5  5
#define AF6  6
#define AF7  7
#define AF8  8
#define AF9  9
#define AF10 10
#define AF11 11
#define AF12 12
#define AF13 13
#define AF14 14
#define AF15 15

//mode
#define INPUT               0x00
#define OUTPUT_10MHz        0x01
#define OUTPUT_2MHz         0x02
#define OUTPUT_50MHz        0x03

//input config
#define ANALOG              0x01
#define FLOATING            0x00
#define PU_PD               0x02


//output config
#define GENERAL_PUSH_PULL           0x00
#define GENERAL_OPEN_DRAIN          0x01
#define ALTERNATE_PUSH_PULL         0x02
#define ALTERNATE_OPEN_DRAIN        0x03

//pull
#define NO_PULL_UP 0x01
#define PULL_UP    0x00
#define PULL_DOWN  0x01

#define GPIO_BASE  (APB2PERIPH_BASE + 0x0800)
#define GPIO       ((unsigned char *) GPIO_BASE)

//получение адреса PIN_PORT в пам€ти
#define pin_id(PIN_PORT, PIN) ( (PIN_PORT<<4)|PIN )
#define GPIO_offset           ((uint32_t)0x00000400)
#define GPIO_base(pin)        (GPIO_BASE +(pin>>4)*GPIO_offset )

//Ќазначение пину значени€
#define pins_mode(pin, mode) ((uint32_t) (mode) <<((pin%8)*4))
#define pins_conf(pin, conf) ((uint32_t) (conf) <<(((pin%8)*4)+2))
#define pins_pull(pin, pull) ((uint32_t) 1<<(pin-(pin/16)*16)<<(pull*16))


//очистка и установкка значени€
#define conf_mode(pin, mode)  {*((uint32_t *) (GPIO_base(pin)+((pin/8)%2)*4)) = \
                ((*((uint32_t *) (GPIO_base(pin)+((pin/8)%2)*4))&(~pins_mode(pin, 0x3)))|pins_mode(pin, mode));}

#define conf_conf(pin, conf)  {*((uint32_t *) (GPIO_base(pin)+((pin/8)%2)*4)) = \
                ((*((uint32_t *) (GPIO_base(pin)+((pin/8)%2)*4))&(~pins_conf(pin, 0x3)))|pins_conf(pin, conf));}

#define conf_pull(pin, pull)  {*((uint32_t *) (GPIO_base(pin)+0x10)) = \
                ((*((uint32_t *) (GPIO_base(pin)+0x10)))|pins_pull(pin, pull));}

//группова€ очистка и установка всех регистров
#define conf_pin(pin, mode, conf, pull) {\
conf_mode(pin, mode)  \
conf_conf(pin, conf) \
conf_pull(pin, pull)}

//выбор альтернативной функции
#define conf_af(pin, af)  {*((uint32_t *) (GPIO_base(pin)+0x20+((pin&0x08)>>1))) = \
                ((*((uint32_t *) (GPIO_base(pin)+0x20+((pin&0x08)>>1)))&(~pin_af(pin,0xF)))|pin_af(pin,af));}

//установить 1
#define set_pin(pin)   (*((uint32_t *)((GPIO_base(pin)) + 0x10))= ((uint32_t) 1<<(pin-(pin/16)*16)))

//установить 0
#define reset_pin(pin) (*((uint32_t *)((GPIO_base(pin)) + 0x10))= ((uint32_t) 1<<(pin-(pin/16)*16)<<16))

//физическое значение на ножке

#define pin_val(pin) (((*((uint32_t *)(GPIO_base(pin) + 0x8)))&((uint32_t)1<<(pin-(pin/16)*16)))>>(pin-(pin/16)*16))

//состо€ние регистра вывода
#define pin_out(pin) (((*((uint32_t *)(GPIO_base(pin) + 0x0C)))&((uint32_t)1<<(pin-(pin/16)*16)))>>(pin-(pin/16)*16))


//инициализаци€ дл€ портов EXTI
#define config_af_exti(pin)  {*((uint32_t *) (AFIO_BASE+0x08 + (4*((pin&0xf)/4)))) = \
                (*((uint32_t *) (AFIO_BASE+0x08 + (4*((pin&0xf)/4)))) &(~(0xf<<(4*(pin&0x3)))) | ((pin/16)<<((pin&0x3)*4)));}

#define EXTI_FALLING_EDGE	0
#define EXTI_RISING_EDGE	1
#define EXTI_BOTH_EDGES		2
//-------------------------------------------------------------
//-------------------------PWM---------------------------------

#define MAX_PWM             4095.0

#define MOTOR1_PWM_PIN      pin_id(PORTA,9)
#define MOTOR1_CCR          (uint32_t *)&(TIM1->CCR1)

#define MOTOR1_DIR_PIN      pin_id(PORTA,8)

//-------------------------------------------------------------
//-------------------------ADC---------------------------------
#define POT_PIN             pin_id(PORTA,0)

//-------------------------------------------------------------
//-------------------------BUTTONS-----------------------------

#define BUTTON_UP           pin_id(PORTB,5)
#define BUTTON_DOWN         pin_id(PORTB,4)

//-------------------------------------------------------------
//-------------------------EXTI--------------------------------

#define BUTTON15_EMERG        pin_id(PORTC,15)
#define EXTI5_ZERO           pin_id(PORTB,5)
#define EXTI4_UNZERO         pin_id(PORTB,4)

//-------------------------------------------------------------
//-------------------------TUMBLE------------------------------

#define TYPE_1              pin_id(PORTB,13)
#define TYPE_2              pin_id(PORTB,13)

//-------------------------------------------------------------
//-------------------------TENZO-------------------------------

#define TENZO1_RCC          pin_id(PORTA,15)
#define TENZO2_RCC          pin_id(PORTA,11)

#define TENZO1_DATA         pin_id(PORTA,12)
#define TENZO2_DATA         pin_id(PORTA,10)

//-------------------------------------------------------------
//-------------------------ENCODER-----------------------------

#define ENCODER1A_PIN       pin_id(PORTB,6)
#define ENCODER1B_PIN       pin_id(PORTB,7)

#define ENCODER1_CNT        ((uint32_t *)&(TIM4->CNT))

//-------------------------------------------------------------
//-------------------------LEDS--------------------------------

#define LED_RED             pin_id(PORTA,2)
#define LED_GREEN           pin_id(PORTA,1)


//-------------------------------------------------------------
//-------------------------SYCHO-------------------------------

#define HEAD_PIN14          pin_id(PORTC,14)
#define MUSCLE_PIN          pin_id(PORTC,13)

//-------------------------------------------------------------
//-------------------------LCD---------------------------------

#define I2C_SDA_PIN         pin_id(PORTB,9)
#define I2C_SCL_PIN         pin_id(PORTB,8)

#endif /*_PINS_H_*/
