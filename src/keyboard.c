#include "keyboard.h"

Keyboard_t keyboard;

void Keyboard_KeyDownHandler(SDL_KeyboardEvent * restrict event)
{
  switch (event->keysym.sym)
  {
    case SDLK_w: keyboard.w = SDL_TRUE; break;
    case SDLK_a: keyboard.a = SDL_TRUE; break;
    case SDLK_s: keyboard.s = SDL_TRUE; break;
    case SDLK_d: keyboard.d = SDL_TRUE; break;

    case SDLK_UP:    keyboard.up    = SDL_TRUE; break;
    case SDLK_LEFT:  keyboard.left  = SDL_TRUE; break;
    case SDLK_DOWN:  keyboard.down  = SDL_TRUE; break;
    case SDLK_RIGHT: keyboard.right = SDL_TRUE; break;

    case SDLK_ESCAPE: keyboard.escape = SDL_TRUE; break;
    case SDLK_SPACE:  keyboard.space  = SDL_TRUE; break;
    case SDLK_RETURN: keyboard.enter  = SDL_TRUE; break;
    case SDLK_LSHIFT: keyboard.shift  = SDL_TRUE; break;

    default: break;
  }
}

void Keyboard_KeyUpHandler(SDL_KeyboardEvent * restrict event)
{
  switch (event->keysym.sym)
  {
    case SDLK_w: keyboard.w = SDL_FALSE; break;
    case SDLK_a: keyboard.a = SDL_FALSE; break;
    case SDLK_s: keyboard.s = SDL_FALSE; break;
    case SDLK_d: keyboard.d = SDL_FALSE; break;

    case SDLK_UP:    keyboard.up    = SDL_FALSE; break;
    case SDLK_LEFT:  keyboard.left  = SDL_FALSE; break;
    case SDLK_DOWN:  keyboard.down  = SDL_FALSE; break;
    case SDLK_RIGHT: keyboard.right = SDL_FALSE; break;

    case SDLK_ESCAPE: keyboard.escape = SDL_FALSE; break;
    case SDLK_SPACE:  keyboard.space  = SDL_FALSE; break;
    case SDLK_RETURN: keyboard.enter  = SDL_FALSE; break;
    case SDLK_LSHIFT: keyboard.shift  = SDL_FALSE; break;

    default: break;
  }
}
