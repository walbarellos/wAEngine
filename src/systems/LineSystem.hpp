// LineSystem.hpp
#pragma once
#include "game/Line.hpp"

class LineSystem {
public:
    void update(Line& line, double dt, bool pulling);
};
