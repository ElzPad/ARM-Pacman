/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_timer.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    timer.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "LPC17xx.h"
#include "timer.h"
#include "../game//game.h"

/******************************************************************************
** Function name:		Timer0_IRQHandler
**
** Descriptions:		Timer/Counter 0 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
extern unsigned char led_value;					/* defined in funct_led								*/

unsigned char ledVal = 0xA5;

void TIMER0_IRQHandler (void)
{
	if (LPC_TIM0->IR & 1) {
		UpdateSeconds();
		LPC_TIM0->IR = 1;			// clear interrupt flag
	}
	else if (LPC_TIM0->IR & 2) {
		LPC_TIM0->IR = 2;
	}
	else if (LPC_TIM0->IR & 4) {
		LPC_TIM0->IR = 4;
	}
	else if (LPC_TIM0->IR & 8) {
		LPC_TIM0->IR = 8;
	}
  return;
}


/******************************************************************************
** Function name:		Timer1_IRQHandler
**
** Descriptions:		Timer/Counter 1 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void TIMER1_IRQHandler (void)
{
	if (LPC_TIM1->IR & 1) {
		LPC_TIM1->IR = 1;			// clear interrupt flag
	}
	else if (LPC_TIM1->IR & 2) {
		LPC_TIM1->IR = 2;
	}
	else if (LPC_TIM1->IR & 4) {
		LPC_TIM1->IR = 4;
	}
	else if (LPC_TIM1->IR & 8) {
		LPC_TIM1->IR = 8;
	}
  return;
}

/******************************************************************************
** Function name:		Timer2_IRQHandler
**
** Descriptions:		Timer/Counter 2 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void TIMER2_IRQHandler (void)
{
	UpdateGhost();
	
  LPC_TIM2->IR = 1;			/* clear interrupt flag */
  return;
}

/******************************************************************************
** Function name:		Timer3_IRQHandler
**
** Descriptions:		Timer/Counter 3 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void TIMER3_IRQHandler (void)
{
  LPC_TIM3->IR = 1;			/* clear interrupt flag */
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
