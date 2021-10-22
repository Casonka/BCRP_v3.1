#include "regulator.h"

BCRPregulate BCRPreg;
BCRPstat status;


int32_t encoderData = 0;

void encoder_input(void)
{
    encoderData = *ENCODER1_CNT;
    //*ENCODER1_CNT = 0;

}

void init_regulator(void) // первая инициализация
{
    /// над коэффициентами поработать
BCRPreg.i_k = 0;
BCRPreg.p_k = 1.0;




}

void set_status(char pi_enable, char kinemen, char connectionen, char tracken) /// различные режимы
{
    status.pi_enabled = pi_enable;
    status.connectionen = connectionen;
    status.kinemen = kinemen;
    status.tracken = tracken;

}

void pi_calc(BCRPregulate *pi_control)  // вычисление пи
{

}
