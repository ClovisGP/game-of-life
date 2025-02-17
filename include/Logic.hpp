#ifndef LOGIC_HPP_
#define LOGIC_HPP_

#include "../interface/ILogic.hpp"

class Logic : public ILogic
{
public:
    Logic(Config &config);
    ~Logic();

    const int &getGeneration() const;
    const bool &getIsRunning() const;
    void nextStep();
    void previousStep();
    void manageRunning();
    void update();
    int findCaseIndexInNew(std::vector<std::shared_ptr<Case>> &newGrid, int x, int y);
    int coverNeighbours(std::vector<std::shared_ptr<Case>> &newGrid, int x, int y);
    void manageCalculCase(std::vector<std::shared_ptr<Case>> &newGrid, int x, int y, bool sameCase = false);
    bool isCaseAlive(std::shared_ptr<Case> target);
    const std::vector<std::shared_ptr<Case>> &getLastGrid() const;
    const std::vector<std::shared_ptr<Case>> &getCurrentGrid() const;
    void calculNewGen();
    const bool getConfigColorEnabled() const;
    const int &getConfigLinesNbr() const;
    const int &getConfigXstart() const;
    const int &getConfigYStart() const;
    void setConfigXstart(int newValue);
    void setConfigYStart(int newValue);

private:
    int _generation;
    bool _isRunning;
    Config &_config;
    
    mutable std::mutex _mtx;                                // Only for the last grid
    std::vector<std::vector<std::shared_ptr<Case>>> _grids; // maybe limit the historic
};

#endif /* !LOGIC_HPP_ */