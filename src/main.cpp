#include <SDL2/SDL.h>
#include "Engine.hpp"
#include "DeltaTime.hpp"

int main(int argc, char* argv[])
{
    if(!Engine::Instance()->Init())
    {
        return EXIT_FAILURE;
    }

    while(Engine::Instance()->IsRunning())
    {
        Engine::Instance()->Listen();
        Engine::Instance()->Update();
        Engine::Instance()->Draw();
        DeltaTime::Instance()->Tick();
    }

    Engine::Instance()->Quit();

    return EXIT_SUCCESS;
}
