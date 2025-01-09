/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_RIT.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    RIT.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "LPC17xx.h"
#include "RIT.h"
#include "../game/game.h"
#include "../led/led.h"

/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
volatile int down_0 = 0;
volatile int down_1 = 0;
volatile int down_2 = 0;

#define N 10

int val_int;
unsigned char val_char;
int n = 0;
int i = 0;
unsigned char vect[N];
 

void RIT_IRQHandler (void)
{
	static int j_up = 0;
	static int j_down = 0;
	static int j_left = 0;
	static int j_right = 0;
	
	UpdateFrames();
	
	if((LPC_GPIO1->FIOPIN & (1<<29)) == 0){	
		/* Joytick UP pressed */
		j_up++;
		switch(j_up){
			case 1:
				SetDirection(0);
				break;
			default:
				break;
		}
	}
	else{
			j_up=0;
	}
	
	if((LPC_GPIO1->FIOPIN & (1<<28)) == 0){	
		/* Joytick RIGHT pressed */
		j_right++;
		switch(j_right){
			case 1:
				SetDirection(1);
				break;
			default:
				break;
		}
	}
	else{
			j_right=0;
	}
	
	if((LPC_GPIO1->FIOPIN & (1<<26)) == 0){	
		/* Joytick DOWN pressed */
		j_down++;
		switch(j_down){
			case 1:
				SetDirection(2);
				break;
			default:
				break;
		}
	}
	else{
			j_down=0;
	}
	
	if((LPC_GPIO1->FIOPIN & (1<<27)) == 0){	
		/* Joytick LEFT pressed */
		j_left++;
		switch(j_left){
			case 1:
				SetDirection(3);
				break;
			default:
				break;
		}
	}
	else{
			j_left=0;
	}
	
	/*************************INT0***************************/
	if(down_0 !=0){
		down_0++;
		if((LPC_GPIO2->FIOPIN & (1<<10)) == 0){
			switch(down_0){
				case 2:
					TogglePause();
					break;
				default:
					break;
			}
		}
		else {	/* button released */
			down_0=0;			
			NVIC_EnableIRQ(EINT0_IRQn);							 /* disable Button interrupts			*/
			LPC_PINCON->PINSEL4    |= (1 << 20);     /* External interrupt 0 pin selection */
		}
	} // end INT0
	
	reset_RIT();
  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
	
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
