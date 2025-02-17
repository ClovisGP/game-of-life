#ifndef CONFIG_HPP_
#define CONFIG_HPP_

#include "../proto.hpp"
#include "../errorCode.hpp"
#include "ConfigCase.hpp"

struct Config {
    bool configReady;
    int lifeMin;
    int lifeMax;
    int reprodMin;
    int reprodMax;
    bool colorEnabled;
    std::vector<ConfigCase> firstGen;
    /* Info to display */
    const int linesNbr;
    int currentXStart;
    int currentYStart;

    Config(const char *fileName);
};

#endif /* !CONFIG_HPP_ */