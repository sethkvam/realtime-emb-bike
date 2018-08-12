#ifndef __LPC1114_H_
#define __LPC1114_H_

void reset();
void NMI();

#define DIR_INPUT 0
#define DIR_OUTPUT 1

struct GPIO {
    volatile       unsigned DATA[0x1000]; 
    volatile const unsigned ___[0x1000];
    volatile struct{
         unsigned PIN0  :  1;
         unsigned PIN1  :  1;
         unsigned PIN2  :  1;
         unsigned PIN3  :  1;
         unsigned PIN4  :  1;
         unsigned PIN5  :  1;
         unsigned PIN6  :  1;
         unsigned PIN7  :  1;
         unsigned PIN8  :  1;
         unsigned PIN9  :  1;
         unsigned PIN10 :  1;
         unsigned PIN11 :  1;
         unsigned _____ : 20;

    } DIR;

    volatile       unsigned IS; 
    volatile       unsigned IBE; 
    volatile       unsigned IEV; 
    volatile       unsigned IE; 
    volatile const unsigned RIS;     
    volatile const unsigned MIS; 
    volatile       unsigned IC; 

};

struct IOCON {
    volatile unsigned PIO2_6;

    volatile unsigned res1;

    volatile unsigned PIO2_0;
    volatile unsigned RESET_PIO0_0;
    volatile unsigned PIO0_1;
    volatile unsigned PIO1_8;

    volatile unsigned res2;

    volatile unsigned PIO0_2;
    volatile unsigned PIO2_7;
    volatile unsigned PIO2_8;
    volatile unsigned PIO2_1;
    volatile struct {
        unsigned FUNC :  3;
        unsigned MODE :  2;
        unsigned HIST :  1;
        unsigned      :  4;
        unsigned OD   :  1;
        unsigned      : 21;
    }PIO0_3;

    volatile struct {
        unsigned FUNC    :  3;
        unsigned         :  5;
        unsigned I2CMODE :  2;
        unsigned         : 22;
    }PIO0_4;

    volatile struct {
        unsigned FUNC    :  3;
        unsigned         :  5;
        unsigned I2CMODE :  2;
        unsigned         : 22;
    }PIO0_5;

    volatile struct {
        unsigned FUNC :  3;
        unsigned MODE :  2;
        unsigned HIST :  1;
        unsigned      :  4;
        unsigned OD   :  1;
        unsigned      : 21;
    }PIO1_9;

    volatile unsigned PIO3_4;
    volatile unsigned PIO2_4;
    volatile unsigned PIO2_5;
    volatile unsigned PIO3_5;
    volatile unsigned PIO0_6;
    volatile unsigned PIO0_7;
    volatile unsigned PIO2_9;
    volatile unsigned PIO2_10;
    volatile unsigned PIO2_2;
    volatile struct {
        unsigned FUNC :  3;
        unsigned MODE :  2;
        unsigned HIST :  1;
        unsigned      :  4;
        unsigned OD   :  1;
        unsigned      : 21;
    }PIO0_8;
    volatile unsigned PIO0_9;
    volatile unsigned SWCLK_PIO0_10;
    volatile unsigned PIO1_10;
    volatile unsigned PIO2_11;
    volatile struct {
        unsigned FUNC   :  3;
        unsigned MODE   :  2;
        unsigned HYS    :  1;
        unsigned        :  1;
        unsigned ADMODE :  1;
        unsigned        :  2;
        unsigned OD     :  1;
        unsigned        : 21;
    }R_PIO0_11;
    
    volatile unsigned R_PIO1_0;
    volatile struct {
        unsigned FUNC   :  3;
        unsigned MODE   :  2;
        unsigned HYS    :  1;
        unsigned        :  1;
        unsigned ADMODE :  1;
        unsigned        :  2;
        unsigned OD     :  1;
        unsigned        : 21;
    }R_PIO1_1;

    volatile unsigned R_PIO1_2;
    volatile unsigned PIO3_0;
    volatile unsigned PIO3_1;
    volatile unsigned PIO2_3;
    volatile unsigned SWDIO_PIO1_3;
    volatile unsigned PIO1_4;
    volatile unsigned PIO1_11;
    volatile unsigned PIO3_2;
    volatile unsigned PIO1_5;
    volatile unsigned PIO1_6;
    volatile unsigned PIO1_7;
    volatile unsigned PIO3_3;
    volatile unsigned SCK_LOC;
    volatile unsigned DSR_LOC;
    volatile unsigned DCD_LOC;
    volatile unsigned RI_LOC;
};

struct SYSCON {
    volatile unsigned SYSMEMREMAP; 
    volatile struct {
        unsigned SSP0_RST_N :  1;
        unsigned I2C_RST_N  :  1;
        unsigned SSP1_RST_N :  1;
        unsigned CAN_RST_N  :  1;
        unsigned            : 28;
    }PRESETCTRL;
    volatile struct {
        volatile unsigned MSEL :  5;
        volatile unsigned PSEL :  2;
        volatile unsigned      : 25;
    }SYSPLLCTRL;

    volatile struct {
        volatile unsigned LOCK  : 1;
        volatile unsigned      : 31;
    }SYSPLLSTAT;

    volatile unsigned res0[4];
    volatile unsigned SYSOSCCTRL; 
    volatile unsigned WDTOSCCTRL; 
    volatile unsigned IRCCTRL;
    volatile unsigned res1;
    volatile unsigned SYSRSTSTAT; 
    volatile unsigned res2[3];
    volatile struct {
        volatile unsigned SEL  :  2;
        volatile unsigned      : 30;
    }SYSPLLCLKSEL;

    volatile struct {
        volatile unsigned ENA  :  1;
        volatile unsigned      : 31;
    }SYSPLLCLKUEN;

    volatile unsigned res3[10];
    volatile struct {
        volatile unsigned SEL :  2;
        volatile unsigned     : 30;
    }MAINCLKSEL;

    volatile struct {
        volatile unsigned ENA :  1;
        volatile unsigned     : 31;
    }MAINCLKUEN;

    volatile unsigned SYSAHBCLKDIV; 
    volatile unsigned res4;
    volatile struct {
        unsigned SYS        :  1;
        unsigned ROM        :  1;
        unsigned RAM        :  1;
        unsigned FLASHREG   :  1;
        unsigned FLASHARRAY :  1;
        unsigned I2C        :  1;
        unsigned GPIO       :  1;
        unsigned CT16B0     :  1;
        unsigned CT16B1     :  1;
        unsigned CT32B0     :  1;
        unsigned CT32B1     :  1;
        unsigned SSP0       :  1;
        unsigned UART       :  1;
        unsigned ADC        :  1;
        unsigned            :  1;
        unsigned WDT        :  1;
        unsigned IOCON      :  1;
        unsigned CAN        :  1;
        unsigned SSP1       :  1;
        unsigned            : 13;
    }SYSAHBCLKCTRL;
 
    volatile unsigned res5[4];
    volatile unsigned SSP0CLKDIV; 
    volatile unsigned UARTCLKDIV; 
    volatile unsigned SSP1CLKDIV;
    volatile unsigned res6[12];
    volatile unsigned WDTCLKSEL; 
    volatile unsigned WDTCLKUEN; 
    volatile unsigned WDTCLKDIV;
    volatile unsigned res7; 
    volatile unsigned CLKOUTCLKSEL;
    volatile unsigned CLKOUTUEN; 
    volatile unsigned CLKOUTCLKDIV;
    volatile unsigned res8[5];
    volatile unsigned PIOPORCAP0; 
    volatile unsigned PIOPORCAP1;
    volatile unsigned res9[18];
    volatile unsigned BODCTRL; 
    volatile unsigned SYSTCKCAL;
    volatile unsigned res10[6];
    volatile unsigned IRQLATENCY;
    volatile unsigned NMISRC; 
    volatile unsigned res11[34];
    volatile unsigned STARTAPRP0; 
    volatile unsigned STARTERP0; 
    volatile unsigned STARTRSRP0CLR;
    volatile unsigned STARTSRP0; 
    volatile unsigned res12[8];
    volatile unsigned PDSLEEPCFG; 
    volatile unsigned PDAWAKECFG; 
    volatile struct {
        unsigned IRCOUT_PD :  1;
        unsigned IRC_PD    :  1;
        unsigned FLASH_PD  :  1;
        unsigned BOD_PD    :  1;
        unsigned ADC_PD    :  1;
        unsigned SYSOSC_PD :  1;
        unsigned WDTOSC_PD :  1;
        unsigned SYSPLL_PD :  1;
        unsigned           : 24;
    }PDRUNCFG; 

    volatile const unsigned __RESERVED_D[110];
    volatile const unsigned DEVICE_ID;
    
};

struct TMR32 { // 20.7
  volatile struct {
    unsigned MR0 :  1;
    unsigned MR1 :  1;
    unsigned MR2 :  1;
    unsigned MR3 :  1;
    unsigned CR0 :  1;
    unsigned     : 27;
  }IR;
  volatile struct {
        unsigned CEn  :  1;
        unsigned CRst :  1;
        unsigned      : 30; 

  }TCR;
  volatile unsigned TC;
  volatile unsigned PR;
  volatile unsigned PC;
  volatile struct {
    unsigned MR0I : 1;
    unsigned MR0R : 1;
    unsigned MR0S : 1;
    unsigned MR1I : 1;
    unsigned MR1R : 1;
    unsigned MR1S : 1;
    unsigned MR2I : 1;
    unsigned MR2R : 1;
    unsigned MR2S : 1;
    unsigned MR3I : 1;
    unsigned MR3R : 1;
    unsigned MR3S : 1;
    unsigned      : 20;
  }MCR;
  volatile unsigned MR0;
  volatile unsigned MR1;
  volatile unsigned MR2;
  volatile unsigned MR3;
  volatile struct {
    unsigned CAP0RE : 1;
    unsigned CAP0FE : 1;
    unsigned CAP0I  : 1;
    unsigned        : 29;
  }CCR;
  volatile unsigned CR0;
  volatile struct {
    unsigned EM0 : 1;
    unsigned EM1 : 1;
    unsigned EM2 : 1;
    unsigned EM3 : 1;
    unsigned EMC0 : 2;
    unsigned EMC1 : 2;
    unsigned EMC2 : 2;
    unsigned EMC3 : 1;
    unsigned      : 21;
  }EMR;
  volatile struct {
    unsigned CTM : 2;
    unsigned CIS : 2;
    unsigned     : 28;
  }CTCR;
  volatile struct {
    unsigned PWMEN0 : 1;
    unsigned PWMEN1 : 1;
    unsigned PWMEN2 : 1;
    unsigned PWMEN3 : 1;
    unsigned        : 28;
  }PWMC;
};

struct TMR16 {
    volatile struct {
        unsigned MR0 :  1;
        unsigned MR1 :  1;
        unsigned MR2 :  1;
        unsigned MR3 :  1;
        unsigned CR0 :  1;
        unsigned     : 27;
    }IR;

    volatile struct {
        unsigned CEn  :  1;
        unsigned CRst :  1;
        unsigned      : 30; 

    }TCR;
    volatile unsigned TC;
    volatile unsigned PR;
    volatile unsigned PC;
    volatile struct {
        unsigned MR0I :  1;
        unsigned MR0R :  1;
        unsigned MR0S :  1;
        unsigned MR1I :  1;
        unsigned MR1R :  1;
        unsigned MR1S :  1;
        unsigned MR2I :  1;
        unsigned MR2R :  1;
        unsigned MR2S :  1;
        unsigned MR3I :  1;
        unsigned MR3R :  1;
        unsigned MR3S :  1;
        unsigned      : 20;
    }MCR;

    volatile unsigned MR0;
    volatile unsigned MR1;
    volatile unsigned MR2;
    volatile unsigned MR3;
    volatile unsigned CCR;
    volatile unsigned CR0;

    //for random gap between CR0 and EMR
    volatile unsigned res0[3];
    
    volatile struct {
        unsigned EM0  :  1;
        unsigned EM1  :  1;
        unsigned EM2  :  1;
        unsigned EM3  :  1;
        unsigned EMC0 :  2;
        unsigned EMC1 :  2;
        unsigned EMC2 :  2;
        unsigned EMC3 :  2;
        unsigned      : 20; 
    }EMR;

    volatile unsigned res1[12];

    volatile unsigned CTCR;
    volatile struct {
        unsigned PWMEN0 :  1;
        unsigned PWMEN1 :  1;
        unsigned PWMEN2 :  1;
        unsigned PWMEN3 :  1;
        unsigned        : 28;
    }PWMC;
      
};


struct ADC {
    volatile struct {
        unsigned SEL    : 8;
        unsigned CLKDIV : 8;
        unsigned BURST  : 1;
        unsigned CLKS   : 3;
        unsigned        : 4;
        unsigned START  : 3;
        unsigned EDGE   : 1;
        unsigned        : 4;
    }AD0CR;

    volatile struct {
        unsigned         :  6;
        unsigned V_VREF  : 10;
        unsigned         :  8;
        unsigned CHN     :  3;
        unsigned         :  3;
        unsigned OVERRUN :  1;
        unsigned DONE    :  1;
    }AD0GDR;

    volatile unsigned _res0;
    volatile struct {
        unsigned ADINTEN  :  8;
        unsigned ADGINTEN :  1;
        unsigned          : 23;
    }AD0INTEN;

    volatile struct {
        unsigned         :  6;
        unsigned V_VREF  : 10;
        unsigned         : 14;
        unsigned OVERRUN :  1;
        unsigned DONE    :  1;
    }AD0DR0;

    volatile struct {
        unsigned         :  6;
        unsigned V_VREF  : 10;
        unsigned         : 14;
        unsigned OVERRUN :  1;
        unsigned DONE    :  1;
    }AD0DR1;

    volatile struct {
        unsigned         :  6;
        unsigned V_VREF  : 10;
        unsigned         : 14;
        unsigned OVERRUN :  1;
        unsigned DONE    :  1;
    }AD0DR2;

    volatile struct {
        unsigned         :  6;
        unsigned V_VREF  : 10;
        unsigned         : 14;
        unsigned OVERRUN :  1;
        unsigned DONE    :  1;
    }AD0DR3;

    volatile struct {
        unsigned         :  6;
        unsigned V_VREF  : 10;
        unsigned         : 14;
        unsigned OVERRUN :  1;
        unsigned DONE    :  1;
    }AD0DR4;

    volatile struct {
        unsigned         :  6;
        unsigned V_VREF  : 10;
        unsigned         : 14;
        unsigned OVERRUN :  1;
        unsigned DONE    :  1;
    }AD0DR5;

    volatile struct {
        unsigned         :  6;
        unsigned V_VREF  : 10;
        unsigned         : 14;
        unsigned OVERRUN :  1;
        unsigned DONE    :  1;
    }AD0DR6;

    volatile struct {
        unsigned         :  6;
        unsigned V_VREF  : 10;
        unsigned         : 14;
        unsigned OVERRUN :  1;
        unsigned DONE    :  1;
    }AD0DR7;

    volatile struct {
        unsigned DONE    :  8;
        unsigned OVERRUN :  8;
        unsigned ADINT   :  1;
        unsigned         : 15;
    }AD0STAT;
};

struct ISER {
    volatile unsigned SETENA : 32;
};

struct ICER {
    volatile unsigned CLRENA : 32;
};

struct SYSTICK {
    volatile struct {
        unsigned ENABLE    : 1; 
        unsigned TICKINT   : 1;
        unsigned CLKSOURCE : 1;
        unsigned           : 13;
        unsigned COUNTFLAG : 1;
        unsigned           : 15;
    }CSR ; 
    volatile struct {
        unsigned RELOAD : 24;
        unsigned        :  8;
    }RVR ; 
    volatile struct {
        unsigned CURRENT : 24;
        unsigned         :  8;
    }CVR; 
    unsigned CALIB;
};

struct I2C0 {
    volatile unsigned CONSET;
    volatile unsigned STAT; 
    volatile unsigned DAT; 
    volatile unsigned ADR0;
    volatile unsigned SCLH;
    volatile unsigned SCLL;
    volatile unsigned CONCLR;
    volatile unsigned MMCTRL;
    volatile unsigned ADR1;
    volatile unsigned ADR2;
    volatile unsigned ADR3;
    volatile unsigned DATA_BUFFER;
    volatile unsigned MASK0;
    volatile unsigned MASK1;
    volatile unsigned MASK2;
    volatile unsigned MASK3;
};


extern struct GPIO GPIO0;
extern struct GPIO GPIO1;

extern struct IOCON IOCON;
extern struct SYSCON SYSCON;
extern struct TMR16 TMR16B0;
extern struct TMR16 TMR16B1;
extern struct TMR32 TMR32B0;
extern struct TMR32 TMR32B1;

extern struct ADC ADC;
extern struct ISER ISER;
extern struct ICER ICER;
extern struct SYSTICK SYST;
extern struct I2C0 I2C0;

#endif
