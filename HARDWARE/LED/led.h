#ifndef _LED_H_
#define _LED_H_

#include "sys.h"

void LED_Init(void);

#define LED_R PDout(14)
#define LED_G PCout(8)
#define LED_B PDout(15)

#define ON 1
#define OFF 0
#endif
