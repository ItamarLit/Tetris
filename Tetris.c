#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include "constants.h"
#include <limits.h>
#include <string.h>

// set the global vars
int gameFlag = FALSE;
int TetrisBoard[20][12];
int last_frame_time = 0;
// init the window to global
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
TTF_Font * font = NULL;
float fallSpeed = 0.5f; // Piece falls every 0.5 seconds
float fallTimer = 0;
SDL_Texture* backgroundTexture = NULL;
// create the arrays for the peices
int Tetrominoes[7][4][4][4] = {
    // I piece rotations
    {
        { // 0
            {0, 1, 0, 0},
            {0, 1, 0, 0},
            {0, 1, 0, 0},
            {0, 1, 0, 0}
        },
        { // 90
            {0, 0, 0, 0},
            {1, 1, 1, 1},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        },
        { // 180
            {0, 1, 0, 0},
            {0, 1, 0, 0},
            {0, 1, 0, 0},
            {0, 1, 0, 0}
        },
        { //  270
            {0, 0, 0, 0},
            {1, 1, 1, 1},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        }
    },
    // O piece rotations
    {
        { // 0
            {0, 0, 0, 0},
            {0, 1, 1, 0},
            {0, 1, 1, 0},
            {0, 0, 0, 0}
        },
        { // 90
            {0, 0, 0, 0},
            {0, 1, 1, 0},
            {0, 1, 1, 0},
            {0, 0, 0, 0}
        },
        { // 180
            {0, 0, 0, 0},
            {0, 1, 1, 0},
            {0, 1, 1, 0},
            {0, 0, 0, 0}
        },
        { //  270
            {0, 0, 0, 0},
            {0, 1, 1, 0},
            {0, 1, 1, 0},
            {0, 0, 0, 0}
        }
    },
    // T piece rotations
    {
        { // 0
            {0, 0, 0, 0},
            {1, 1, 1, 0},
            {0, 1, 0, 0},
            {0, 0, 0, 0}
        },
        { // 90
            {0, 0, 0, 0},
            {0, 1, 0, 0},
            {1, 1, 0, 0},
            {0, 1, 0, 0}
        },
        { // 180
            {0, 0, 0, 0},
            {0, 1, 0, 0},
            {1, 1, 1, 0},
            {0, 0, 0, 0}
        },
        { //  270
            {0, 0, 0, 0},
            {1, 0, 0, 0},
            {1, 1, 0, 0},
            {1, 0, 0, 0}
        }
    },
    // L piece rotations
    {
        { // 0
            {0, 1, 0, 0},
            {0, 1, 0, 0},
            {0, 1, 1, 0},
            {0, 0, 0, 0}
        },
        { // 90
            {0, 0, 0, 0},
            {0, 1, 1, 1},
            {0, 1, 0, 0},
            {0, 0, 0, 0}
        },
        { // 180
            {0, 0, 0, 0},
            {0, 1, 1, 0},
            {0, 0, 1, 0},
            {0, 0, 1, 0}
        },
        { //  270
            {0, 0, 0, 0},
            {0, 0, 1, 0},
            {1, 1, 1, 0},
            {0, 0, 0, 0}
        }
    },
    // J piece rotations
    {
        { // 0
            {0, 0, 1, 0},
            {0, 0, 1, 0},
            {0, 1, 1, 0},
            {0, 0, 0, 0}
        },
        { // 90
            {0, 0, 0, 0},
            {0, 1, 0, 0},
            {0, 1, 1, 1},
            {0, 0, 0, 0}
        },
        { // 180
            {0, 0, 0, 0},
            {0, 1, 1, 0},
            {0, 1, 0, 0},
            {0, 1, 0, 0}
        },
        { //  270
            {0, 0, 0, 0},
            {1, 1, 1, 0},
            {0, 0, 1, 0},
            {0, 0, 0, 0}
        }
    },
    // S piece rotations
    {
        { // 0
            {0, 0, 0, 0},
            {0, 1, 1, 0},
            {1, 1, 0, 0},
            {0, 0, 0, 0}
        },
        { // 90
            {0, 0, 0, 0},
            {1, 0, 0, 0},
            {1, 1, 0, 0},
            {0, 1, 0, 0}
        },
        { // 180
            {0, 0, 0, 0},
            {0, 1, 1, 0},
            {1, 1, 0, 0},
            {0, 0, 0, 0}
        },
        { //  270
            {0, 0, 0, 0},
            {1, 0, 0, 0},
            {1, 1, 0, 0},
            {0, 1, 0, 0}
        }
    },
    // Z piece rotations
    {
        { // 0
            {0, 0, 0, 0},
            {1, 1, 0, 0},
            {0, 1, 1, 0},
            {0, 0, 0, 0}
        },
        { // 90
            {0, 0, 0, 0},
            {0, 0, 1, 0},
            {0, 1, 1, 0},
            {0, 1, 0, 0}
        },
        { // 180
            {0, 0, 0, 0},
            {1, 1, 0, 0},
            {0, 1, 1, 0},
            {0, 0, 0, 0}
        },
        { //  270
            {0, 0, 0, 0},
            {0, 0, 1, 0},
            {0, 1, 1, 0},
            {0, 1, 0, 0}
        }
    }
};

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

enum colors BoardColors[20][12];

struct Peice
// this will be the struct of every peice 
{   
    enum peiceName name;
    int rotation;
    int x, y; // top left corners
    enum colors color;
};

struct Peice nextP;
int score = 0;




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


void setColor(SDL_Renderer *renderer, enum colors color) {
    switch (color) {
        case Black:
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black
            break;
        case White:
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Black
            break;
        case Red:
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red
            break;
        case Green:
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Green
            break;
        case Blue:
            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Blue
            break;
        case Purple:
            SDL_SetRenderDrawColor(renderer, 128, 0, 128, 255); // Purple
            break;
        case Orange:
            SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255); // Orange
            break;
        case Pink:
            SDL_SetRenderDrawColor(renderer, 255, 192, 203, 255); // Pink
            break;
        case Gray:
            SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255); // Gray
            break;
        default:
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Default: Black
            break;
    }
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

int initWindow(void){
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return FALSE;
    }
    if(TTF_Init() != 0){
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return FALSE;
    }
    window = SDL_CreateWindow(
        "Shmetris",              
        SDL_WINDOWPOS_CENTERED,    
        SDL_WINDOWPOS_CENTERED,    
        WINDOW_WIDTH,                      
        WINDOW_HEIGHT,                       
        SDL_WINDOW_SHOWN          
    );
    if (!window) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return FALSE;
    }
    // create the renderer
    renderer = SDL_CreateRenderer(window, -1, 0);
    if(!renderer){
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return FALSE;
    }
    // creat the font
    font = TTF_OpenFont("Font/vgasys.ttf", 25);

    return TRUE;
}


void createBackground(SDL_Renderer* renderer) {
    // create the static background
    backgroundTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, WINDOW_WIDTH, WINDOW_HEIGHT);
    SDL_SetRenderTarget(renderer, backgroundTexture);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_Rect playArea = {PLAY_AREA_X, PLAY_AREA_Y, 400, 800}; 
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); 
    SDL_RenderDrawRect(renderer, &playArea);
    SDL_Rect nextPeiceArea = {NEXT_AREA_X, NEXT_AREA_Y, 200, 200};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); 
    SDL_RenderDrawRect(renderer, &nextPeiceArea);
    SDL_Rect scoreArea = {SCORE_AREA_X, SCORE_AREA_Y, 200, 40};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); 
    SDL_RenderDrawRect(renderer, &scoreArea);
    SDL_SetRenderTarget(renderer, NULL);
}


void setRotation(struct Peice* p){
    // this func will set the rotation
    p->rotation = (p->rotation + 1) % 4;
}

void renderPeice(SDL_Renderer* renderer, struct Peice p){
    // set the render color for the whole peice
    setColor(renderer, p.color);
    // this func will render the peice into the buffer
    for (int i = 0; i < 4; i++)
    {  
        for (int j = 0; j < 4; j++)
        {   
            if(Tetrominoes[p.name][p.rotation][i][j] != 0){                
                // check if we need to render the block and render at a fixed x
                int rect_x = j * BLOCK_SIZE + p.x;
                int rect_y = i * BLOCK_SIZE + p.y;   

                SDL_Rect rect = {rect_x, rect_y, BLOCK_SIZE, BLOCK_SIZE};
                // draw the fill of the rect
                setColor(renderer, p.color);
                SDL_RenderFillRect(renderer, &rect);
                // white outline
                setColor(renderer, White);
                SDL_RenderDrawRect(renderer, &rect);

            }
        }
    }
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

void find_block_extremes(struct Peice p, int *leftmost_x, int *rightmost_x) {
  *leftmost_x = INT_MAX;
  *rightmost_x = INT_MIN;

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (Tetrominoes[p.name][p.rotation][i][j] != 0) {
        int block_x = p.x + j * BLOCK_SIZE;
        if(*leftmost_x > block_x){
            *leftmost_x = block_x;
        }
        if(*rightmost_x < block_x){
            *rightmost_x = block_x;
        }
      }
    }
  }
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

void renderBoard(SDL_Renderer* renderer) {
    for (int i = 0; i < 20; i++) {
        for (int j = 1; j <= 10; j++) {  // Iterate over playable columns
            if (TetrisBoard[i][j] != 0) {  
                int column = j - 1;
                int rect_x = (column) * BLOCK_SIZE + PLAY_AREA_X; // Correctly align to the playable area
                int rect_y = i * BLOCK_SIZE + PLAY_AREA_Y;  
                //printf("block rendered at x: %d, y: %d \n", rect_x, rect_y);
                SDL_Rect rect = {rect_x, rect_y, BLOCK_SIZE, BLOCK_SIZE};
                setColor(renderer, BoardColors[i][j]);
                SDL_RenderFillRect(renderer, &rect);
                setColor(renderer, White);
                SDL_RenderDrawRect(renderer, &rect);
            }
        }
    }
}

void setUpBoard() {
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 12; j++) {
            TetrisBoard[i][j] = 0; 
            BoardColors[i][j] = Black; 
        }
    }
}

void destroy_window(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    gameFlag = FALSE;
}

void update(struct Peice* currentPeice) {
    float delta_time = (SDL_GetTicks() - last_frame_time) / 1000.0f;
    last_frame_time = SDL_GetTicks();
    fallTimer += delta_time;
    if (fallTimer >= fallSpeed) {
        fallTimer = 0;
        currentPeice->y += BLOCK_SIZE;
        if (checkCollision(*currentPeice)) {
            currentPeice->y -= BLOCK_SIZE;
            lockPiece(*currentPeice);
            // check if we clear any rows
            // check for losing play
            if(checkLosing(*currentPeice)){
                gameFlag = FALSE;
            }
            if(gameFlag){
                // only when game running
                checkRows();
                *currentPeice = createPeice(nextP.name, nextP.rotation);
                
                nextP = createPeice((enum peiceName)(rand() % 7), 0);
            }
            checkRows();
        }
    }
}


void renderText(SDL_Renderer* renderer, const char* text, int x, int y, enum colors color) {
    SDL_Color sdlColor =  {255, 255, 255, 255};
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, sdlColor);
    if (!textSurface) {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
        return;
    }
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (!textTexture) {
        printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        SDL_FreeSurface(textSurface);
        return;
    }
    SDL_Rect renderQuad = {x, y, textSurface->w, textSurface->h};
    SDL_RenderCopy(renderer, textTexture, NULL, &renderQuad);
    SDL_DestroyTexture(textTexture);
    SDL_FreeSurface(textSurface);
}

void renderGameInfo(SDL_Renderer* renderer) {
    char scoreText[32];
    sprintf(scoreText, "Score: %d", score);
    renderText(renderer, scoreText, SCORE_AREA_X + 10, SCORE_AREA_Y + 10, White);

    renderText(renderer, "Next:", NEXT_AREA_X + 10, NEXT_AREA_Y + 10, White);
}



void render(struct Peice* p) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
    renderGameInfo(renderer);
    renderBoard(renderer);
    renderPeice(renderer, *p);
    // draw the next peice
    if(nextP.name == O){
        nextP.x = 470;
        nextP.y = 70;
    }
    else{
        nextP.x = 490;
        nextP.y = 70;
    }
    renderPeice(renderer, nextP);
    SDL_RenderPresent(renderer);
}


void process_input(struct Peice* currentPeice){
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type)
    {
        case SDL_QUIT:
            gameFlag = FALSE;
            break;
        case SDL_KEYDOWN:
            if(event.key.keysym.sym == SDLK_ESCAPE){
                gameFlag = FALSE;
            } 
            else if(event.key.keysym.sym == SDLK_UP){
                int prevRotation = currentPeice->rotation;  
                setRotation(currentPeice);  
                if (checkCollision(*currentPeice)) { 
                        currentPeice->rotation = prevRotation;  
                }
            }
            else if(event.key.keysym.sym == SDLK_RIGHT){
                int prevX = currentPeice->x; 
                currentPeice->x += BLOCK_SIZE; 
                if (checkCollision(*currentPeice)) {  
                        currentPeice->x = prevX;  
                }
              
            }
            else if(event.key.keysym.sym == SDLK_LEFT){
                int prevX = currentPeice->x; 
                currentPeice->x -= BLOCK_SIZE; 
                if (checkCollision(*currentPeice)) {  
                        currentPeice->x = prevX;  
                }
                

            }
            else if(event.key.keysym.sym == SDLK_DOWN){
                int prevY = currentPeice->y; 
                currentPeice->y += BLOCK_SIZE; 
                if (checkCollision(*currentPeice)) {  
                        currentPeice->y = prevY;  
                }
            }
            break;
        
    }

}

int main(int argc, char* argv[]) {
    gameFlag = initWindow();
    createBackground(renderer);
    struct Peice p = createPeice(O, 0);
    // set the next peice
    nextP = createPeice((enum peiceName)(rand() % 7), 0);

    while (gameFlag) {
        process_input(&p);
        update(&p);
        // check that the user hasnt lost yet
        if(gameFlag){
            render(&p);  
        }
    } 
    destroy_window();
    return 0;
}




