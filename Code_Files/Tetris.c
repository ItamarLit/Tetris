#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include "../Header_Files/constants.h"
#include "../Header_Files/game_vars.h"
#include "../Header_Files/game_logic.h"
#include "../Header_Files/render.h"
#include <limits.h>
#include <string.h>




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




