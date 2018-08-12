#include "lpc1114.h"
#include "main.h"
#include "6x14.c"
/*
 *                                            STO           DATA
 *                                           IRQ15          IRQ15/ACK
 *         +----------------------------------+-----------+ +--------+
 *         v                                  |           | v        |
 *    +------+         +------+         +------+         +------+    |
 *    |0:    |   STA   |1,2:  | ADDR+R  |3:    | DATA    |5:    |    |
 *    | IDLE |-------->|START |-------->|ADDR  |-------->|DATA  |----+
 *    |      |  IRQ15  |      | IRQ15   |  ACK | IRQ15   |  ACK |
 *    +------+         +------+ ACK     ++-----+ ACK     +------+
 *        ^ ^             | ^            | |                   |
 *        | |       ADDR+R| |   STA      | |DATA               |DATA
 *        | |       IRQ15 | +---------+--+ |IRQ15              |IRQ15
 *        | |       NACK  v    IRQ15  |    vNACK               |NACK
 *        | |          +------+       | +------+               |
 *        | | STO      |4:    |       +-|6:*   |               |
 *        | +----------|ADDR  |         |DATA  |<--------------+
 *        |  IRQ15     |  NACK|         |  NACK|
 *        |            +------+         +------+
 *        |                       STO      |
 *        +--------------------------------+
 *                              no IRQ
 *
 *
 *     Note that NACK means different things at different times.  NACK from the
 *     address means that the addressed device is unresponsive.  A NACK from
 *     data means that the number of bytes being sent is controlled by the
 *     receiver and no more data can be sent.
 *
 *     State 7: This is not drawn.  This state can be entered from any other
 *     state except for 0.  This occurs when the data line is held low by
 *     another device.  The transfer failed and a start condition must be sent
 *     again.
 */
#define AA   (1<<2)  // Assert acknowlege flag
#define SI   (1<<3)  // I2C interrupt flag
#define STO  (1<<4)  // STOP flag
#define STA  (1<<5)  // START flag
#define I2EN (1<<6)  // I2C interface enable

extern const char top_6x14[][6];
extern const char bot_6x14[][6];

const unsigned index_to_top = 244;
const unsigned index_to_bot = 372;
const unsigned index_nums[] = {16,17,18,19,20,21,22,23,24,25}; 

int i = 0;

void trigger_display_update();
void update_buf(unsigned new_gear);

__attribute__((constructor))
void display_init() {

  SYSCON.SYSAHBCLKCTRL.IOCON  = 1;
  SYSCON.SYSAHBCLKCTRL.I2C    = 1;
  SYSCON.PRESETCTRL.I2C_RST_N = 1;

  IOCON.PIO0_5.FUNC    = 1;

  IOCON.PIO0_5.I2CMODE = 0;

  IOCON.PIO0_4.FUNC    = 1;
  IOCON.PIO0_4.I2CMODE = 0;

  I2C0.SCLH = 240;
  I2C0.SCLL = 240;
  I2C0.CONSET = I2EN;

  ISER.SETENA |= (1<<15);
}

/* DISPLAY UPDATE
 */
void trigger_display_update() {
  i = 0;
  I2C0.CONSET = STO;
  update_buf(GEAR);
  I2C0.CONSET = STA;
}

/* UPDATE SINGLE DIGIT BUFFER
 *  
 * d             : an index into top/bot_6x14[]
 * (end - start) : number of characters to write, starting at top/bot_6x14[d][0]
 */
void buffer_digit_update(unsigned d, unsigned start, unsigned end) {
  int j;
  int k = 0;
  for(j=start; j <= end; j++){
    buffer[index_to_top + j] = top_6x14[d][k];
    buffer[index_to_bot + j] = bot_6x14[d][k];
    k++;
  }
}

/* MODULO
 *
 *  num : number to mod
 *  div : number to mod by
 */
unsigned mod(unsigned num, unsigned div) {
  while (num >= div) {
    num -= div;
  }
  return num;
}

/* UPDATE BUFFER
 *
 *  new_gear : (1-21); updates the buffer and display accordingly 
 */
void update_buf(unsigned new_gear) {
  int j;
  if (new_gear < 10) {
    buffer_digit_update(index_nums[new_gear], 0, 5);
    buffer_digit_update(0,6,13);
  } else {
    
    /* DIGIT 1 */
    if (new_gear >= 10 && new_gear <= 19) {
      buffer_digit_update(index_nums[1], 0, 5);
    } else {
      buffer_digit_update(index_nums[2], 0, 5);
    }

    /* 2 spaces */
    buffer_digit_update(0,6,7);

    /* DIGIT 2 */
    unsigned d2 = mod(new_gear, 10);
    buffer_digit_update(index_nums[d2], 8, 13);

  }
}

void IRQ15() {
  
  switch(I2C0.STAT>>3) {
  case 1: /* START condition has been transmitted. */
  case 2: /* Repeated START condition has been transmitted. */
    I2C0.DAT = buffer[i] + 0;  //startup data.
    ++i;
    I2C0.CONCLR = STA | AA | SI;  //clears the control register from these bits if set.
    break;

  case 3: /* SLA+W has been transmitted; ACK has been received. */
  case 5: /* Data byte in DAT has been transmitted; ACK has been received. */

    if(i < (sizeof(buffer)/sizeof(buffer[0]))) {  //this is actually a loop that gets called until line 202 is called.
      I2C0.DAT = buffer[i];  //actual stuff to written to screen.
      ++i;
      I2C0.CONCLR = STA | STO | AA | SI; //clears the control register from these bits if set.
    }
    else {
      I2C0.CONSET = STO; //stops the transfer of data.
      I2C0.CONCLR = STA | AA | SI; //clears the control register from these bits if set.
    }
    break;

  case 4: /* SLA+W has been transmitted; NOT ACK has been received. */
  case 6: /* Data byte in DAT has been transmitted; NOT ACK has been received. */
    I2C0.CONSET = STO;
    I2C0.CONCLR = STA | AA | SI;
    break;

  case 7: /* Arbitration lost in SLA+R/W or Data bytes. */
    I2C0.CONCLR = STA | STO | AA | SI;
    break;
  }
}
