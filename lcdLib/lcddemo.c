#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include <msp430.h>

#define SW1 BIT0
#define SW2 BIT1
#define SW3 BIT2
#define SW4 BIT3

#define switches (SW1 | SW2 | SW3 | SW4)


/** Initializes everything, clears the screen, draws "hello" and a square */
int
main()
{
  configureClocks();
  lcd_init();
  u_char width = screenWidth, height = screenHeight;

  clearScreen(COLOR_BLUE);
  
  P2REN |= switches;
  P2IE |= switches;
  P2OUT |= switches;

  or_sr(0x18);

  
}

void __interrupt_vec(PORT2_VECTOR) Port_2(){



  if(P2IFG & SW1){
    P2IFG &= ~SW1;
    switch_interrupt_handler_SW1();
  }
}


void switch_interrupt_handler_SW1(){
  char p2 = P2IN;

  P2IES |= (p2 & switches);
  P2IES &= (p2 | ~switches);

  if(p2 & SW1){
    // clearScreen(COLOR_BLUE);
  }
  else{
    fillRectangle(15,30, 100, 100, COLOR_ORANGE);
    fillRectangle(35,50,20,20,COLOR_BLACK);
    fillRectangle(75,50,20,20,COLOR_BLACK);
    fillRectangle(35,100,58,20,COLOR_BLACK);
    fillRectangle(25,85,20,20,COLOR_BLACK);
    fillRectangle(85,85,20,20,COLOR_BLACK);
  }
}
