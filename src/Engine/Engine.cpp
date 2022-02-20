#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

#include "Engine.hpp"
#include "Window.hpp"
#include "Time.hpp"
#include "Input.hpp"
#include "Asset.hpp"
#include "DeltaTime.hpp"

Engine* Engine::_engine = nullptr;

bool Engine::Init()
{
    if(!init())
        return false;

    if(!setup())
        return false;

    return _isRunning;
}

bool Engine::init()
{
    SDL_Log("SDL starting...");

    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "sdl init failed with error: %s", SDL_GetError());
        return false;
    }
    
    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    int imgInitted = IMG_Init(imgFlags);

    if((imgInitted&imgFlags) != imgFlags)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "sdl img init failed with error: %s", IMG_GetError());
        return false;
    }

    _window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

    if (_window == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "sdl create window failed with error: %s", SDL_GetError());
        return false;
    }

    SDL_Log("window created.");

    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_PRESENTVSYNC);

    if (_renderer == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "sdl create renderer failed with error: %s", SDL_GetError());
        return false;
    }

    SDL_Log("renderer created.");

    _isRunning = true;

    return _isRunning;
}

bool Engine::setup()
{
    _showWindowTitleInterval = 0.1;
    _showWindowTitleTime = new Time();

    Asset* assetPlayer = new Asset(_renderer, "assets/player/with_flashlight.png");

    if(assetPlayer->HasError())
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "player asset error: %s", assetPlayer->GetError().c_str());
        return false;
    }

    _player = new Player( assetPlayer, "player");

    _background = new Asset(_renderer, "assets/background/background.png");

    if(_background->HasError())
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "background asset error: %s", _background->GetError().c_str());
        return false;
    }

    return true;
}

void Engine::Listen()
{
    _isRunning = Input::Instance()->Listen();
}

void Engine::Update()
{
    update();
    
    _player->Update();
}

void Engine::update()
{
    if(Input::Instance()->IsKeyDown(SDL_SCANCODE_UP))
        SDL_Log("[UP]");
    if(Input::Instance()->IsKeyDown(SDL_SCANCODE_DOWN))
        SDL_Log("[DOWN]");
    if(Input::Instance()->IsKeyDown(SDL_SCANCODE_RIGHT))
        SDL_Log("[RIGHT]");
    if(Input::Instance()->IsKeyDown(SDL_SCANCODE_LEFT))
        SDL_Log("[LEFT]");
    if(Input::Instance()->IsMouseButtonDown(MouseButton::LEFT))
        SDL_Log("[M-LEFT]");
    if(Input::Instance()->IsMouseButtonDown(MouseButton::RIGHT))
        SDL_Log("[M-RIGHT]");

    double elapsed = Time::Since(_showWindowTitleTime);
    
    if(elapsed >= _showWindowTitleInterval)
    {
        _title = std::string(WINDOW_TITLE);
        _title += " | ";

        Time* t = new Time();
        _title += t->String();
        _title += " | ";
        
        float deltaTime = DeltaTime::Instance()->GetDeltaTime(); 
        _title += "DeltaTime=" + std::to_string(deltaTime);
        _title += " | ";
        
        SDL_Point cursor = Input::Instance()->GetCursor();
        _title += "X=" + std::to_string(cursor.x);
        _title += " | ";
        _title += "Y=" + std::to_string(cursor.y);
    }
}

void Engine::Draw()
{
    SDL_SetRenderDrawColor(_renderer, 255, 255, 255, SDL_ALPHA_TRANSPARENT);
    SDL_RenderClear(_renderer);

    SDL_SetWindowTitle(_window, _title.c_str());

    SDL_Rect bg = { 0, 0, _background->GetWidth(), _background->GetHeight() };
    _background->Draw(_renderer, &bg, 0, 0);

    _player->Draw(_renderer);

    SDL_RenderPresent(_renderer);
}

void Engine::Quit()
{
    _player->Destroy();
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    IMG_Quit();
    SDL_Quit();
    SDL_Log("SDL quit.");
}
