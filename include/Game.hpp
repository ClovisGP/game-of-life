#ifndef GAME_HPP_
#define GAME_HPP_

#include "../interface/IGame.hpp"
#include "Logic.hpp"
#include "struct/Config.hpp"
#include <vector>
#include <memory>
#include "Renderable/ToolsBar.hpp"
#include "Renderable/Grid.hpp"

class Game : public IGame
{
public:
    Game(int width, int height, Config &config);
    ~Game();
    bool init(const char *title);
    void run();
    void cleanup();

private:
    void processEvents();
    void update();
    void render();

    const int _windowWidth;
    const int _windowHeight;
    const int _frameLimit;
    const int _updateLimite;

    SDL_Window *window;
    SDL_Renderer *renderer;
    Logic _logic;
    Config &_config;
    bool _isRunning;
    int _generation = 0;
    std::vector<std::unique_ptr<IRenderable>> _renderable;
};

#endif // GAME_HPP_
