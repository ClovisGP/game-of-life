#include "../../include/Renderable/Button.hpp"

Button::Button(int positionX, int positionY, int width, int height, std::function<void()> onClick)
    : Renderable(positionX, positionY, width, height),
      _rect(SDL_Rect{_positionX, _positionY, _width, _height}),
      _isHovered(false),
      _onClick(onClick)
{
}

Button::~Button()
{
}

void Button::render(SDL_Renderer *renderer, TTF_Font *font, const char *text, const SDL_Color textColor, const SDL_Color color)
{

    SDL_SetRenderDrawColor(renderer,
                           _isHovered ? (color.r - 20 > 0 ? color.r - 20 : 0) : color.r,
                           _isHovered ? (color.g - 20 > 0 ? color.g - 20 : 0) : color.g,
                           _isHovered ? (color.b - 20 > 0 ? color.b - 20 : 0) : color.b,
                           color.a);
    SDL_RenderFillRect(renderer, &_rect);
    displayAText(renderer, font, &_rect, text, textColor);
}

void Button::handleEvent(const SDL_Event &event)
{
    if (event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN)
    {
        bool inside = (event.motion.x >= _rect.x && event.motion.x <= _rect.x + _rect.w && event.motion.y >= _rect.y && event.motion.y <= _rect.y + _rect.h);
        _isHovered = inside;

        if (inside && event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
        {
            if (_onClick)
                _onClick();
        }
    }
}

void Button::click()
{
    if (_onClick)
        _onClick();
}
