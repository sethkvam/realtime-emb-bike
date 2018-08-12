
#define DEFAULT_IRQ __attribute__((weak, alias("default_irq")))

extern char __INITIAL_SP;
extern char __VECTOR_CHECKSUM;

void reset();
void NMI() DEFAULT_IRQ; //__attribute__((weak, alias("default_irq")));
void HardFault() DEFAULT_IRQ; 
void SVCall() DEFAULT_IRQ; 
void PendSV() DEFAULT_IRQ; 
void SysTick() DEFAULT_IRQ; 
void IRQ0() DEFAULT_IRQ; 
void IRQ1() DEFAULT_IRQ; 
void IRQ2() DEFAULT_IRQ; 
void IRQ3() DEFAULT_IRQ; 
void IRQ4() DEFAULT_IRQ; 
void IRQ5() DEFAULT_IRQ; 
void IRQ6() DEFAULT_IRQ; 
void IRQ7() DEFAULT_IRQ; 
void IRQ8() DEFAULT_IRQ; 
void IRQ9() DEFAULT_IRQ; 
void IRQ10() DEFAULT_IRQ; 
void IRQ11() DEFAULT_IRQ; 
void IRQ12() DEFAULT_IRQ; 
void IRQ13() DEFAULT_IRQ; 
void IRQ14() DEFAULT_IRQ; 
void IRQ15() DEFAULT_IRQ; 
void IRQ16() DEFAULT_IRQ; 
void IRQ17() DEFAULT_IRQ; 
void IRQ18() DEFAULT_IRQ; 
void IRQ19() DEFAULT_IRQ; 
void IRQ20() DEFAULT_IRQ; 
void IRQ21() DEFAULT_IRQ; 
void IRQ22() DEFAULT_IRQ; 
void IRQ23() DEFAULT_IRQ; 
void IRQ24() DEFAULT_IRQ; 
void IRQ25() DEFAULT_IRQ; 
void IRQ26() DEFAULT_IRQ; 
void IRQ27() DEFAULT_IRQ; 
void IRQ28() DEFAULT_IRQ; 
void IRQ29() DEFAULT_IRQ; 
void IRQ30() DEFAULT_IRQ; 
void IRQ31() DEFAULT_IRQ; 

static void default_irq() {}

char* vector[48] __attribute__((section(".vector"))) = {
    (char*)&__INITIAL_SP,
    (char*)(&reset)+1,
    (char*)(&NMI)+1,
    (char*)(&HardFault)+1,
    (unsigned)(0x00000000),
    (unsigned)(0x00000000),
    (unsigned)(0x00000000),
    (char*)&__VECTOR_CHECKSUM,
    (unsigned)(0x00000000),
    (unsigned)(0x00000000),
    (unsigned)(0x00000000),
    (char*)(&SVCall)+1,
    (unsigned)(0x00000000),
    (unsigned)(0x00000000),
    (char*)(&PendSV)+1,
    (char*)(&SysTick)+1,
    (char*)(&IRQ0)+1,
    (char*)(&IRQ1)+1,
    (char*)(&IRQ2)+1,
    (char*)(&IRQ3)+1,
    (char*)(&IRQ4)+1,
    (char*)(&IRQ5)+1,
    (char*)(&IRQ6)+1,
    (char*)(&IRQ7)+1,
    (char*)(&IRQ8)+1,
    (char*)(&IRQ9)+1,
    (char*)(&IRQ10)+1,
    (char*)(&IRQ11)+1,
    (char*)(&IRQ12)+1,
    (char*)(&IRQ13)+1,
    (char*)(&IRQ14)+1,
    (char*)(&IRQ15)+1,
    (char*)(&IRQ16)+1,
    (char*)(&IRQ17)+1,
    (char*)(&IRQ18)+1,
    (char*)(&IRQ19)+1,
    (char*)(&IRQ20)+1,
    (char*)(&IRQ21)+1,
    (char*)(&IRQ22)+1,
    (char*)(&IRQ23)+1,
    (char*)(&IRQ24)+1,
    (char*)(&IRQ25)+1,
    (char*)(&IRQ26)+1,
    (char*)(&IRQ27)+1,
    (char*)(&IRQ28)+1,
    (char*)(&IRQ29)+1,
    (char*)(&IRQ30)+1,
    (char*)(&IRQ31)+1,
    
};