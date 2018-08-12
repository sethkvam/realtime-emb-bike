#include "lpc1114.h"
#include "main.h"

void servo_set_pos(unsigned width) {
    TMR16B0.MR0 = TMR16B0.MR3 - width;
}

 
