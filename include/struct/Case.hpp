#ifndef CASE_HPP
#define CASE_HPP

#include "../threadInclude.hpp"

struct Case {
    int x;
    int y;
    int population;
    bool existBefore;
    //mutable std::mutex mtx; // Useless

    Case(int xPos, int yPos, int pop, bool existBefore = false);
};

#endif // CASE_HPP