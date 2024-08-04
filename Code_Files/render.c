#include "../Header_Files/render.h"

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
