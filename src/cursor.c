#include "cursor.h"

Vector2 cursorPosition = {0, 0};

void cursor_Update(Vector2 *cursor) {
    cursorPosition = GetMousePosition();
}

void cursor_Debug() {
    const char *text = TextFormat("Cursor: (%1.f, %1.f)", cursorPosition.x, cursorPosition.y);
    DrawText(text, 10, 10, 20, BLACK);
}