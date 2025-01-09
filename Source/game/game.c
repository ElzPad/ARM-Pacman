#include <stdio.h>
#include <stdlib.h>

#include "./game.h"
#include "../GLCD//GLCD.h"

static Game *GameVar = NULL;

void GameInit(void) {
	GameVar = (Game *) malloc(sizeof(Game));
	if (GameVar == NULL) {
		exit(1);
	}
	GameVar->currentState = GAME_STATE_PLAYING;  // Start game state
  GameVar->score = 0;                          // Initial score is 0
  GameVar->lives = 1;                          // Initial number of lives is 1
	GameVar->pills = 0;												 // Initial number of pills is 240
  GameVar->time = 5;                          // Start with 60s remaining
}

void UpdateSeconds() {
	switch (GameVar->currentState) {
		case GAME_STATE_PLAYING:
			GameVar->time = GameVar->time >= 1 ? GameVar->time-1 : 0;
			LCD_DrawTime(GameVar->time);
			if (GameVar->time == 0) {
				if (GameVar->pills > 0)
					LCD_DrawGameOver();
				else
					LCD_DrawWinMessage();
				GameVar->currentState = GAME_STATE_GAME_OVER;
			}
			break;
			
		default:
			break;
	}
}

void Draw() {
	
}