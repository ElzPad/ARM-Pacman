#include <stdio.h>
#include <stdlib.h>

#include "./game.h"
#include "../GLCD//GLCD.h"

Game *GameVar;

void GameInit() {
  GameVar = (Game *) malloc(sizeof(Game));
	GameVar->currentState = GAME_STATE_START;  // Start game state
  GameVar->score = 0;                        // Initial score is 0
  GameVar->lives = 3;                        // Initial lives is 3
  GameVar->time = 60;                        // Start with 60s remaining
}

void UpdateSeconds() {
	if (GameVar->currentState == GAME_STATE_PLAYING) {
		GameVar->time = GameVar->time >= 1 ? GameVar->time-1 : 0;
  }
	LCD_DrawTime(GameVar->time);
}

void Draw() {
	
}