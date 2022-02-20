#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <SDL2/SDL.h>
#include <vector>

class Sprite
{
    public:
        Sprite(int width, int height);
        void Add(int row, int col);
        SDL_Rect Get(int frame);
    
    public:
        inline std::vector<SDL_Rect> GetFrames() { return _frames; };
        inline int Size() { return _frames.size(); }
        inline void Destroy() { _frames.clear(); }

    private:
        std::vector<SDL_Rect> _frames;
        int _width;
        int _height;
};

#endif
