#ifndef GAME_H
#define GAME_H

#include <stdint.h>

typedef enum {
    GAME_STATE_START = 0,
    GAME_STATE_PLAYING,      // The game is being played
    GAME_STATE_PAUSED,       // The game is paused
		GAME_STATE_RESUMED,			 // The game is resuming
	  GAME_STATE_EATEN,				 // Character has been eaten by pacman
    GAME_STATE_GAME_OVER,    // The game is over
    GAME_STATE_EXIT          // The game is exiting
} GameState;

typedef struct {
	  int16_t x, y;
} Point;

typedef struct {
    GameState currentState;  // Current state of the game
    short int score;         // Player's current score
    short int lives;         // Remaining lives
		short int timesEaten;
	  short int pills;				 // Remaining pills
		short int powerTimes[6]; // Time of appearance of power pills
		short int powerPositions[6];
    short int time;          // Remaining time
		Point position;
	  Point ghostPosition;
		short int ghostMode;
	  short int ghostTimer;
	  short int direction;
		short int frameEven;
} Game;

void GameInit(void);
void TogglePause(void);
void SetDirection(short int direction);
void UpdateSeconds(void);
void UpdateCharacter(void);
void UpdateGhost(void);
void Draw(void);
void DrawTime(short int);

#endif