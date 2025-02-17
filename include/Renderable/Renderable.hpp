#ifndef RENDERABLE_HPP_
#define RENDERABLE_HPP_

#include "../../interface/IRenderable.hpp"

class Renderable : public IRenderable
{
public:
    Renderable(int positionX, int positionY, int width, int height);
    virtual ~Renderable() = default;

    virtual int init();
    virtual void render(SDL_Renderer *renderer);
    virtual void handleEvent(const SDL_Event &event);

protected:
    int displayAText(SDL_Renderer *renderer, TTF_Font *font, SDL_Rect *rectToChoose, const char *textStr, SDL_Color textColor = {0, 0, 0, 255});

    const int _positionX;
    const int _positionY;
    const int _width;
    const int _height;
};

#endif /* !RENDERABLE_HPP_ */