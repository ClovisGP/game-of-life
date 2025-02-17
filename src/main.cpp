#include "../include/Game.hpp"
#include "../include/proto.hpp"
#include "../include/errorCode.hpp"
#include "../include/struct/Config.hpp"

int main(int argc, char **argv)
{
    const int argsManResult = checkArgsValidity(argc, argv); // Just to make some rapid sizing

    if (argsManResult == ERROR_CODE)
    {
        std::cerr << BAD_ARGUMENT << std::endl;
        return (ERROR_CODE);
    }
    Config config(argv[1]);
    if (!config.configReady)
        return (ERROR_CODE);

    Game game(
        argsManResult == EXIT_SUCCESS ? 1200 : argsManResult == 1 ? 1000 : 1550,
        argsManResult == EXIT_SUCCESS ? 800 : argsManResult == 1 ? 625 : 1000,
        config);

    if (game.init("GameOfLife"))
    {
        game.run();
    }
    return (EXIT_SUCCESS);
}