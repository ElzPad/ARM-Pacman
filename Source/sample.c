/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               main.c
** Descriptions:            The GLCD application function
**
**--------------------------------------------------------------------------------------------------------
** Created by:              AVRman
** Created date:            2010-11-7
** Version:                 v1.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             Paolo Bernardi
** Modified date:           03/01/2020
** Version:                 v2.0
** Descriptions:            basic program for LCD and Touch Panel teaching
**
*********************************************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "LPC17xx.h"
#include "GLCD/GLCD.h" 
#include "game/game.h"
#include "timer/timer.h"
#include "RIT/RIT.h"

#ifdef SIMULATOR
extern uint8_t ScaleFlag; // <- ScaleFlag needs to visible in order for the emulator to find the symbol (can be placed also inside system_LPC17xx.h but since it is RO, it needs more work)
#endif


int main(void)
{
  SystemInit();  												/* System Initialization (i.e., PLL)  */
	
  NVIC_SetPriority(RIT_IRQn, 0);
	
	LCD_Initialization();
	LCD_Clear(Black);
	
	LPC_SC->PCONP |= (1 << 22);						/* Turn on TIMER2 */
	LPC_SC->PCONP |= (1 << 23);           /* Turn on TIMER3 */	
	
	init_RIT(0x0AC4B40);
	init_timer(0, 0, 0, 3, 0x17D7840);
	init_timer(1, 0, 0, 3, 0x0BC4B40);
	
	GameInit();
	BUTTON_init();												/* BUTTON Initialization              */
	
	enable_timer(0);
	enable_timer(1);
	
	LPC_SC->PCON |= 0x1;									/* power-down	mode										*/
	LPC_SC->PCON &= ~(0x2);						
	
  while (1)	
  {
		__ASM("wfi");
  }
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
