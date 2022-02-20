#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <SDL2/SDL.h>
#include <string>

#include "Time.hpp"
#include "Player.hpp"
#include "Asset.hpp"

class Engine
{
    public:
        inline static Engine* Instance() { return _engine = _engine != nullptr ? _engine : new Engine(); }
        inline bool IsRunning() { return _isRunning; };

    public:
        bool Init();
        void Listen();
        void Update();
        void Draw();
        void Quit();

    private:
        Engine() {};
        static Engine* _engine;
        SDL_Window* _window;
        SDL_Renderer* _renderer;
        bool _isRunning;

    private:
        std::string _title;
        double _showWindowTitleInterval;
        Time* _showWindowTitleTime;

    private:
        Player* _player;
        Asset* _background;

    private:
        bool init();
        bool setup();
        void update();
};

#endif
