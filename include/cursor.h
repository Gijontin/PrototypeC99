#ifndef CURSOR_H
#define CURSOR_H

#include "raylib.h"

extern Vector2 cursorPosition;

void cursor_Update(Vector2 *cursor);
void cursor_Debug();

#endif