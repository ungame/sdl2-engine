#include <SDL2/SDL.h>
#include "DeltaTime.hpp"

DeltaTime* DeltaTime::_deltaTime = nullptr;

DeltaTime::DeltaTime()
{
    _frameTime = 0.0f;
    _lastFrame = 0.0f;
}

void DeltaTime::Tick()
{
    float tick = SDL_GetTicks();
    _frameTime = tick - _lastFrame;
    _lastFrame = tick;
}

float DeltaTime::GetDeltaTime()
{
    float dt = _frameTime * (FPS_TARGET / SEC_TO_MS);
    if (dt > DT_TARGET)
        return DT_TARGET;
    return dt;
}

