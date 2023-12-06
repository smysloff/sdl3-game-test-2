#pragma once

#include <strings.h>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h> 
#include "config.h"
#include "keyboard.h"
#include "controls.h"

typedef enum GameState
{
  GAME_STATE_INIT,
  GAME_STATE_MENU,
  GAME_STATE_PLAY,
  GAME_STATE_STOP,
  GAME_STATE_OVER,
  GAME_STATE_SIZE
} GameState;

typedef struct Game_s
{
  GameState state;
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Event event;
  TTF_Font *font;
  SDL_Texture *title;
  SDL_Texture *invite;
} Game_t;

void Game_Init(void);
void Game_Loop(void);
void Game_Quit(void);
