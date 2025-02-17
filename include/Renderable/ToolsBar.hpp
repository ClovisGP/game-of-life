#ifndef TOOLSBAR_HPP_
#define TOOLSBAR_HPP_

#include "../Logic.hpp"
#include "Renderable.hpp"
#include "Button.hpp"


class ToolsBar : public Renderable
{
public:
    ToolsBar(Logic &logic, int positionX, int positionY, int width, int height);
    ~ToolsBar();

    int init() override; // To catch the error of the font init
    void render(SDL_Renderer *renderer) override;
    void handleEvent(const SDL_Event &event) override;
    void printTest(void);

private:
    void clickXReduce();
    void clickXIncrease();
    void clickYReduce();
    void clickYIncrease();
    SDL_Rect _background;
    SDL_Rect _backgroundBorder;
    std::vector<SDL_Rect> _texts;
    std::vector<Button> _buttons;
    Logic &_logic;

    TTF_Font *_font;

    const int &_generation;
    const bool &_isRunning;
    const int &_xStart;
    const int &_yStart;
    const int &_linesNbr;
};

#endif // TOOLSBAR_HPP_
