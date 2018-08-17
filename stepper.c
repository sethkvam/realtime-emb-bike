#include "lpc1114.h"
#include "main.h"

const unsigned A[4]     = {0x0fff,0,0,0};
const unsigned A_BAR[4] = {0,0,0x0fff,0};
const unsigned B[4]     = {0,0x0fff,0,0};
const unsigned B_BAR[4] = {0,0,0,0x0fff};

/* STEPPER_MOVEMENT
 *   0: To Start
 *   1: Rotate up
 *   2: Rotate down
 */
unsigned step_loc = 0;            // which of the pins to write to
unsigned step_array_pos = 0;      // part of the array to write too
unsigned step_array_pos_up = 3;   // using the step up index
unsigned step_array_pos_down = 0; // using the step up index
unsigned stepper_movement = 0;    // deciding which movement to do
unsigned steps = 0;               // how many steps to take
unsigned move_to_next_index = 3;  // when to move up an index in array


__attribute__((constructor))
 void stepper_init() {

    GPIO1.DIR.PIN9 = 1;       // A
    GPIO1.DIR.PIN8 = 1;       // A_BAR
    GPIO1.DIR.PIN7 = 1;       // B
    GPIO1.DIR.PIN6 = 1;       // B_BAR
    
    GPIO0.DIR.PIN3 = 0;       // switch
    GPIO0.IE       = PIN_3;   // unmask the interrupt
    GPIO0.IEV      = 0<<3;    // turn PIO0_3 for interrupt
    GPIO0.IS       = 0<<3;    // turn PIO_3 for edge sensitive

    IOCON.PIO0_3.MODE = 2;
    IOCON.PIO0_3.FUNC = 0;

    GPIO1.DATA[PIN_9] = 0;
    GPIO1.DATA[PIN_8] = 0; 
    GPIO1.DATA[PIN_7] = 0;
    GPIO1.DATA[PIN_6] = 0;

    SYSCON.SYSAHBCLKCTRL.CT32B1 = 1;
    SYSCON.SYSAHBCLKCTRL.IOCON  = 1;
    IOCON.R_PIO1_1.FUNC         = 3;

    TMR32B1.PR          = 48;
    TMR32B1.MR3         = 5000;
    TMR32B1.MR1         = 5000; 
    TMR32B1.MCR.MR3R    = 1;
    TMR32B1.MCR.MR1I    = 1;

    TMR32B1.TC          = 0;  
    TMR32B1.PC          = 0; 
    TMR32B1.TCR.CEn     = 0;

    GPIO0.DIR.PIN1 = 1;
    GPIO0.DATA[PIN_1] = PIN_1;
 }

 void setup(){
    TMR16B0.TCR.CEn  = 0;
    
    trigger_display_update();
    rotate_to_start();

    TMR16B0.TC = 0;
    TMR16B0.TCR.CEn  = 1;
    ISER.SETENA |= 1<<16 | 1<<15 | 1<<24 | 1<< 19;
 }


 void rotate_to_up(){
    // take the correct step
    if(step_loc == 0){
        GPIO1.DATA[PIN_9] = A[step_array_pos_up];
    }else if (step_loc == 1){
        GPIO1.DATA[PIN_8] = A_BAR[step_array_pos_up]; 
    }else if(step_loc == 2){
        GPIO1.DATA[PIN_7] = B[step_array_pos_up];
    }else if(step_loc == 3){
        GPIO1.DATA[PIN_6] = B_BAR[step_array_pos_up];
    }
    // move down the step array
    if(move_to_next_index == 0){
        if(step_array_pos_up == 0){
            step_array_pos_up = 3;
            move_to_next_index = 3;
        }else{
            step_array_pos_up--;
            move_to_next_index = 3;
        }
    }else{
        move_to_next_index--;
    }
    // move down the step location
    if(step_loc == 3){
        step_loc = 0;
    }else{
        step_loc ++;
    }
    // check if steps have finished
    if(steps == 0){
        TMR16B0.TCR.CEn  = 1; // turn on hall clock 
        TMR32B1.TCR.CEn  = 0; // turn off stepper clock
        ISER.SETENA |= 1<<15 | 1<<24 | 1<<16;
    }else{
        steps--;
    }
 }



 void rotate_to_down(){
    // take the correct step
    if(step_loc == 0){
        GPIO1.DATA[PIN_9] = A[step_array_pos_down];
    }else if (step_loc == 1){
        GPIO1.DATA[PIN_8] = A_BAR[step_array_pos_down]; 
    }else if(step_loc == 2){
        GPIO1.DATA[PIN_7] = B[step_array_pos_down];
    }else if(step_loc == 3){
        GPIO1.DATA[PIN_6] = B_BAR[step_array_pos_down];
    }
    // move down the step array
    if(move_to_next_index == 0){
        if(step_array_pos_down == 3){
            step_array_pos_down = 0;
            move_to_next_index = 3;
        }else{
            step_array_pos_down++;
            move_to_next_index = 3;
        }
    }else{
        move_to_next_index--;
    }
    // move down the step location
    if(step_loc == 3){
        step_loc = 0;
    }else{
        step_loc ++;
    }
    // check if steps have finished
    if(steps == 0){
        TMR16B0.TCR.CEn  = 1; // turn on hall clock 
        TMR32B1.TCR.CEn  = 0; // turn off stepper clock
        ISER.SETENA |= 1<<15 | 1<<24 | 1<<16;
    }else{
        steps--;
    }
 }
   
   void rotate_to_start(){
     int j = 3;
     while (GPIO0.DATA[PIN_3] != 0){

         GPIO1.DATA[PIN_9] = A[j]; 
         GPIO1.DATA[PIN_8] = A_BAR[j]; 
         GPIO1.DATA[PIN_7] = B[j]; 
         GPIO1.DATA[PIN_6] = B_BAR[j];

	 if(j == 0){
             j = 3;
         }else{
             j--;
         }  

	 for(int k=0; k < 10000; k++){}
     }
 }


void IRQ19() {
    TMR32B1.IR.MR1  = 1;
    switch(stepper_movement){
        case 0:
            break;
        case 1:
            rotate_to_up();
            break;
        case 2:
            rotate_to_down();
            break;
    }
}




 
