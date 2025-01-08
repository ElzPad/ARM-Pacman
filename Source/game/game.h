#ifndef GAME_H
#define GAME_H

typedef enum {
    GAME_STATE_START = 0,
    GAME_STATE_PLAYING,      // The game is being played
    GAME_STATE_PAUSED,       // The game is paused
    GAME_STATE_GAME_OVER,    // The game is over
    GAME_STATE_EXIT          // The game is exiting
} GameState;

typedef struct {
    GameState currentState;  // Current state of the game
    int score;               // Player's current score
    int lives;               // Remaining lives
    short int time;          // Remaining time
} Game;

void GameInit();
void UpdateSeconds();
void Draw();
void DrawTime(short int);

#endif