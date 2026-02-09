#ifndef __CSB_H
#define __CSB_H
#include "sys.h"
#include "delay.h"
#define TRIG_Send  PBout(11)
#define ECHO_Reci  PBin(10)
float Hcsr04GetLength(void );
void Hcsr04Init(void);

#endif
