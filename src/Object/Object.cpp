#include <string>
#include <map>

#include "Object.hpp"
#include "Animation.hpp"

void Object::Destroy()
{
    std::map<std::string, Animation*>::iterator it = _animations.begin();

    while(it != _animations.end())
    {
        it->second->Destroy();
        it++;
    }

    _animations.clear();
}