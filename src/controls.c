#include "controls.h"

extern Keyboard_t keyboard;

Controls_t controls;

void Controls_Update(void)
{
  controls.up    = keyboard.w || keyboard.up;
  controls.left  = keyboard.a || keyboard.left;
  controls.down  = keyboard.s || keyboard.down;
  controls.right = keyboard.d || keyboard.right;

  controls.escape = keyboard.escape;
  controls.space  = keyboard.space;
  controls.enter  = keyboard.enter;
  controls.shift  = keyboard.shift;
}
