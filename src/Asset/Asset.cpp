#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

#include "Asset.hpp"

Asset::Asset(SDL_Renderer* renderer, std::string filePath)
{
    SDL_Surface* surface = IMG_Load(filePath.c_str());
    
    if(surface == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "sdl img load failed with error: %s", IMG_GetError());
        _error = "can't load img";
        return;
    }

    _texture = SDL_CreateTextureFromSurface(renderer, surface);

    if(_texture == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "sdl create texture from surface failed with error: %s", SDL_GetError());
        _error = "can't create texture";
        return;
    }

    SDL_Log("Surface: Width=%d, Height=%d",  surface->w, surface->h);

    _width = surface->w;
    _height = surface->h;
    
    SDL_FreeSurface(surface);
    _error = "";
}

void Asset::Draw(SDL_Renderer* renderer, int width, int height, int x, int y, int row, int frame, int scale, SDL_RendererFlip flip)
{
    SDL_Rect src;
    src.x = width * frame;
    src.y = height * row;
    src.w = width;
    src.h = height;

    Draw(renderer, &src, x, y, scale, flip);
}

void Asset::Draw(SDL_Renderer* renderer, SDL_Rect* frame, int x, int y, int scale, SDL_RendererFlip flip)
{
    SDL_Rect dst = { x, y, frame->w * scale, frame->h * scale };

    SDL_Point* center = nullptr;
    double angle = 0;

    SDL_RenderCopyEx(renderer, _texture, frame, &dst, angle, center, flip);
}

void Asset::Destroy()
{
    if(_texture != nullptr)
        SDL_DestroyTexture(_texture);
}
