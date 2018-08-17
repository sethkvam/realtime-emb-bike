#include "lpc1114.h"
#include "main.h"

#define FRONT_0 0
#define FRONT_1 1100
#define FRONT_2 1800

unsigned front_gear[18] = {0,0,1,0,0,1,2,0,1,0,2,1,1,2,2,1,2,2};
unsigned back_gear[18]  = {5,4,5,3,2,4,5,1,3,0,4,2,1,3,2,0,1,0};

unsigned GEAR           = 0;
unsigned time_check     = 0;
unsigned magnet_count   = 0;
unsigned magnet_power   = ON;

__attribute__((constructor))
 void servo_init() {
    SYSCON.SYSAHBCLKCTRL.CT16B0 = 1;
    SYSCON.SYSAHBCLKCTRL.ADC    = 1;
    SYSCON.SYSAHBCLKCTRL.IOCON  = 1;
    SYSCON.PDRUNCFG.ADC_PD      = 0;

    GPIO0.DIR.PIN1              = 1;

    IOCON.PIO0_8.FUNC           = 2;
    IOCON.R_PIO0_11.FUNC        = 2;
    IOCON.R_PIO0_11.ADMODE      = 0;

    ADC.AD0CR.CLKDIV            = 10;
    ADC.AD0CR.SEL               =  1;
    ADC.AD0CR.CLKS              =  0; 
    ADC.AD0INTEN.ADINTEN        =  1;
    ADC.AD0INTEN.ADGINTEN       =  0;

    TMR16B0.PR                  = 48;
    TMR16B0.MR3                 = 5000;
    TMR16B0.MR1                 = 5000;
    TMR16B0.MR0                 = TMR16B0.MR3 - 1500; 
    TMR16B0.MCR.MR3R            = 1;
    TMR16B0.MCR.MR1I            = 1;
    TMR16B0.PWMC.PWMEN0         = 1;

    TMR16B0.TC                  = 0;  
    TMR16B0.PC                  = 0; 
    TMR16B0.TCR.CEn             = 0;

    GPIO0.DATA[1<<1]            = 1<<1;
 }


/* GEAR UP
 *
 * Increments global GEAR, rotates derailluers up, updates display.
 */
void gear_up(){
     GEAR++;
     if(GEAR == 18){
         GEAR = 17;
     }else{
        switch(front_gear[GEAR]){
            case 0:
                servo_set_pos(FRONT_0);
                break;
            case 1:
                servo_set_pos(FRONT_1);
                break;
            case 2:
                servo_set_pos(FRONT_2);
                break;
        }
        /* back gears */
        stepper_movement = 1;
        steps = 500;
        TMR16B0.TCR.CEn  = 0; //turn off hall clock
        TMR32B1.TC       = 0; 
        TMR32B1.TCR.CEn  = 1; //turn on stepper clock
        
     }

     ISER.SETENA |= (1<<15);
     trigger_display_update();
}


/* GEAR DOWN
 *
 * Decrements global GEAR, rotates derailluers down, updates display.
 */
void gear_down(){
    if (GEAR <= 0) {
      GEAR = 0;
    } else {
        GEAR--;
        switch(front_gear[GEAR]){
            case 0:
                servo_set_pos(FRONT_0);
                break;
            case 1:
                servo_set_pos(FRONT_1);
                break;
            case 2:
                servo_set_pos(FRONT_2);
                break;
        }
        /* back gears */
        stepper_movement = 2;
        steps = 1000;
        TMR16B0.TCR.CEn  = 0;
        TMR32B1.TC       = 0; 
        TMR32B1.TCR.CEn  = 1;

	ISER.SETENA |= (1<<15);
        trigger_display_update();
    }
}


/* GEAR CHECK 
 *
 * Check how many magnets have been read from the Hall Effect Sensor.
 * Gears up or down accordingly.
 */
void gear_check(){
    if (magnet_count > 5) {
        gear_up();
    } else if (magnet_count < 3 && magnet_count >= 1) {
        gear_down();
    }
    time_check = 0;
    magnet_count = 0;
    
}


/* IRQ16 
 *
 * triggers every 20 m/s
 */
void IRQ16() {
    ADC.AD0CR.START = 1;  // start the sampling of ADC
    TMR16B0.IR.MR1  = 1;  // resets the interrupt
    
    time_check += 1;
    if (time_check > 300) {   
        gear_check();
    }    
}


/* IRQ24
 *
 * triggers every ADC reading
 */
void IRQ24() {
   unsigned sample = ADC.AD0DR0.V_VREF;
   if (magnet_power == ON && sample <= 200) {
        magnet_count += 1;
        magnet_power = OFF;
        GPIO0.DATA[1<<1] = 1<<1;
   } else if (magnet_power == OFF && sample >= 700) {
        magnet_power = ON;
        GPIO0.DATA[1<<1] = 0;
   }
}
