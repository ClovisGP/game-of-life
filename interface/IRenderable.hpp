#ifndef IRENDERABLE_HPP_
#define IRENDERABLE_HPP_

#include "../include/SDL2Include.hpp"
#include "../include/errorCode.hpp"
#include "../include/proto.hpp"

class IRenderable
{
    public:
        virtual ~IRenderable() = default;

        virtual void render(SDL_Renderer *) = 0;
        virtual int init() = 0;
        virtual void handleEvent(const SDL_Event &event) = 0;
};

#endif /* !IRENDERABLE_HPP_ */