#include "../../include/Renderable/Grid.hpp"

Grid::Grid(Logic &logic, int positionX, int positionY, int width, int height)
    : Renderable(positionX, positionY, width, height),
      _logic(logic),
      _nbrLinesCol(logic.getConfigLinesNbr())
{
    _caseSize = (_width - (_nbrLinesCol + 1) * _linesThickness) / (_nbrLinesCol + 1);
    const int length = (((_nbrLinesCol + 1) - 1) * (_caseSize + _linesThickness) + _linesThickness);
    _xRelative = positionX + ((width - length) / 2);
    _yRelative = positionY + ((height - length) / 2);

    for (int indexLines = 0; indexLines < (_nbrLinesCol + 1); indexLines++)
    {
        int yPos = _yRelative + indexLines * (_caseSize + _linesThickness);
        int xPos = _xRelative + indexLines * (_caseSize + _linesThickness);

        _lines.push_back(std::make_unique<SDL_Rect>(SDL_Rect{_xRelative, yPos, length, _linesThickness}));
        _columns.push_back(std::make_unique<SDL_Rect>(SDL_Rect{xPos, _yRelative, _linesThickness, length}));
    }
}

Grid::~Grid()
{
}

void Grid::render(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    for (int indexLines = 0; indexLines < _lines.size(); indexLines++)
    {
        SDL_RenderFillRect(renderer, _lines[indexLines].get());
        SDL_RenderFillRect(renderer, _columns[indexLines].get());
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    const std::vector<std::shared_ptr<Case>> &gridToDisplay = _logic.getCurrentGrid();
    const int xStart = _logic.getConfigXstart();
    const int yStart = _logic.getConfigYStart();

    for (int index = 0; index < gridToDisplay.size(); index++)
    {
        if (xStart <= gridToDisplay[index]->x && gridToDisplay[index]->x < (xStart + _nbrLinesCol) && yStart <= gridToDisplay[index]->y && gridToDisplay[index]->y < (yStart + _nbrLinesCol) && _logic.isCaseAlive(gridToDisplay[index]))
        {
            if (_logic.getConfigColorEnabled())
                chooseCaseColor(renderer, gridToDisplay[index].get()->population);
            SDL_Rect square = SDL_Rect({_xRelative + _linesThickness + ((gridToDisplay[index]->x % _nbrLinesCol) * (_caseSize + _linesThickness)),
                                        _yRelative + _linesThickness + ((gridToDisplay[index]->y % _nbrLinesCol) * (_caseSize + _linesThickness)),
                                        _caseSize,
                                        _caseSize});
            SDL_RenderFillRect(renderer, &square);
        }
    }
}

void Grid::chooseCaseColor(SDL_Renderer *renderer, int population)
{
    switch (population)
    {
    case 1:
        SDL_SetRenderDrawColor(renderer, 255, 229, 204, 255);
        break;
    case 2:
        SDL_SetRenderDrawColor(renderer, 255, 178, 102, 255);
        break;
    case 3:
        SDL_SetRenderDrawColor(renderer, 255, 153, 51, 255);
        break;
    case 4:
        SDL_SetRenderDrawColor(renderer, 255, 128, 0, 255);
        break;
    case 5:
        SDL_SetRenderDrawColor(renderer, 204, 102, 0, 255);
        break;
    case 6:
        SDL_SetRenderDrawColor(renderer, 153, 76, 0, 255);
        break;
    case 7:
        SDL_SetRenderDrawColor(renderer, 102, 51, 0, 255);
        break;
        SDL_SetRenderDrawColor(renderer, 51, 25, 0, 255);
        break;
    }
}