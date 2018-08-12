

MEMORY{
    flash (rx) : ORIGIN = 0x00000000, LENGTH = 32k
    sram (rwx) : ORIGIN = 0x10000000, LENGTH = 4k
}



PROVIDE(__INITIAL_SP = ORIGIN(sram) + LENGTH(sram));
PROVIDE(__VECTOR_CHECKSUM = 0
                            - __INITIAL_SP
                            - (reset + 1)
                            - (NMI + 1)
                            - (HardFault + 1));


PROVIDE(I2C0     = 0x40000000);
PROVIDE(TMR16B0  = 0x4000C000);
PROVIDE(TMR16B1  = 0x40010000);
PROVIDE(TMR32B0  = 0x40014000);
PROVIDE(TMR32B1  = 0x40018000);
PROVIDE(ADC      = 0x4001C000);
PROVIDE(IOCON    = 0x40044000);
PROVIDE(SYSCON   = 0x40048000);
PROVIDE(GPIO0    = 0x50000000);
PROVIDE(GPIO1    = 0x50010000);
PROVIDE(SYST     = 0xE000E010);
PROVIDE(ISER     = 0xE000E100); 
PROVIDE(ICER     = 0xE000E180); 

SECTIONS {
    .text : {
        . = 0x00000000;
        *(.vector);
        . = ALIGN(4);
        *(.text);
    } > flash

    .init_array : {
        . = ALIGN(4);
        *(.init_array);
    } > flash

    .rodata : {
        . = ALIGN(4);
        *(.rodata);
    } > flash

    .data : {
        . = 0x00000000;
        *(.data);
    } > sram AT > flash

    .bss : {
        . = ALIGN(4);
        *(.bss);
    } > sram

    __DATA_LMA = LOADADDR(.data);
    __DATA_VMA = ADDR(.data);
    __DATA_SIZE = SIZEOF(.data);
    __DATA_END = __DATA_VMA + __DATA_SIZE; 

    __BSS_VMA = ADDR(.bss);
    __BSS_SIZE = SIZEOF(.bss);
    __BSS_END = __BSS_VMA + __BSS_SIZE;

    __INIT_VMA = ADDR(.init_array);
    __INIT_END = ADDR(.init_array) + SIZEOF(.init_array);
    
}

ENTRY (vector)