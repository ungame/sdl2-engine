#include <SDL2/SDL.h>
#include <string>

#include "Player.hpp"
#include "Asset.hpp"
#include "Sprite.hpp"
#include "Animation.hpp"
#include "Object.hpp"
#include "DeltaTime.hpp"
#include "Input.hpp"
#include "Window.hpp"
#include "Time.hpp"

const int GROUND = WINDOW_HEIGHT - 50;

Player::Player(Asset* asset, std::string name, SDL_RendererFlip flip)
{
    _asset = asset;
    _object = new Object(name);
    _flip = flip;
    
    _isWalking = false;
    _isOnTheGround = true;
    _jumpStartedAt = nullptr;

    setup();
}


void Player::Update()
{
    float deltaTime = DeltaTime::Instance()->GetDeltaTime();

    update(deltaTime);
}

void Player::Draw(SDL_Renderer* renderer)
{
    Animation* animation = _object->GetAnimation(_currentAnimation);

    float x = _object->GetX();
    float y = _object->GetY();

    animation->Animate(renderer, _asset, x, y, _scale, _flip);
}

void Player::setup()
{   
    _scale = 2.0;
    _width = _asset->GetWidth() / 8;
    _height = _asset->GetHeight() / 8;

    _object->SetY(WINDOW_HEIGHT - _height);

    Sprite* spriteIdle = new Sprite(_width, _height);
    spriteIdle->Add(0, 0);
    spriteIdle->Add(0, 1);
    spriteIdle->Add(1, 0);
    
    double frameInterval = 0.2;
    bool repeat = true;
    Animation* idle = new Animation("idle", spriteIdle, frameInterval, repeat);

    _object->AddAnimation(idle->GetName(), idle);

    Sprite* spriteWalk = new Sprite(_width, _height);
    spriteWalk->Add(1, 1);
    spriteWalk->Add(1, 2);
    spriteWalk->Add(1, 3);
    spriteWalk->Add(1, 4);
    spriteWalk->Add(1, 5);
    spriteWalk->Add(1, 6);
    spriteWalk->Add(1, 7);
    spriteWalk->Add(2, 0);
    spriteWalk->Add(2, 1);

    frameInterval = 0.1f;
    Animation* walk = new Animation("walk", spriteWalk, frameInterval, repeat);

    _object->AddAnimation(walk->GetName(), walk);

    Sprite* spriteJump = new Sprite(_width, _height);
    // spriteJump->Add(3, 4);
    spriteJump->Add(3, 5);

    frameInterval = 0.1f;
    repeat = false;
    Animation* jump = new Animation("jump", spriteJump, frameInterval, repeat); 

    _object->AddAnimation(jump->GetName(), jump);

    Sprite* spriteFall = new Sprite(_width, _height);
    spriteFall->Add(3, 0);

    frameInterval = 0.01f;
    Animation* fall = new Animation("fall", spriteFall, frameInterval, repeat);

    _object->AddAnimation(fall->GetName(), fall);
    
    _currentAnimation = "idle";
}

void Player::Destroy()
{
    _object->Destroy();
    _asset->Destroy();
}

void Player::update(float deltaTime)
{
    _isWalking = false;

    bool jumpClicked = Input::Instance()->IsKeyDown(SDL_SCANCODE_SPACE) || Input::Instance()->IsKeyDown(SDL_SCANCODE_W) || Input::Instance()->IsKeyDown(SDL_SCANCODE_UP);

    if(jumpClicked && _isOnTheGround)
    {        
        _jumpStartedAt = new Time();
        _jumpForce = PLAYER_JUMP_FORCE;
        _isOnTheGround = false;

        _object->GetAnimation(_currentAnimation)->Reset();
        _currentAnimation = "jump";
    }

    if(!_isOnTheGround)
    {
        float y = _object->GetY() - (_jumpForce * deltaTime);
        _object->SetY(y);
        _jumpForce -= (GRAVITY * deltaTime);
   
        if(_flip == SDL_FLIP_HORIZONTAL)
        {
            float x = _object->GetX() - ((PLAYER_WALK_SPEED * 4) * deltaTime);
            _object->SetX(x);
        }
        else
        {
            float x = _object->GetX() + ((PLAYER_WALK_SPEED * 4) * deltaTime);
            _object->SetX(x);
        }

        if(Time::Since(_jumpStartedAt) >= 0.3 && _currentAnimation == "jump")
        {
            _object->GetAnimation(_currentAnimation)->Reset();
            _currentAnimation = "fall";
        }
    }

    bool isWalkingRight = Input::Instance()->IsKeyDown(SDL_SCANCODE_RIGHT) || Input::Instance()->IsKeyDown(SDL_SCANCODE_D);

    if(isWalkingRight)
    {
        _flip = SDL_FLIP_NONE;
        _isWalking = true;

        float x = _object->GetX() + (PLAYER_WALK_SPEED * deltaTime);
        _object->SetX(x);
    }
        
    bool isWalkingLeft = Input::Instance()->IsKeyDown(SDL_SCANCODE_LEFT) || Input::Instance()->IsKeyDown(SDL_SCANCODE_A);

    if(isWalkingLeft)
    {
        _flip = SDL_FLIP_HORIZONTAL;
        _isWalking = true;

        float x = _object->GetX() - (PLAYER_WALK_SPEED * deltaTime);
        _object->SetX(x);
    }


    if (_object->GetY() + (_height * _scale) >= GROUND)
    {
        _object->SetY(GROUND -  (_height * _scale));
        _isOnTheGround = true;
    }

    if(_isOnTheGround && _isWalking)
    {
        if(_currentAnimation == "idle" || _currentAnimation == "fall")
        {
            _object->GetAnimation(_currentAnimation)->Reset();
            _currentAnimation = "walk";
        }   

        // SDL_Log("Walking: X=%f", _object->GetX());
    }
    else 
    {
        if((_currentAnimation == "walk" || _currentAnimation == "fall") && _isOnTheGround)
        {
            _object->GetAnimation(_currentAnimation)->Reset();
            _currentAnimation = "idle";
        }
    }
}