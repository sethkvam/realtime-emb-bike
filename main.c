#include "lpc1114.h"
#include "main.h"

#include "hall.c"
#include "front_derailer.c"
#include "ssd1306.c"
#include "stepper.c"

unsigned front_gear[18] = {0,0,1,0,0,1,2,0,1,0,2,1,1,2,2,1,2,2};
unsigned back_gear[18]  = {5,4,5,3,2,4,5,1,3,0,4,2,1,3,2,0,1,0};

// void main() {
//   GEAR = 0;
//   trigger_display_update();
// }
