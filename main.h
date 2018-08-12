#ifndef __MAIN_H_
#define __MAIN_H_

#define ON  1
#define OFF 0

#define PIN_9 1<<9
#define PIN_8 1<<8
#define PIN_7 1<<7
#define PIN_6 1<<6
#define PIN_5 1<<5
#define PIN_3 1<<3
#define PIN_1 1<<1

extern void trigger_display_update();
extern void rotate_to_start();
extern void rotate_to_up();
extern void rotate_to_down();
extern void servo_set_pos();
extern void gear_check();

extern unsigned GEAR;
extern unsigned stepper_movement; 
extern unsigned steps; 

#endif
