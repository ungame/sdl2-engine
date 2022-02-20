#ifndef ASSET_HPP
#define ASSET_HPP

#include <SDL2/SDL.h>
#include <string>

class Asset
{
    public:
        Asset(SDL_Renderer* renderer, std::string filePath);
        void Draw(SDL_Renderer* renderer, int width, int height, int x, int y, int row, int frame, int scale = 1, SDL_RendererFlip flip = SDL_FLIP_NONE);
        void Draw(SDL_Renderer* renderer, SDL_Rect* frame, int x, int y, int scale = 1, SDL_RendererFlip = SDL_FLIP_NONE);
        void Destroy();

    public:
        inline int GetWidth() { return _width; }
        inline int GetHeight() { return _height; }
        inline std::string GetError() { return _error; };
        inline bool HasError() { return _error.length() != 0; }

    private:
        SDL_Texture* _texture;
        int _width;
        int _height;
        std::string _error;

};

#endif
