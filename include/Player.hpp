#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SDL2/SDL.h>
#include <string>

#include "Asset.hpp"
#include "Sprite.hpp"
#include "Animation.hpp"
#include "Object.hpp"
#include "Time.hpp"

#define PLAYER_WALK_SPEED 1.0f
#define PLAYER_JUMP_FORCE 15.0f
#define PLAYER_JUMP_TIME 1.0f
#define GRAVITY 1.0

class Player
{
    public:
        Player(Asset* asset, std::string name, SDL_RendererFlip flip = SDL_FLIP_NONE);
        void Update();
        void Draw(SDL_Renderer* renderer);
        void Destroy();
        
    private:
        Asset* _asset;
        Object* _object;
        SDL_RendererFlip _flip;
        std::string _currentAnimation;
        int _width;
        int _height;
        int _scale;

    private:
        void setup();

    private:
        bool _isWalking;
        bool _isOnTheGround;
        float _jumpForce;
        Time* _jumpStartedAt;

        void update(float deltaTime);
};

#endif
