#ifndef _BOARD_H_
#define _BOARD_H_

#include "allheaders.h"

void setVoltage(float duty);
void setPWM(float duty);
void add_ext_interrupt(unsigned char pin,char edge);
void initAll(void);

#endif /*_BOARD_H_*/
