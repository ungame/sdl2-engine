#ifndef INPUT_HPP
#define INPUT_HPP

#include <SDL2/SDL.h>

enum MouseButton 
{
    NONE,
    LEFT,
    RIGHT
};

class Input
{
    public:
        inline static Input* Instance() { return _input = _input != nullptr ? _input : new Input(); }

    public:
        bool Listen();
        bool IsKeyDown(SDL_Scancode key);
        bool IsMouseButtonDown(MouseButton mouseButton); 
        inline SDL_Point GetCursor() { return _cursor; }

    private:
        Input();
        static Input* _input;

    private:
        const Uint8* _keyboard;
        Uint8 _mouse;
        SDL_Point _cursor;
};

#endif
