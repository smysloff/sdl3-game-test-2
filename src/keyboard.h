#pragma once

#include <SDL3/SDL.h>

typedef struct Keyboard_s
{
  SDL_bool w, a, s, d;
  SDL_bool up, left, down, right;
  SDL_bool escape, space, enter, shift;
} Keyboard_t;

void Keyboard_KeyDownHandler(SDL_KeyboardEvent *event);
void Keyboard_KeyUpHandler(SDL_KeyboardEvent *event);
