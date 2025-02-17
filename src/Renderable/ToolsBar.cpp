#include "../../include/Renderable/ToolsBar.hpp"

ToolsBar::ToolsBar(Logic &logic, int positionX, int positionY, int width, int height)
    : Renderable(positionX, positionY, width, height),
      _logic(logic),
      _generation(logic.getGeneration()),
      _xStart(logic.getConfigXstart()),
      _yStart(logic.getConfigYStart()),
      _linesNbr(logic.getConfigLinesNbr()),
      _isRunning(logic.getIsRunning()),
      _background(SDL_Rect{_positionX, _positionY, _width, _height}),
      _backgroundBorder(SDL_Rect{_positionX + _width - 2, _positionY, 2, _height})
{
}

ToolsBar::~ToolsBar()
{
    TTF_CloseFont(_font);
    _font = nullptr;
    TTF_Quit();
}

int ToolsBar::init() // To catch the error of the font init
{
    if (TTF_Init() == -1)
    {
        std::cerr << "Failed to initialize SDL_ttf: " << TTF_GetError() << std::endl;
        return ERROR_CODE;
    }
    _font = TTF_OpenFont("./rsc/ComicSansMS.ttf", 24);
    if (!_font)
    {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        return ERROR_CODE;
    }

    _texts.emplace_back(SDL_Rect{_positionX + _width / 4, _positionY + (_width / 20), _width / 2, _width / 10});                              // Title
    _texts.emplace_back(SDL_Rect{_positionX + _width / 10, _positionY + ((_width / 10) * 3), (_width / 2) - (_width / 10), _width / 10});     // Generation
    _texts.emplace_back(SDL_Rect{_positionX + ((_width / 2) + (_width / 40)), _positionY + ((_width / 10) * 3), (_width / 12), _width / 10}); // Generation count
    _texts.emplace_back(SDL_Rect{_positionX + (_width / 16), _positionY + ((_width / 10) * 9), (_width / 16) * 2, _width / 10});              // Label X position
    _texts.emplace_back(SDL_Rect{_positionX + ((_width / 16) * 4), _positionY + ((_width / 10) * 9), (_width / 16) * 3, _width / 10});        // X position
    _texts.emplace_back(SDL_Rect{_positionX + (_width / 16) * 9, _positionY + ((_width / 10) * 9), (_width / 16) * 2, _width / 10});          // Label y position
    _texts.emplace_back(SDL_Rect{_positionX + ((_width / 16) * 12), _positionY + ((_width / 10) * 9), (_width / 16) * 3, _width / 10});       // y position

    _buttons.emplace_back(_positionX + _width / 4, _positionY + ((_width / 10) * 5), _width / 2, _width / 10, std::bind(&Logic::manageRunning, &_logic));                                  // Launch all
    _buttons.emplace_back(_positionX + _width / 10, _positionY + ((_width / 10) * 7), (_width / 2) - (_width / 10), _width / 10, std::bind(&Logic::previousStep, &_logic));                // previous step
    _buttons.emplace_back(_positionX + ((_width / 2) + (_width / 40)), _positionY + ((_width / 10) * 7), (_width / 2) - (_width / 10), _width / 10, std::bind(&Logic::nextStep, &_logic)); // next step
    _buttons.emplace_back(_positionX + (_width / 16), _positionY + ((_width / 10) * 11), (_width / 16) * 2, _width / 10, std::bind(&ToolsBar::clickXReduce, this));                        // - X
    _buttons.emplace_back(_positionX + ((_width / 16) * 4), _positionY + ((_width / 10) * 11), (_width / 16) * 2, _width / 10, std::bind(&ToolsBar::clickXIncrease, this));                // + X
    _buttons.emplace_back(_positionX + (_width / 16) * 10, _positionY + ((_width / 10) * 11), (_width / 16) * 2, _width / 10, std::bind(&ToolsBar::clickYReduce, this));                   // - Y
    _buttons.emplace_back(_positionX + ((_width / 16) * 13), _positionY + ((_width / 10) * 11), (_width / 16) * 2, _width / 10, std::bind(&ToolsBar::clickYIncrease, this));               // + Y
    return EXIT_SUCCESS;
}

void ToolsBar::render(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 230, 230, 230, 255);
    SDL_RenderFillRect(renderer, &_background);
    SDL_SetRenderDrawColor(renderer, 75, 75, 75, 255);
    SDL_RenderFillRect(renderer, &_backgroundBorder);

    displayAText(renderer, _font, &(_texts[0]), "GAME OF LIFE");
    displayAText(renderer, _font, &(_texts[1]), "Generation:");
    displayAText(renderer, _font, &(_texts[2]), std::to_string(_generation).c_str());
    displayAText(renderer, _font, &(_texts[3]), "Grid X:");
    displayAText(renderer, _font, &(_texts[4]), std::to_string(_xStart + 1).append("-").append(std::to_string(_xStart + _linesNbr)).c_str()); // Ugly but AHHHH
    displayAText(renderer, _font, &(_texts[5]), "Grid Y:");
    displayAText(renderer, _font, &(_texts[6]), std::to_string(_yStart + 1).append("-").append(std::to_string(_yStart + _linesNbr)).c_str()); // Ugly but AHHHH

    _buttons[0].render(renderer, _font, _isRunning ? "Stop" : "Launch", SDL_Color{25, 25, 25, 255}, _isRunning ? SDL_Color{255, 153, 153, 255} : SDL_Color{153, 255, 153, 255});
    _buttons[1].render(renderer, _font, "Previous Generation", SDL_Color{25, 25, 25, 255}, _isRunning ? SDL_Color{102, 51, 0, 255} : SDL_Color{255, 204, 153, 255});
    _buttons[2].render(renderer, _font, "Next Generation", SDL_Color{25, 25, 25, 255}, _isRunning ? SDL_Color{0, 51, 102, 255} : SDL_Color{153, 204, 255, 255});
    _buttons[3].render(renderer, _font, "<", SDL_Color{25, 25, 25, 255}, SDL_Color{153, 255, 204, 255});
    _buttons[4].render(renderer, _font, ">", SDL_Color{25, 25, 25, 255}, SDL_Color{153, 255, 204, 255});
    _buttons[5].render(renderer, _font, "<", SDL_Color{25, 25, 25, 255}, SDL_Color{153, 255, 204, 255});
    _buttons[6].render(renderer, _font, ">", SDL_Color{25, 25, 25, 255}, SDL_Color{153, 255, 204, 255});
}

void ToolsBar::handleEvent(const SDL_Event &event)
{
    if (_isRunning)
    { // To disabled the two others buttons run is auto is running
        _buttons[0].handleEvent(event);
        _buttons[3].handleEvent(event);
        _buttons[4].handleEvent(event);
        _buttons[5].handleEvent(event);
        _buttons[6].handleEvent(event);
        return;
    }
    for (int indexButtons = 0; indexButtons < _buttons.size(); indexButtons++)
    {
        _buttons[indexButtons].handleEvent(event);
    }
}

void ToolsBar::printTest()
{
    std::cout << "Test" << std::endl;
}

void ToolsBar::clickXReduce()
{
    if ((_logic.getConfigXstart() - _logic.getConfigLinesNbr()) >= 0)
        _logic.setConfigXstart(_logic.getConfigXstart() - _logic.getConfigLinesNbr());
}

void ToolsBar::clickXIncrease()
{
    _logic.setConfigXstart(_logic.getConfigXstart() + _logic.getConfigLinesNbr());
}
void ToolsBar::clickYReduce()
{
    if ((_logic.getConfigYStart() - _logic.getConfigLinesNbr()) >= 0)
        _logic.setConfigYStart(_logic.getConfigYStart() - _logic.getConfigLinesNbr());
}

void ToolsBar::clickYIncrease()
{
    _logic.setConfigYStart(_logic.getConfigYStart() + _logic.getConfigLinesNbr());
}