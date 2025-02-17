#include "../../include/struct/Config.hpp"

Config::Config(const char *fileName) : linesNbr(50), currentXStart(0), currentYStart(0)
{
    std::ifstream file(fileName);
    if (!file)
    {
        std::cerr << BAD_CONFIG << std::endl
                  << BAD_FILE << std::endl;
        configReady = false;
        return;
    }

    nlohmann::json jsonData;
    try
    {
        file >> jsonData;
    }
    catch (const nlohmann::json::parse_error &e)
    {
        std::cerr << BAD_CONFIG << std::endl
                  << BAD_PARSING << std::endl;
        configReady = false;
        return;
    }

    if (jsonData.contains("life-min") && jsonData["life-min"].is_number_integer())
    {
        int value = jsonData["life-min"];
        if (value < 0 || 8 < value)
        {
            std::cerr << BAD_CONFIG << std::endl
                      << BAD_LIFE_MIN << std::endl;
            lifeMin = 2;
        }
        else
            lifeMin = value;
    }
    if (jsonData.contains("life-max") && jsonData["life-max"].is_number_integer())
    {
        int value = jsonData["life-max"];
        if (value < 0 || 8 < value)
        {
            std::cerr << BAD_CONFIG << std::endl
                      << BAD_LIFE_MAX << std::endl;
            lifeMax = 3;
        }
        else
            lifeMax = value;
    }
    if (jsonData.contains("repro-min") && jsonData["repro-min"].is_number_integer())
    {
        int value = jsonData["repro-min"];
        if (value < 0 || 8 < value)
        {
            std::cerr << BAD_CONFIG << std::endl
                      << BAD_REPRO_MIN << std::endl;
            reprodMin = 3;
        }
        else
            reprodMin = value;
    }
    if (jsonData.contains("repro-max") && jsonData["repro-max"].is_number_integer())
    {
        int value = jsonData["repro-max"];
        if (value < 0 || 8 < value)
        {
            std::cerr << BAD_CONFIG << std::endl
                      << BAD_REPRO_MAX << std::endl;
            reprodMax = 3;
        }
        else
            reprodMax = value;
    }
    if (jsonData.contains("colorful-grid") && jsonData["colorful-grid"].is_boolean())
    {
        colorEnabled = jsonData["colorful-grid"];
    }

    if (jsonData.contains("start-state") && jsonData["start-state"].is_array())
    {
        for (const auto &obj : jsonData["start-state"])
        {
            if (obj.contains("x") && obj["x"].is_number_integer() &&
                obj.contains("y") && obj["y"].is_number_integer() &&
                obj.contains("population") && obj["population"].is_number_integer())
            {
                firstGen.emplace_back(obj["x"], obj["y"], obj["population"]);
            }
            else
            {
                std::cerr << BAD_CONFIG << std::endl
                          << BAD_START_STATE_CASE << std::endl;
                configReady = false;
            }
        }
        if (firstGen.size() < 1)
        {
            std::cerr << BAD_CONFIG << std::endl
                      << BAD_START_STATE << std::endl;
            configReady = false;
            return;
        }
        configReady = true;
    }
    else
    {
        std::cerr << BAD_CONFIG << std::endl
                  << BAD_START_STATE << std::endl;
        configReady = false;
    }
}