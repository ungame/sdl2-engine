#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <SDL2/SDL.h>
#include <string>
#include <map>

#include "Animation.hpp"

struct FVector
{
    FVector(float x, float y)
    {
        X = x;
        Y = y;
    }

    float X;
    float Y;
};

class Object
{
    public:
        Object(std::string name, FVector position = FVector(0.0f, 0.0f)): _name(name), _position(position) {} 
       
        inline std::string GetName() { return _name; }
        inline void AddAnimation(std::string name, Animation* animation) { _animations[name] = animation; }
        inline Animation* GetAnimation(std::string name) { return _animations[name]; }
        inline int CountAnimations(std::string name) { return _animations[name]->Animated(); }

        inline void SetX(float x) { _position.X = x; }
        inline float GetX() { return _position.X; }
        inline void SetY(float y) { _position.Y = y; }
        inline float GetY() { return _position.Y; }

    public:
        void Destroy();

    private:
        std::string _name;
        std::map<std::string, Animation*> _animations;
        FVector _position;
};

#endif
