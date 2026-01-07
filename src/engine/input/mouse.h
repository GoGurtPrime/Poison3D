#ifndef MOUSE_H
    #define MOUSE_H 1
    
    typedef enum MouseState {
        MOUSE_DISABLED,
        MOUSE_ENABLED
    } MouseState;

    typedef struct MousePosition {
        int x;
        int y;
    } MousePosition;

    // Initialize the mouse system
    void mouse_init();

    // Update the mouse position state
    void mouse_set_pos(int x, int y);

    MousePosition* get_mouse_pos();

    MouseState mouse_get_state();
#endif
