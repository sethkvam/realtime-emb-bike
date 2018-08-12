#include "lpc1114.h"
#include "main.h"
//#include "stepper.c"
//#include "ssd1306.c"

unsigned time_check = 0;
unsigned magnet_count = 0;
unsigned magnet_power = ON;

__attribute__((constructor))
 void servo_init() {
    SYSCON.SYSAHBCLKCTRL.CT16B0 = 1;
    SYSCON.SYSAHBCLKCTRL.ADC    = 1;
    SYSCON.SYSAHBCLKCTRL.IOCON  = 1;
    SYSCON.PDRUNCFG.ADC_PD      = 0;

    GPIO0.DIR.PIN1 = 1;

    IOCON.R_PIO0_11.FUNC        = 2;
    IOCON.R_PIO0_11.ADMODE      = 0;

    ADC.AD0CR.CLKDIV            = 10; // clock division
    ADC.AD0CR.SEL               =  1; // set the channel to sample from
    ADC.AD0CR.CLKS              =  0; // sets sampling to 10 bits
    ADC.AD0INTEN.ADINTEN        =  1; // sets the interrupt for ADC sampling
    ADC.AD0INTEN.ADGINTEN       =  0;

    //changed from b1 to b0
    TMR16B0.PR          =                  48;
    TMR16B0.MR3         =               20000;
    TMR16B0.MR1         =               20000;
    TMR16B0.MR0         =  TMR16B0.MR3 - 1500; 
    TMR16B0.MCR.MR3R    =                   1;
    TMR16B0.MCR.MR1I    =                   1;
    TMR16B0.PWMC.PWMEN0 =                   1;


    TMR16B0.TC      = 0; //gets incremented when pc = pr 
    TMR16B0.PC      = 0; //gets incremented per clock tick
    TMR16B0.TCR.CEn = 1;  

    ISER.SETENA |= 1<<16;
    ISER.SETENA |= 1<<24;

    GPIO0.DATA[1<<1] = 1<<1;
 }


/* GEAR UP
 *
 * Increments global GEAR, rotates derailluers up, updates display.
 */
void gear_up(){
    //move gear up in array
    //rotate_to_up();
     GEAR++;
     trigger_display_update();
}


/* GEAR DOWN
 *
 * Decrements global GEAR, rotates derailluers down, updates display.
 */
void gear_down(){
    //GEAR = 4;
    GEAR--;
    if (GEAR == 0) {
      GEAR = 1;
    } else {
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
    } else if (magnet_count < 3) {
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
    if (time_check > 50) {  // 30 == 1 second, IRQ17 interuppts every .02 sec. 
        gear_check();
        // GEAR++;
        // trigger_display_update();
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
