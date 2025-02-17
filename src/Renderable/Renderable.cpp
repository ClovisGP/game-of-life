#include "../../include/Renderable/Renderable.hpp"

Renderable::Renderable(int positionX, int positionY, int width, int height) : _positionX(positionX), _positionY(positionY), _width(width), _height(height)
{
}

int Renderable::displayAText(SDL_Renderer *renderer, TTF_Font *font, SDL_Rect *rectToChoose, const char *textStr, SDL_Color textColor)
{
    SDL_Surface *surface = TTF_RenderText_Solid(font, textStr, textColor);
    if (!surface)
    {
        std::cerr << "Failed to create text surface: " << TTF_GetError() << std::endl;
        return (ERROR_CODE);
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (!texture)
    {
        std::cerr << "Failed to create text texture: " << SDL_GetError() << std::endl;
        return (ERROR_CODE);
    }

    SDL_RenderCopy(renderer, texture, nullptr, rectToChoose);
    SDL_DestroyTexture(texture);
    return (EXIT_SUCCESS);
}

int Renderable::init()
{
    std::cerr << "This method init is not implemented." << std::endl;
    return EXIT_SUCCESS;
}

void Renderable::render(SDL_Renderer *renderer)
{
    std::cerr << "This method render is not implemented." << std::endl;
}

void Renderable::handleEvent(const SDL_Event &event)
{
    std::cerr << "This method handleEvent is not implemented." << std::endl;
}