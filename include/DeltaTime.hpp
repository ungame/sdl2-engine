#ifndef DELTATIME_HPP
#define DELTATIME_HPP

#define FPS_TARGET 60.0f
#define SEC_TO_MS  1000.0f
#define DT_TARGET  1.5f

class DeltaTime
{
    public:
        inline static DeltaTime* Instance() { return _deltaTime = _deltaTime != nullptr ? _deltaTime : new DeltaTime(); }

    public:
        void Tick();
        float GetDeltaTime();

    private:
        DeltaTime();
        static DeltaTime* _deltaTime;
        float _frameTime;
        float _lastFrame;
};

#endif
