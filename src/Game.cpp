#include "../include/Game.hpp"
#include <iostream>

Game::Game(int width, int height, Config &config)
    : window(nullptr), renderer(nullptr), _isRunning(false),
      _windowWidth(width), _windowHeight(height), _logic(config), _frameLimit(1000 / 5), _updateLimite(1000 / 2), _config(config)
{
    _renderable.push_back(std::make_unique<ToolsBar>(_logic, 0, 0, _windowWidth / 3, _windowHeight));
    _renderable.push_back(std::make_unique<Grid>(_logic, (_windowWidth / 3) + 20, 20, ((_windowWidth / 3) * 2) - 40, _windowHeight - 40));
}

Game::~Game()
{
    cleanup();
}

bool Game::init(const char *title)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _windowWidth, _windowHeight, 0);
    if (!window)
    {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }
    SDL_SetWindowResizable(window, SDL_FALSE); // Doesn't work

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    if (_renderable[0]->init() == ERROR_CODE)
        return false;

    _isRunning = true;
    return true;
}

void Game::run()
{
    Uint32 lastUpdateTime = SDL_GetTicks();
    Uint32 lastRenderTime = SDL_GetTicks();

    while (_isRunning)
    {
        Uint32 currentTime = SDL_GetTicks();

        if (currentTime - lastUpdateTime >= 250)
        {
            update();
            lastUpdateTime = currentTime;
        }
        if (currentTime - lastRenderTime >= 15)
        { // + 60FPS
            processEvents();
            render();
            lastRenderTime = currentTime;
        }
    }
}

void Game::processEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            _isRunning = false;
        }
        _renderable[0]->handleEvent(event);
    }
}

void Game::update()
{
    _logic.update();
}

void Game::render()
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    for (int index = 0; index < _renderable.size(); index++)
    {
        _renderable[index]->render(renderer);
    }

    SDL_RenderPresent(renderer);
}

void Game::cleanup()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}