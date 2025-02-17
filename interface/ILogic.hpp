#ifndef ILOGIC_HPP_
#define ILOGIC_HPP_

#include "../include/proto.hpp"
#include "../include/struct/Case.hpp"
#include "../include/struct/Config.hpp"
#include <mutex>

class ILogic
{
public:
    virtual ~ILogic() = default ;

    virtual const int &getGeneration() const = 0;
    virtual const bool &getIsRunning() const = 0;
    virtual void nextStep() = 0;
    virtual void previousStep() = 0;
    virtual void manageRunning() = 0;
    virtual void update() = 0;
    virtual int findCaseIndexInNew(std::vector<std::shared_ptr<Case>> &newGrid, int x, int y) = 0;
    virtual int coverNeighbours(std::vector<std::shared_ptr<Case>> &newGrid, int x, int y) = 0;
    virtual void manageCalculCase(std::vector<std::shared_ptr<Case>> &newGrid, int x, int y, bool sameCase = false) = 0;
    virtual bool isCaseAlive(std::shared_ptr<Case> target) = 0;
    virtual const std::vector<std::shared_ptr<Case>> &getLastGrid() const = 0;
    virtual const std::vector<std::shared_ptr<Case>> &getCurrentGrid() const = 0;
    virtual void calculNewGen() = 0;
    virtual const bool getConfigColorEnabled() const = 0;
    virtual const int &getConfigLinesNbr() const = 0;
    virtual const int &getConfigXstart() const = 0;
    virtual const int &getConfigYStart() const = 0;
    virtual void setConfigXstart(int newValue) = 0;
    virtual void setConfigYStart(int newValue) = 0;
};

#endif /* !ILOGIC_HPP_ */