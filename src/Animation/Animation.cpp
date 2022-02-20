#include "Animation.hpp"
#include "Time.hpp"
#include "Sprite.hpp"
#include "Asset.hpp"

Animation::Animation(std::string name, Sprite* sprite, double frameInterval, bool repeat)
{
    _name = name;
    _sprite = sprite;
    _frameInterval = frameInterval;
    _repeat = repeat;

    _isStarted = false;
    _currentFrame = 0;
    _frameStarted = nullptr;
}

void Animation::Animate(SDL_Renderer* renderer, Asset* asset, int x, int y, int scale, SDL_RendererFlip flip)
{
    if(!_isStarted)
    {
        _isStarted = true;
        _frameStarted = new Time(); 
    }

    SDL_Rect frame = _sprite->Get(_currentFrame);

    asset->Draw(renderer, &frame, x, y, scale, flip);

    next();
}

void Animation::next()
{
    double elapsed = Time::Since(_frameStarted);

    if(_name == "jump" || _name == "fall" || _name == "walk")
        SDL_Log("Animation=%s, StartedAt=%s, Elapsed=%lf, FrameInterval=%f, Frames=%d, CurrentFrame=%d, Animated=%d", _name.c_str(), _frameStarted->String().c_str(), elapsed, _frameInterval, _sprite->Size(), _currentFrame, _animated);

    if(elapsed < _frameInterval)
        return;

    if(_currentFrame == _sprite->Size() - 1)
    {
        if(_repeat)
        {
            _currentFrame = 0;
            _animated++;
        }
        else
        {
            _animated = 1;
        }
    } 
    else
    {
        _currentFrame++;
    }

    _frameStarted = new Time();
}

void Animation::Reset()
{
    SDL_Log("%s reseted", _name.c_str());
    _isStarted = false;
    _frameStarted = nullptr;
    _currentFrame = 0;
    _animated = 0;
}

void Animation::Destroy()
{
    if(_sprite != nullptr)
    {
        _sprite->Destroy();
        delete _sprite;
    }
}