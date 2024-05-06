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
  if(P2IFG & SW2){
    P2IFG &= ~SW2;
    switch_interrupt_handler_SW2();
  }
  if(P2IFG & SW3){
    P2IFG &= ~SW3;
    switch_interrupt_handler_SW3();
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
    clearScreen(COLOR_BLUE);
    fillRectangle(15,30, 100, 100, COLOR_ORANGE);
    fillRectangle(35,50,20,20,COLOR_BLACK);
    fillRectangle(75,50,20,20,COLOR_BLACK);
    fillRectangle(35,100,58,20,COLOR_BLACK);
    fillRectangle(25,85,20,20,COLOR_BLACK);
    fillRectangle(85,85,20,20,COLOR_BLACK);
  }
}

void switch_interrupt_handler_SW2(){
  char p2 = P2IN;

  P2IES |= (p2 & switches);
  P2IES &= (p2 & ~switches);

  if(p2 & SW2){
    
  }
  else{
    clearScreen(COLOR_BLUE);
    fillRectangle(15,30,100,100, COLOR_WHITE);
    fillRectangle(35,50,20,20,COLOR_BLACK);
    fillRectangle(75,50,20,20,COLOR_BLACK);

    for(short col = 0;col < 40; col++){
      for(short row = 0; row < col; row++){
	drawPixel(25 + col, 90 + row, COLOR_YELLOW);
      }
   }
    for(short col = 0; col < 40; col++){
      for(short row = 0; row < col; row++){
	drawPixel(100 - col, 90 + row, COLOR_YELLOW);
      }
   }
    fillRectangle(screenWidth/2 - 25, 130, 50, 20, COLOR_RED);

  }
  
}

void switch_interrupt_handler_SW3(){
  char p2 = P2IN;

  P2IES |= (p2 & switches);
  P2IES &= (p2 & ~switches);

  if(p2 & SW3){
  }
  else{
    clearScreen(COLOR_BLUE);

    //basketball goal
    fillRectangle(50,70, 30, 100, COLOR_BLACK);
    fillRectangle(35,40,60,50,COLOR_WHITE);

    for(short i = 0; i < 30;i++){
      drawPixel(50+i,60, COLOR_RED);
      drawPixel(50 + i, 80, COLOR_RED);
    }
    for(short i = 0; i < 20; i++){
      drawPixel(50,60+i,COLOR_RED);
      drawPixel(80,60+i,COLOR_RED);
    }
    fillRectangle(50,80,30,5,COLOR_ORANGE);

    for(short i = 0; i <30; i++){
      drawPixel(50+i, 80 + i, COLOR_GRAY);
      drawPixel(50+i, 85+i, COLOR_GRAY);
      drawPixel(80-i,80+i,COLOR_GRAY);
      drawPixel(80-i, 85 + i, COLOR_GRAY);
    }
    for(short i = 0; i < 35; i++){
      drawPixel(50,80+i,COLOR_GRAY);
      drawPixel(80,80+i,COLOR_GRAY);
    }
    fillRectangle(50,115,30,1,COLOR_GRAY);
  }
}
