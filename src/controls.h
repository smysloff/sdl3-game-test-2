#pragma once

#include <SDL3/SDL.h>
#include "keyboard.h"

typedef struct Controls_s
{
  SDL_bool up, left, down, right;
  SDL_bool escape, space, enter, shift;
} Controls_t;

void Controls_Update(void);
