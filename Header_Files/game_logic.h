#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "../Header_Files/game_vars.h"
#include "../Header_Files/constants.h"

enum colors getColorForPeice(enum peiceName name);
struct Peice createPeice(enum peiceName name, int rotation);
int getGridX(int pixelX);
int getGridY(int pixelY);
void setRotation(struct Peice* p);
int checkLosing(struct Peice p);
int checkCollision(struct Peice p);
void moveRowsDown(void *Board, int numRows, int numCols, int rowNum, size_t elementSize);
void checkRows();
void lockPiece(struct Peice p);

#endif