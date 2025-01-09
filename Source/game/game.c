#include <stdio.h>
#include <stdlib.h>

#include "./game.h"
#include "../timer/timer.h"
#include "../GLCD//GLCD.h"
#include "RIT/RIT.h"

static Game *GameVar = NULL;

uint16_t lifePixels[] = {
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 65120, 65120, 65120, 65120, 65120, 65120, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 0, 0, 0, 0, 0, 
0, 0, 0, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 0, 0, 0, 0, 
0, 0, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 0, 0, 0, 
0, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 0, 0, 
0, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 0, 0, 
65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 0, 
65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 0, 
65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 0, 
0, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 
0, 0, 0, 0, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 
0, 0, 0, 0, 0, 0, 0, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 
0, 0, 0, 0, 0, 0, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 
0, 0, 0, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 
65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 
65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 0, 
0, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 0, 
0, 0, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 0, 0, 
0, 0, 0, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 0, 0, 0, 
0, 0, 0, 0, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 65120, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 65120, 65120, 65120, 65120, 65120, 65120, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
};

volatile uint8_t map[44][48] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,},
	{1, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 0, 1, 1, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 0, 1,},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,},
	{1, 0, 2, 0, 2, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 1, 1, 0, 2, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 2, 0, 1,},
	{1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1,},
  {1, 0, 2, 0, 2, 0, 0, 1, 1, 1, 0, 0, 2, 0, 0, 1, 1, 1, 0, 0, 2, 0, 0, 1, 1, 0, 2, 0, 2, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 2, 0, 2, 0, 1,},
  {1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,},
	{1, 0, 2, 0, 2, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 1, 1, 1, 0, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 2, 0, 1,},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 0, 0, 0, 0, 1,},
  {1, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 0, 1, 1, 1, 0, 0, 2, 0, 2, 0, 2, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 2, 0, 1,},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,},
	{1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 2, 0, 2, 0, 0, 0, 0, 0, 0, 0, 2, 0, 2, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 2, 0, 2, 0, 1, 1, 1, 1, 1, 1, 1, 1,},
	{1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,},
	{1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 2, 0, 1, 1, 1, 1, 1, 1, 1, 1,},
	{1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,},
	{1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 0, 2, 0, 2, 0, 2, 0, 2, 0, 0, 2, 0, 2, 0, 2, 0, 1, 1, 1, 1, 1, 1, 1, 1,},
	{1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,},
	{1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 2, 0, 2, 0, 2, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 2, 0, 2, 0, 2, 0, 1, 1, 1, 1, 1, 1, 1, 1,},
	{1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 2, 0, 2, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 2, 0, 2, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
	{0, 2, 0, 2, 0, 2, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 2, 0, 2, 0, 2, 0,},
	{2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 2, 0, 2, 0, 2, 0, 0, 2, 0, 2, 0, 2, 0, 2,},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
	{1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 2, 0, 2, 0, 2, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 2, 0, 2, 0, 2, 0, 1, 1, 1, 1, 1, 1, 1, 1,},
	{1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,},
	{1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 2, 0, 2, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 2, 0, 2, 0, 1, 1, 1, 1, 1, 1, 1, 1,},
	{1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,},
	{1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 2, 0, 2, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 2, 0, 2, 0, 1, 1, 1, 1, 1, 1, 1, 1,},
	{1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,},
	{1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 2, 0, 2, 0, 2, 0, 1, 1, 1, 1, 1, 1, 0, 0, 2, 0, 1, 1, 1, 1, 1, 1, 0, 0, 2, 0, 2, 0, 2, 0, 1, 1, 1, 1, 1, 1, 1, 1,},
	{1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 2, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 2, 0, 2, 0, 1, 1, 1, 1, 1, 1, 0, 0, 2, 0, 1, 1, 1, 1, 1, 1, 0, 0, 2, 0, 2, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1,},
	{1, 0, 2, 0, 2, 0, 2, 0, 2, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 2, 0, 0, 1, 1, 1, 1, 1, 1, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 1,},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 2, 0, 2, 0, 1, 1, 1, 1, 1, 1, 0, 0, 2, 0, 1, 1, 1, 1, 1, 1, 0, 0, 2, 0, 2, 0, 2, 0, 2, 0, 0, 0, 0, 0, 0, 1,},
	{1, 0, 2, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 2, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 2, 0, 1,},
	{1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 2, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1,},
	{1, 0, 2, 0, 2, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 2, 0, 2, 0, 1,},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,},
	{1, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 1,},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,},
	{1, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 1,},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,},
};

void GeneratePowerPills() {
	int i=0, j=0, ok, positions[6], count=0;
	
	for (i=0; i<6; i++) {
		ok = 0;
		while (!ok) {
			positions[i] = (LPC_TIM0->TC & (LPC_TIM1->TC ^ 0x543)) % (240);
			ok = 1;
			for (j=0; j<i; j++)
				if (positions[i] == positions[j])
					ok = 0;
		}
	}
	disable_timer(2);
	
	for (i=0; i<44; i++) {
		for (j=0; j<48; j++) {
			if (map[i][j] == 2) {
				if (count==positions[0] || count==positions[1] || count==positions[2] || count==positions[3] || count==positions[4] || count==positions[5]) {
					map[i][j] = 3;
				}
				count++;
			}
		}
	}
	
}

void DrawPills() {
	int i=0, j=0;
	
	for (i=0; i<44; i++) {
		for (j=0; j<48; j++) {
			if (map[i][j] == 2)
				LCD_DrawRect(j*5+1, 50+i*5+1, j*5+3, 50+i*5+3, Green);
			else if (map[i][j] == 3)
				LCD_DrawRect(j*5, 50+i*5, j*5+4, 50+i*5+4, Red);
		}
	}
}

void GameInit(void) {
	int i=0, j=0;
	
	GameVar = (Game *) malloc(sizeof(Game));
	if (GameVar == NULL) {
		exit(1);
	}
	GameVar->currentState = GAME_STATE_START;    // Start game state
  GameVar->score = 0;                          // Initial score is 0
  GameVar->lives = 1;                          // Initial number of lives is 1
	GameVar->pills = 240; 										   // Initial number of pills is 240
  GameVar->time = 60;                          // Start with 60s remaining
	GameVar->positionX = 23;
	GameVar->positionY = 26;
	GameVar->direction = 0;
	GameVar->frameEven = 0;
}

void TogglePause() {
	if (GameVar->currentState == GAME_STATE_PAUSED) {
		GameVar->currentState = GAME_STATE_RESUMED;
	} else if (GameVar->currentState == GAME_STATE_PLAYING) {
		GameVar->currentState = GAME_STATE_PAUSED;
	}
}

void SetDirection(short int direction) {
	GameVar->direction = direction;
}

void UpdateSeconds() {
	int i=0, j=0, freeSpaces=0;
	
	switch (GameVar->currentState) {
		case GAME_STATE_START:
			LCD_DrawTimeLabel();
			LCD_DrawTime(GameVar->time);
			LCD_DrawScoreLabel();
			LCD_DrawScore(GameVar->score);
			LCD_DrawMap();
			LCD_DrawImage(20, 280, 30, lifePixels);
			GeneratePowerPills();
		  DrawPills();
			LCD_DrawCharacter(GameVar->positionX, GameVar->positionY, GameVar->direction, GameVar->frameEven);
			enable_RIT();
			GameVar->currentState = GAME_STATE_PAUSED;
		  break;
		
		case GAME_STATE_PLAYING:
			GameVar->time = GameVar->time >= 1 ? GameVar->time-1 : 0;
			LCD_DrawTime(GameVar->time);
		  LCD_DrawScore(GameVar->score);
			if (GameVar->time == 0) {
				if (GameVar->pills > 0)
					LCD_DrawGameOver();
				else
					LCD_DrawWinMessage();
				GameVar->currentState = GAME_STATE_GAME_OVER;
			}
			break;
			
		case GAME_STATE_PAUSED:
			LCD_DrawPauseMessage();
		  break;
		
		case GAME_STATE_RESUMED:
			LCD_ClearMessage();
			GameVar->currentState = GAME_STATE_PLAYING;
			break;			
		
		default:
			break;
	}
}

void UpdateFrames() {
	int i=0;
	GameVar->frameEven = GameVar->frameEven-1;
	
	if (GameVar->currentState == GAME_STATE_PLAYING) {
		switch(GameVar->direction) {
			case 0:
				if (
					map[GameVar->positionY-1][GameVar->positionX] != 1 &&
				  map[GameVar->positionY-1][GameVar->positionX+1] != 1 &&
				  map[GameVar->positionY-1][GameVar->positionX+2] != 1
				) {
					LCD_ClearCharacter(GameVar->positionX, GameVar->positionY);
					GameVar->positionY -= 1;
				}
				break;
			case 1:
				if (GameVar->positionX==47) {
					LCD_ClearCharacter(GameVar->positionX, GameVar->positionY);
					GameVar->positionX = 0;
				} else if (
					map[GameVar->positionY][GameVar->positionX+3] != 1 &&
				  map[GameVar->positionY+1][GameVar->positionX+3] != 1 &&
				  map[GameVar->positionY+2][GameVar->positionX+3] != 1
				) {
					LCD_ClearCharacter(GameVar->positionX, GameVar->positionY);
					GameVar->positionX += 1;
				}
				break;
			case 2:
				if (
					map[GameVar->positionY+3][GameVar->positionX] != 1 &&
				  map[GameVar->positionY+3][GameVar->positionX+1] != 1 &&
				  map[GameVar->positionY+3][GameVar->positionX+2] != 1
				) {
					LCD_ClearCharacter(GameVar->positionX, GameVar->positionY);
					GameVar->positionY += 1;
				}
				break;
			case 3:
				if (GameVar->positionX==0) {
					LCD_ClearCharacter(GameVar->positionX, GameVar->positionY);
					GameVar->positionX = 47;
				} else if (
					map[GameVar->positionY][GameVar->positionX-1] != 1 &&
				  map[GameVar->positionY+1][GameVar->positionX-1] != 1 &&
				  map[GameVar->positionY+2][GameVar->positionX-1] != 1
				) {
					LCD_ClearCharacter(GameVar->positionX, GameVar->positionY);
					GameVar->positionX -= 1;
				}
				break;
			default:
				break;
		}
		LCD_DrawCharacter(GameVar->positionX, GameVar->positionY, GameVar->direction, GameVar->frameEven);
	
		// Verifica la presenza di pills nelle 9 celle occupate da Pacman
		for (i=0; i<9; i++) {
			if (map[GameVar->positionY+i/3][GameVar->positionX+i%3] == 2) {
				GameVar->score += 10;
				GameVar->pills--;
				map[GameVar->positionY+i/3][GameVar->positionX+i%3] = 0;
			} else if (map[GameVar->positionY+i/3][GameVar->positionX+i%3] == 3) {
				GameVar->score += 50;
				GameVar->pills--;
				map[GameVar->positionY+i/3][GameVar->positionX+i%3] = 0;
			}
		}
		
		if (GameVar->pills == 0) {
			LCD_DrawWinMessage();
			GameVar->currentState = GAME_STATE_GAME_OVER;
		}
		
		
		if (GameVar->lives <3 && (GameVar->score > GameVar->lives * 1000)) {
			GameVar->lives += 1;
			LCD_DrawImage(20+35*(GameVar->lives-1), 280, 30, lifePixels);
		}
	}
}

void Draw() {
	
}