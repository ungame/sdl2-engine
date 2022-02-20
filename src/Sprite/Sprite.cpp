#include <SDL2/SDL.h>
#include <vector>
#include "Sprite.hpp"

Sprite::Sprite(int width, int height)
{
    _width = width;
    _height = height;
}

void Sprite::Add(int row, int col)
{
    SDL_Rect frame;
    frame.x = _width * col;
    frame.y = _height * row;
    frame.w = _width;
    frame.h = _height;
    _frames.push_back(frame);
}

SDL_Rect Sprite::Get(int frame)
{
    if(frame >= 0 && frame < Size())
        return _frames[frame];

    SDL_Rect empty;
    return empty;
}
