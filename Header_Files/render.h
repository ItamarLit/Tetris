#ifndef RENDER_H
#define RENDER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../Header_Files/constants.h"
#include "../Header_Files/game_vars.h"
#include <stdio.h>

void setColor(SDL_Renderer *renderer, enum colors color);
void createBackground(SDL_Renderer* renderer);
void renderPeice(SDL_Renderer* renderer, struct Peice p);
void renderBoard(SDL_Renderer* renderer);
void renderText(SDL_Renderer* renderer, const char* text, int x, int y, enum colors color);
void renderGameInfo(SDL_Renderer* renderer);
void render(struct Peice* p);

#endif