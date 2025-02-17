#include "../include/Logic.hpp"

Logic::Logic(Config &config)
    : _generation(0),
      _isRunning(false),
      _config(config)
{
    /* Generation 0*/
    std::vector<std::shared_ptr<Case>> tmpGrid;

    tmpGrid.reserve(_config.firstGen.size());
    for (int index = 0; index < _config.firstGen.size(); index++)
    {
        tmpGrid.emplace_back(std::make_shared<Case>(_config.firstGen[index].x, _config.firstGen[index].y, _config.firstGen[index].population, true));
    }
    _grids.push_back(std::move(tmpGrid));
}

Logic::~Logic()
{
}

const int &Logic::getGeneration() const
{
    return _generation;
}

const bool &Logic::getIsRunning() const
{
    return _isRunning;
}

void Logic::nextStep()
{
    calculNewGen();
}

void Logic::previousStep()
{
    if (_generation > 0)
    {
        _generation = _generation - 2;
        calculNewGen();
    }
}

void Logic::manageRunning()
{
    _isRunning = !_isRunning;
}

void Logic::update()
{
    if (!_isRunning)
        return;

    calculNewGen();
}

void Logic::calculNewGen()
{
    /* Thread version */
    /* To enabled it, uncomment it and the mutex. But the code proceed by the thread are so simple thta the thread are less optimised
    (for 50 generation, it takes 3 seconds more than just one process). And the solution to make a mutex for the grid and one for each case is not secure too so you have the explaination.
    */
    // if (_grids.size() - 1 < _generation + 1)
    // {
    //     // Init threads
    //     std::vector<std::shared_ptr<Case>> tmpGrid;
    //     size_t caseCount = _grids[_generation].size();
    //     size_t numThreads = 5;
    //     if (caseCount > 500) // Calcul the amount of threads needed
    //         numThreads = (caseCount > 1000) ? ((caseCount > 2000) ? 4 : 3) : 2;
    //     size_t chunkSize = caseCount / numThreads;
    //     std::vector<std::thread> threads(numThreads);
    //     std::function<void(int, size_t, size_t)> processThread = [&](int id, size_t start, size_t end) { // The function of the Thread
    //         for (size_t index = start; index < end; index++)
    //         {
    //             if (isCaseAlive(_grids[_generation][index]))
    //             {
    //                 coverNeighbours(tmpGrid, _grids[_generation][index]->x, _grids[_generation][index]->y);
    //             }
    //         }
    //     };
    //     // Threads launch
    //     for (size_t index = 0; index < numThreads; index++)
    //         threads[index] = std::thread(
    //             processThread,
    //             index, // Helps debug
    //             index * chunkSize,
    //             ((index == numThreads - 1) ? caseCount : (index * chunkSize) + chunkSize));

    //     // Join threads
    //     for (size_t index = 0; index < numThreads; index++)
    //         threads[index].join();

    //     _grids.push_back(std::move(tmpGrid));
    // }
    // _generation++;

    /* Version without Thread */
    if (_grids.size() - 1 < _generation + 1)
    {
        std::vector<std::shared_ptr<Case>> tmpGrid;

        for (size_t index = 0; index < _grids[_generation].size(); index++)
        {
            if (isCaseAlive(_grids[_generation][index]))
            {
                coverNeighbours(tmpGrid, _grids[_generation][index]->x, _grids[_generation][index]->y);
            }
        }
        _grids.push_back(std::move(tmpGrid));
    }
    _generation++;
}

int Logic::coverNeighbours(std::vector<std::shared_ptr<Case>> &newGrid, int x, int y)
{
    for (int indexLine = -1, indexColumn = -1; indexLine <= 1 && indexColumn <= 1;)
    {
        if (x + indexLine == x && y + indexColumn == y)
        {
            manageCalculCase(newGrid, x, y, true);
        }
        else if ((x + indexLine >= 0 && y + indexColumn >= 0))
        {
            manageCalculCase(newGrid, x + indexLine, y + indexColumn);
        }
        if (indexLine + 1 > 1)
        {
            indexLine = -1;
            indexColumn++;
        }
        else
        {
            indexLine++;
        }
    }
    return 0;
}

void Logic::manageCalculCase(std::vector<std::shared_ptr<Case>> &newGrid, int x, int y, bool sameCase)
{
    //_mtx.lock();
    const int indexCase = findCaseIndexInNew(newGrid, x, y);
    //_mtx.unlock();

    if (indexCase >= 0)
    {
        //_mtx.lock();
        if (sameCase)
            newGrid[indexCase]->existBefore = true;
        else
            newGrid[indexCase]->population++;
        //_mtx.unlock();
    }
    else
    {
        //_mtx.lock();
        if (sameCase)
            newGrid.emplace_back(std::make_shared<Case>(x, y, 0, true));
        else
            newGrid.emplace_back(std::make_shared<Case>(x, y, 1));
        //_mtx.unlock();
    }
}

int Logic::findCaseIndexInNew(std::vector<std::shared_ptr<Case>> &newGrid, int x, int y)
{
    std::vector<std::shared_ptr<Case>>::iterator it = std::find_if(
        newGrid.begin(), newGrid.end(),
        [x, y](const std::shared_ptr<Case> &casePtr)
        {
            return casePtr->x == x && casePtr->y == y;
        });

    const int result = (it != newGrid.end()) ? std::distance(newGrid.begin(), it) : -1;
    return result;
}

bool Logic::isCaseAlive(std::shared_ptr<Case> target)
{
    return ((_config.lifeMin <= target->population && target->population <= _config.lifeMax) && target->existBefore) ||
           (_config.reprodMin <= target->population && target->population <= _config.reprodMax);
}

const std::vector<std::shared_ptr<Case>> &Logic::getLastGrid() const
{
    return _grids[_grids.size() - 1];
}

const std::vector<std::shared_ptr<Case>> &Logic::getCurrentGrid() const
{
    return _grids[_generation];
}

const bool Logic::getConfigColorEnabled() const
{
    return _config.colorEnabled;
}

const int &Logic::getConfigLinesNbr() const
{
    return _config.linesNbr;
}

const int &Logic::getConfigXstart() const
{
    return _config.currentXStart;
}

const int &Logic::getConfigYStart() const
{
    return _config.currentYStart;
}

void Logic::setConfigXstart(int newValue)
{
    _config.currentXStart = newValue;
}

void Logic::setConfigYStart(int newValue)
{
    _config.currentYStart = newValue;
}