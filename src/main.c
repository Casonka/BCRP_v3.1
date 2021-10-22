/*
**
**                           DRIVER FOR STAND 3.0
**
**
**********************************************************************/
/*
   Last committed:     $Revision: $
   Last changed by:    $Author: CASKA $
   Last changed date:  $Date: 27.05.21 $
   ID:                 $Id:  $

**********************************************************************/
#include "allheaders.h"
int main(void)
{

    initAll();                          // инициализация портов платы
    init_regulator();                   // регулятор с коэффициентами
    set_status( 0, 0 , 0, 0 );          /// pi connect track


  while(1)
  {
    get_state();
  }

}
