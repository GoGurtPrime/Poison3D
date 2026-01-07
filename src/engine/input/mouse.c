#include "mouse.h"

MousePosition _mouse_pos = {0};

MouseState _mouse_state = MOUSE_DISABLED;

void mouse_init()
{
    _mouse_pos.x = 0;
    _mouse_pos.y = 0;
    _mouse_state = MOUSE_ENABLED;
}

void mouse_set_pos(int x, int y)
{
    _mouse_pos.x = x;
    _mouse_pos.y = y;
}

struct MousePosition* get_mouse_pos()
{
    return &_mouse_pos;
}

MouseState mouse_get_state()
{
    return _mouse_state;
}
