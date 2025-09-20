#include "ecs/systems/WindSystem.hpp"

WindSystem::WindSystem() : time(0.0), noise() {}

void WindSystem::update(Registry& reg, double dt) {
    time += dt;
    float windForce = noise.sample(time);

    for (auto [e, w] : reg.view<Wind>()) {
        w->force = windForce;
    }
}
