#include "lpc1114.h"

#define NULL 0

extern unsigned __DATA_LMA;
extern unsigned __DATA_VMA;
extern unsigned __DATA_END;
extern unsigned __BSS_VMA;
extern unsigned __BSS_END;
extern unsigned __INIT_VMA; 
extern unsigned __INIT_END; 
typedef void(*ctor_t)();

void setup() __attribute__((weak));
void loop() __attribute__((weak));


void reset() {
    SYSCON.MAINCLKSEL.SEL     = 0;
    SYSCON.MAINCLKUEN.ENA     = 0;
    SYSCON.MAINCLKUEN.ENA     = 1;
    SYSCON.SYSPLLCTRL.MSEL    = 4;  
    SYSCON.SYSPLLCTRL.PSEL    = 1; 
    SYSCON.SYSPLLCLKSEL.SEL   = 0;
    SYSCON.SYSPLLCLKUEN.ENA   = 0;
    SYSCON.SYSPLLCLKUEN.ENA   = 1;
    SYSCON.PDRUNCFG.SYSPLL_PD = 0;


    unsigned* from = &__DATA_LMA;
    unsigned* to   = &__DATA_VMA;
    unsigned* end  = &__DATA_END;
    while(to < end){
        *to = *from;
        ++to;
        ++from;
    }

    to  = &__BSS_VMA;
    end = &__BSS_END;
    while(to < end){
        *to = 0;
        ++to;
    }

    ctor_t* ctor_from = &__INIT_VMA;
    ctor_t* ctor_end  = &__INIT_END;
    while(ctor_from != ctor_end) {
        (*ctor_from)();
        ++ctor_from;
    }

    while(SYSCON.SYSPLLSTAT.LOCK == 0) {}

    SYSCON.MAINCLKSEL.SEL = 0x3;
    SYSCON.MAINCLKUEN.ENA = 0;
    SYSCON.MAINCLKUEN.ENA = 1;

    if(setup != NULL){
        setup();
    }
    if(loop != NULL){
        loop();
    }else{
        while(1){
            asm("wfi");
        }
    }
    
}
