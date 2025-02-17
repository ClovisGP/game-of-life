#ifndef GRID_HPP_
#define GRID_HPP_

#include "../Logic.hpp"
#include "Renderable.hpp"
#include "iostream"
#include <vector>
#include <memory>

class Grid : public Renderable
{
public:
    Grid(Logic &logic, int positionX, int positionY, int width, int height);
    ~Grid();

    void render(SDL_Renderer *renderer) override;
    void chooseCaseColor(SDL_Renderer *renderer, int population);

private:
    std::vector<std::unique_ptr<SDL_Rect>> _lines;
    std::vector<std::unique_ptr<SDL_Rect>> _columns;
    Logic &_logic;
    int _caseSize;
    const int _linesThickness = 2;
    const int _nbrLinesCol;

    int _xRelative;
    int _yRelative;
};

#endif // GRID_HPP_
