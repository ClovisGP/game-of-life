#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "Renderable.hpp"
#include <functional>

class Button : public Renderable
{
public:
    Button(int positionX, int positionY, int width, int height, std::function<void()> onClick);
    ~Button();

    void click();
    void render(SDL_Renderer *renderer, TTF_Font *font, const char *text, const SDL_Color textColor, const SDL_Color color = SDL_Color{255, 255, 255, 255});
    void handleEvent(const SDL_Event &event);

private:
    SDL_Rect _rect;
    std::function<void()> _onClick;
    bool _isHovered;
};

#endif // BUTTON_HPP