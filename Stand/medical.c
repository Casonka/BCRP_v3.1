#include "medical.h"


//void go_to_zero(void)
//{
//
//
//}
uint8_t state  = 0;
int flag_ini = 0;



uint8_t get_tumble(void)
{

    if( !pin_val(TYPE_1) && !pin_val(TYPE_2) )
    {
        tumbler = 1;
        return tumbler;
    }
    if( pin_val(TYPE_1) && !pin_val(TYPE_2) )
    {
        tumbler = 2;
        return tumbler;
    }
    if( !pin_val(TYPE_1) && pin_val(TYPE_2) )
    {
        tumbler = 3;
        return tumbler;
    }
    if( pin_val(TYPE_1) && pin_val(TYPE_2) )
    {
        tumbler = 0;
        return tumbler;
    }
}

uint8_t get_state(void)
{

    if( !pin_val( BUTTON_DOWN ) && !pin_val( BUTTON_UP ) )
    {
        reset_pin( LED_RED );
        reset_pin( LED_GREEN );

//        if( pin_val( EXTI5_ZERO ) )
//        {
//            state = 5;
//            return state;
//        }
//
//        if( pin_val( EXTI4_UNZERO ) )
//        {
//            state  = 6;
//            return state;
//        }
    state = 1;
    return state;
    }

    if( pin_val( BUTTON_DOWN ) && !pin_val( BUTTON_UP ) )
    {
        state = 2;
        return state;
    }

    if( !pin_val( BUTTON_DOWN ) && pin_val( BUTTON_UP ) )
    {
        state = 3;
        return state;
    }

    if( pin_val( BUTTON_DOWN ) && pin_val( BUTTON_UP ) )
    {
        state = 4;
        return state;
    }
}

void calibration(void)
{

if( state == 1 )
{
    setVoltage( 0.0 );
}
if( state == 2 )
{
    setVoltage( 0.2 );
}
if( state == 3)
{
    setVoltage( -0.2 );
}
if( state == 4)
    setVoltage( 0.0);

}
