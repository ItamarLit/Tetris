#include "../Header_Files/game_logic.h"


enum colors getColorForPeice(enum peiceName name) {
    // this func maps the colors to the peice types
    switch (name) {
        case I: return Red;
        case O: return Green;
        case T: return Blue;
        case L: return Orange;
        case J: return Purple;
        case S: return Pink;
        case Z: return Gray;
        default: return Gray; 
    }
}

struct Peice createPeice(enum peiceName name, int rotation) {
    struct Peice p;
    p.name = name;
    p.rotation = rotation;
    p.x = 150;  
    p.y = 0;  
    p.color = getColorForPeice(name);  
    return p;
}

int getGridX(int pixelX) {
    int relativeX = pixelX - PLAY_AREA_X;
    int gridX = (relativeX / BLOCK_SIZE) + 1; 
    return gridX;
}

int getGridY(int pixelY){
    int gridY = (pixelY - 40) / BLOCK_SIZE + 1;
    return gridY;
}

void setRotation(struct Peice* p){
    // this func will set the rotation
    p->rotation = (p->rotation + 1) % 4;
}

int checkLosing(struct Peice p){
    // go over the peice grid to check
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (Tetrominoes[p.name][p.rotation][i][j] != 0) {
                int globalY = getGridY(p.y) + i;
                int globalX = getGridX(p.x) + j;
                // check if player loses
                if (globalY < 2 && globalY >= 0 && TetrisBoard[globalY][globalX] == 1) {
                    return TRUE;
                }
            }
        }
    }
    return FALSE;
}

int checkCollision(struct Peice p) {
    int leftMost;
    int rightMost;
    // go over the peice grid to check
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (Tetrominoes[p.name][p.rotation][i][j] != 0) {
                int globalX = getGridX(p.x) + j;
                int globalY = getGridY(p.y) + i;
                // check if at bottom
                if (globalY >= 20) {
                    return TRUE;
                }
                // check if the peice is out of bounds or is coliding
                if (globalY >= 0 && globalX >= 1 && globalX < 11 && TetrisBoard[globalY][globalX] != 0) {
                    return TRUE;
                }
                // check if we are going out of bounds
                if(globalX < 1 || globalX > 10){
                    return TRUE;
                }
                
            }
        }
    }
    return FALSE;
}

void moveRowsDown(void *Board, int numRows, int numCols, int rowNum, size_t elementSize) {
    if (rowNum < 0 || rowNum >= numRows) {
        return; 
    }

    for (int i = rowNum; i > 0; i--) {
        memcpy((char *)Board + i * numCols * elementSize, (char *)Board + (i - 1) * numCols * elementSize, numCols * elementSize);
    }

    // Clear the top row after shifting
    memset(Board, 0, numCols * elementSize);
}


void checkRows(){
    // this func will check if a row is full and will delete it
    int rowsCleared = 0;
    int cleared = 0;
    for (int i = 0; i < 20; i++)
    {
        cleared = 1;
        for (int j = 1; j < 11; j++)
        {
            // check if the row is cleared
            if(TetrisBoard[i][j] != 1){
                cleared = 0;
            }
        }
        // clear the row and the colors
        if(cleared){
            rowsCleared += 1;
            int rowNum = i;
            for (int g = 1; g < 11; g++)
            {
                TetrisBoard[rowNum][g] = 0;
                BoardColors[rowNum][g] = 0;
            }
            // move the whole board down
            moveRowsDown(TetrisBoard, 20, 12, rowNum, sizeof(int));
            moveRowsDown(BoardColors, 20, 12, rowNum, sizeof(enum colors));
            
        }
        
    }
    switch (rowsCleared)
    {
        case 0:
            score = score;
            break;
        case 1:
            score += 100;
            break;
        case 2:
            score += 300;
            break;
        case 3:
            score += 500;
            break;
        case 4:
            score += 800;
            break;
        
    }
   
}



void lockPiece(struct Peice p) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (Tetrominoes[p.name][p.rotation][i][j] != 0) {
                // adjust the p.x based on the offset of the board
                int globalX = getGridX(p.x) + j;
                int globalY = getGridY(p.y) + i; 
                if (globalY >= 0 && globalX >= 1 && globalX < 11 && globalY < 20) {
                    TetrisBoard[globalY][globalX] = 1;  
                    BoardColors[globalY][globalX] = p.color; 
                }
            }
        }
    }
}