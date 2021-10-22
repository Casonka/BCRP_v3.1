#ifndef _MEDICAL_H_
#define _MEDICAL_H_


#include "allheaders.h"

extern uint8_t tumbler;
extern uint8_t state;

void StateAuto(float duty, int adc_min, int adc_max);
//void go_to_zero(void);

void get_tenzo();

extern uint8_t get_tumble(void);
extern uint8_t get_state(void);



#endif /*_MEDICAL_H_*/
