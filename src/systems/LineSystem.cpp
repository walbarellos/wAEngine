// LineSystem.cpp
#include "systems/LineSystem.hpp"

void LineSystem::update(Line& line, double dt, bool pulling) {
    line.update(dt, pulling);
}
