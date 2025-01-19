#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>

#include "./game.h"
#include "../timer/timer.h"
#include "../GLCD//GLCD.h"
#include "RIT/RIT.h"

#define ROWS 44
#define COLS 48

Point getNextGhostStep(Point start, Point goal, short int ghostMode);

static Game *GameVar = NULL;

uint8_t lifePixels[] = {
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 
0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 
0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 
0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 
0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 
1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 
1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 
1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 
0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 
0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 
0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 
0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 
0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
};

volatile uint8_t map[ROWS][COLS] = {
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
	{1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 2, 0, 2, 0, 2, 0, 1, 1, 1, 1, 1, 1, 4, 4, 4, 4, 1, 1, 1, 1, 1, 1, 0, 0, 2, 0, 2, 0, 2, 0, 1, 1, 1, 1, 1, 1, 1, 1,},
	{1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 2, 0, 2, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 2, 0, 2, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
	{0, 2, 0, 2, 0, 2, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 2, 0, 2, 0, 2, 0,},
	{2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 2, 0, 2, 0, 2, 0, 0, 2, 0, 2, 0, 2, 0, 2,},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
	{1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 2, 0, 2, 0, 2, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 2, 0, 2, 0, 2, 0, 1, 1, 1, 1, 1, 1, 1, 1,},
	{1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 4, 4, 4, 4, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,},
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

void GeneratePowerTimes() {
	int i=0;
	short int time, position;
	for (i=0; i<6; i++) {
		time = ((LPC_TIM0->TC & 0xAAAA) ^ (LPC_TIM1->TC & 0x5555)) % (60);
		GameVar->powerTimes[i] = time;
		position = ((LPC_TIM0->TC & 0x5555) ^ (LPC_TIM1->TC & 0xAAAA)) % 250;
		GameVar->powerPositions[i] = position;
	}
}

void GeneratePowerPill() {
	int i=0, j=0, position, count=0;
	
	position = GameVar->powerPositions[i] % (GameVar->pills);
	for (i=0; i<44; i++) {
		for (j=0; j<48; j++) {
			if (map[i][j] == 2) {
				if (count==position) {
					map[i][j] = 3;
					LCD_DrawRect(j*5, 50+i*5, j*5+4, 50+i*5+4, Red);
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
				LCD_DrawRect(j*5+1, 50+i*5+1, j*5+2, 50+i*5+2, Green);
			else if (map[i][j] == 3)
				LCD_DrawRect(j*5, 50+i*5, j*5+4, 50+i*5+4, Red);
		}
	}
}

void resetPacmanPosition() {
	GameVar->position.x = 22;
	GameVar->position.y = 40;
	GameVar->direction = 0;
}

void resetGhostPosition() {
	GameVar->ghostPosition.x = 22;
	GameVar->ghostPosition.y = 21;
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
	GameVar->timesEaten = 0;
	GameVar->pills = 240; 										   // Initial number of pills is 240
  GameVar->time = 60;                          // Start with 60s remaining
	resetPacmanPosition();
	resetGhostPosition();	
	GameVar->frameEven = 0;
}

int GameIsPlaying() {
	return GameVar->currentState == GAME_STATE_PLAYING;
}

void TogglePause() {
	if (GameVar->currentState == GAME_STATE_PAUSED) {
		GameVar->currentState = GAME_STATE_RESUMED;
	} else if (GameVar->currentState == GAME_STATE_PLAYING) {
		GameVar->currentState = GAME_STATE_PAUSED;
	}
}

void SetDirection(short int direction) {
	if (GameVar->currentState == GAME_STATE_PLAYING) {
		GameVar->direction = direction;
	}
}

void verifyIfEaten() {
  if (abs(GameVar->ghostPosition.x-GameVar->position.x)<3 && abs(GameVar->ghostPosition.y-GameVar->position.y)<3) {
		switch (GameVar->ghostMode) {
			case 0:
		    GameVar->timesEaten += 1;
	      GameVar->currentState = GAME_STATE_EATEN;
			  break;
			case 1:
				GameVar->score += 100;
			  GameVar->ghostTimer = 3;
			  LCD_ClearCharacter(GameVar->ghostPosition);
			  GameVar->ghostMode = 2;
		}
  }
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
			LCD_DrawImage((Point){20, 280}, 30, lifePixels);
			GeneratePowerTimes();
		  DrawPills();
			LCD_DrawCharacter(GameVar->position, GameVar->direction, GameVar->frameEven);
			enable_RIT();
    	enable_timer(2);
			GameVar->currentState = GAME_STATE_PAUSED;
		  break;
		
		case GAME_STATE_PLAYING:
			GameVar->time = GameVar->time >= 1 ? GameVar->time-1 : 0;
		  switch (GameVar->time) {
				case 45:
					LPC_TIM1->MR0 = 0x0AC4B40;
					break;
			  case 30:
					LPC_TIM1->MR0 = 0x09C4B40;
					break;
				case 15:
					LPC_TIM2->MR0 = 0x07C4B40;
					break;
				default:
					break;
			}
			LCD_DrawTime(GameVar->time);
		  LCD_DrawScore(GameVar->score);
		
			for (i=0; i<6; i++) {
				if (GameVar->time == GameVar->powerTimes[i]) {
					GeneratePowerPill();
				}
			}
			
			if (GameVar->time == 0) {
				if (GameVar->pills > 0)
					LCD_DrawGameOver();
				else
					LCD_DrawWinMessage();
				GameVar->currentState = GAME_STATE_GAME_OVER;
			}
			
			switch (GameVar->ghostMode) {
				case 1:
   				GameVar->ghostTimer--;
		  		if (GameVar->ghostTimer == 0) {
			  		GameVar->ghostMode = 0;
				  }
					break;
				case 2:
   				GameVar->ghostTimer--;
		  		if (GameVar->ghostTimer == 0) {
						resetGhostPosition();
			  		GameVar->ghostMode = 0;
				  }
					break;
				default:
				  break;
			} 
				
			break;
			
		case GAME_STATE_PAUSED:
			LCD_DrawPauseMessage();
		  break;
		
		case GAME_STATE_RESUMED:
			LCD_ClearMessage();
		
		  LCD_DrawMapRectBorders(84, 144, 155, 175, Blue);
    	LCD_DrawRect(110, 140, 129, 145, Pink);
    	LCD_DrawRect(110, 175, 129, 179, Pink);
		
   		LCD_DrawGhost(GameVar->ghostPosition, 0);
			GameVar->currentState = GAME_STATE_PLAYING;
			break;
		
		case GAME_STATE_EATEN:
		  GameVar->lives -= 1;
			LCD_DrawRect(20+35*(GameVar->lives), 280, 50+35*(GameVar->lives), 310, Black);
		  if (GameVar->lives == 0) {
				LCD_DrawGameOver();
				GameVar->currentState = GAME_STATE_GAME_OVER;
			} else {
				LCD_DrawPauseMessage();
				LCD_ClearCharacter(GameVar->position);
				LCD_ClearCharacter(GameVar->ghostPosition);
				GameVar->direction = 0;
				resetPacmanPosition();
	      resetGhostPosition();
				GameVar->currentState = GAME_STATE_PAUSED;
			}
		
		default:
			break;
	}
}

void UpdateCharacter() {
	int i=0;
	GameVar->frameEven = GameVar->frameEven-1;
	
	if (GameVar->currentState == GAME_STATE_PLAYING) {
		switch(GameVar->direction) {
			case 0:
				if (
					map[GameVar->position.y-1][GameVar->position.x] != 1 &&
				  map[GameVar->position.y-1][GameVar->position.x+1] != 1 &&
				  map[GameVar->position.y-1][GameVar->position.x+2] != 1 &&
				map[GameVar->position.y-1][GameVar->position.x] != 4 &&
				  map[GameVar->position.y-1][GameVar->position.x+1] != 4 &&
				  map[GameVar->position.y-1][GameVar->position.x+2] != 4
				) {
					LCD_ClearCharacter(GameVar->position);
					GameVar->position.y -= 1;
				}
				break;
			case 1:
				if (GameVar->position.x==47) {
					LCD_ClearCharacter(GameVar->position);
					GameVar->position.x = 0;
				} else if (
					map[GameVar->position.y][GameVar->position.x+3] != 1 &&
				  map[GameVar->position.y+1][GameVar->position.x+3] != 1 &&
				  map[GameVar->position.y+2][GameVar->position.x+3] != 1 &&
			   	map[GameVar->position.y][GameVar->position.x+3] != 4 &&
				  map[GameVar->position.y+1][GameVar->position.x+3] != 4 &&
				  map[GameVar->position.y+2][GameVar->position.x+3] != 4
				) {
					LCD_ClearCharacter(GameVar->position);
					GameVar->position.x += 1;
				}
				break;
			case 2:
				if (
					map[GameVar->position.y+3][GameVar->position.x] != 1 &&
				  map[GameVar->position.y+3][GameVar->position.x+1] != 1 &&
				  map[GameVar->position.y+3][GameVar->position.x+2] != 1 &&
				  map[GameVar->position.y+3][GameVar->position.x] != 4 &&
				  map[GameVar->position.y+3][GameVar->position.x+1] != 4 &&
				  map[GameVar->position.y+3][GameVar->position.x+2] != 4
				) {
					LCD_ClearCharacter(GameVar->position);
					GameVar->position.y += 1;
				}
				break;
			case 3:
				if (GameVar->position.x==0) {
					LCD_ClearCharacter(GameVar->position);
					GameVar->position.x = 47;
				} else if (
					map[GameVar->position.y][GameVar->position.x-1] != 1 &&
				  map[GameVar->position.y+1][GameVar->position.x-1] != 1 &&
				  map[GameVar->position.y+2][GameVar->position.x-1] != 1 &&
				  map[GameVar->position.y][GameVar->position.x-1] != 4 &&
				  map[GameVar->position.y+1][GameVar->position.x-1] != 4 &&
				  map[GameVar->position.y+2][GameVar->position.x-1] != 4
				) {
					LCD_ClearCharacter(GameVar->position);
					GameVar->position.x -= 1;
				}
				break;
			default:
				break;
		}
		LCD_DrawCharacter(GameVar->position, GameVar->direction, GameVar->frameEven);
		verifyIfEaten();
		
		// Verifica la presenza di pills nelle 9 celle occupate da Pacman
		for (i=0; i<9; i++) {
			if (map[GameVar->position.y+i/3][GameVar->position.x+i%3] == 2) {
				GameVar->score += 10;
				GameVar->pills--;
				map[GameVar->position.y+i/3][GameVar->position.x+i%3] = 0;
			} else if (map[GameVar->position.y+i/3][GameVar->position.x+i%3] == 3) {
				GameVar->ghostMode = 1;
				GameVar->ghostTimer = 15;
				GameVar->score += 50;
				GameVar->pills--;
				map[GameVar->position.y+i/3][GameVar->position.x+i%3] = 0;
			}
		}
		
		if (GameVar->pills == 0) {
			LCD_DrawWinMessage();
			GameVar->currentState = GAME_STATE_GAME_OVER;
		}
		
		if (GameVar->lives<3 && (GameVar->score > (GameVar->lives+GameVar->timesEaten)*1000)) {
			GameVar->lives += 1;
			LCD_DrawImage((Point){20+35*(GameVar->lives-1), 280}, 30, lifePixels);
		}
	}
}

void UpdateGhost() {
	Point res;
	short int i=0, j=0;
	if (GameVar->currentState==GAME_STATE_PLAYING && GameVar->ghostMode!=2) {
		for (i=GameVar->ghostPosition.y; i<GameVar->ghostPosition.y+3; i++) {
			for (j=GameVar->ghostPosition.x; j<GameVar->ghostPosition.x+3; j++) {
				if (i>0 && i<ROWS && j>0 && j<COLS) {
					switch(map[i][j]) {
						case 0:
							LCD_DrawRect(j*5, 50+i*5, j*5+4, 50+i*5+4, Black);
							break;
						case 2:
							LCD_DrawRect(j*5, 50+i*5, j*5+4, 50+i*5+4, Black);
							LCD_DrawRect(j*5+1, 50+i*5+1, j*5+2, 50+i*5+2, Green);
							break;
						case 3:
							LCD_DrawRect(j*5, 50+i*5, j*5+4, 50+i*5+4, Red);
							break;
						case 4:
							LCD_DrawRect(j*5, 50+i*5, j*5+4, 50+i*5+4, Pink);
							break;
						default:
							break;
					}
				}
			}
		}
		res = getNextGhostStep(GameVar->ghostPosition, GameVar->position, GameVar->ghostMode);
		if (res.x!=-1 && res.y!=-1)
			GameVar->ghostPosition = res;
		LCD_DrawGhost(GameVar->ghostPosition, GameVar->ghostMode);
		
		verifyIfEaten();
	}
}

int manhattanDistance(Point current, Point goal) {
  return abs(current.x - goal.x) + abs(current.y - goal.y);
}
int diagonalDistance(Point current, Point goal) {
	if (abs(current.x - goal.x) > abs(current.y - goal.y)) {
		return abs(current.x - goal.x);
	} else {
		return abs(current.y - goal.y);
	}
}

int isValid(Point pos) {
	if (pos.y<0 || pos.y>=ROWS || pos.x<0 || pos.y>=COLS) {
		return 0;
	}
	
	int res=1, i=0, newX, newY;
	
	for (i=0; i<9; i++) {
		newY = pos.y+i/3;
		newX = pos.x+i%3;
		if (newY<0 || newY/3>=ROWS || newX<0 || newX>=COLS)
			res = 0;
		else if (map[newY][newX] == 1)
			res = 0;
	}
	return res;
}

Point getNextGhostStep(Point start, Point goal, short int ghostMode) {
	Point next = start;
	short int i, directions[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
	int optimalDist = ghostMode ? INT_MIN : INT_MAX;
  
  for (i = 0; i < 4; i++) {
    Point newPos = {start.x + directions[i][1], start.y + directions[i][0]};
		if (isValid(newPos)) {
			if (ghostMode==0 && diagonalDistance(newPos, goal)<optimalDist) {
			  optimalDist = diagonalDistance(newPos, goal);
			  next = newPos;
			} else if (ghostMode==1 && diagonalDistance(newPos, goal)>optimalDist) {
			  optimalDist = diagonalDistance(newPos, goal);
			  next = newPos;
			} 
		}
	}
	return next;
}