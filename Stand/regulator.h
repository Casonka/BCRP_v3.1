#ifndef _REGULATOR_H_
#define _REGULATOR_H_

#include "allheaders.h"

#define thread_pitch        0.001           ///шаг резьбы
#define normal_length       1               ///длина винта
#define R_screw             0.002           ///радиус винта
#define PI                  3.1415926535    ///число пи

#define length_of_R ((2.0 * PI) * R_screw)  /// длина окружности



extern int32_t encoderData;
//extern int;    encoder_angle;

typedef struct
{
    char pi_enabled;
    char kinemen;
    char tracken;
    char connectionen;

}BCRPstat;

typedef struct
{

float    p_k;
float    i_k;
float    target;
float    current;
float    error;
float    sum_error;
char     regulation_enabled;
char     regulation_finished;
char     regulation_outputed;
float    max_sum_error;
float    min_sum_error;
float    max_output;
float    min_output;
float    output;

}BCRPregulate;

extern          BCRPregulate BCRPreg;
extern          BCRPstat status;


#endif /*_REGULATOR_H_*/
