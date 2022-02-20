#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <string>
#include "Time.hpp"
#include "Sprite.hpp"
#include "Asset.hpp"

class Animation
{
    public:
        Animation(std::string name, Sprite* sprite, double frameInterval, bool repeat);
        void Reset();
        void Animate(SDL_Renderer* renderer, Asset* asset, int x, int y, int scale = 1, SDL_RendererFlip flip = SDL_FLIP_NONE);
        void Destroy();

    public:
        inline std::string GetName() { return _name; }
        inline int Animated() { return _animated; }

    private:
        std::string _name;
        Sprite* _sprite;
        int _currentFrame;
        Time* _frameStarted;
        double _frameInterval;
        bool _isStarted;
        bool _repeat;
        int _animated;

    private:
        void next();
};

#endif
