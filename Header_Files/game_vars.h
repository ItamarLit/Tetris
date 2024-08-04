#ifndef GAME_VARS_H
#define GAME_VARS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../Header_Files/constants.h"


// Declare the global vars
extern int gameFlag;
extern int TetrisBoard[20][12];
extern int last_frame_time;
extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern TTF_Font * font;
extern float fallSpeed;
extern float fallTimer;
extern SDL_Texture* backgroundTexture;

extern int Tetrominoes[7][4][4][4];

enum peiceName {
    I = 0,
    O = 1,
    T = 2,
    L = 3,
    J = 4,
    S = 5,
    Z = 6
};

enum colors {
    Red = 0,
    Green = 1,
    Blue = 2,
    Purple = 3,
    Orange = 4,
    Pink = 5,
    Gray = 6,
    Black = 7,
    White = 8
};

extern enum colors BoardColors[20][12];

extern struct Peice {
    enum peiceName name;
    int rotation;
    int x, y; // top left corners
    enum colors color;
} nextP;
extern int score;


#endif