#include "ecs/Registry.hpp"
#include "ecs/MovementSystem.hpp"
#include <iostream>

int main() {
    Registry reg;

    // cria entidade
    Entity kite = reg.create();
    reg.add(kite, Position{0.0f, 0.5f});
    reg.add(kite, Velocity{1.0f, 0.2f});

    // cria sistema
    MovementSystem sys;

    // simula 3 passos de 1s
    for (int i = 0; i < 3; i++) {
        sys.update(reg, 1.0f);
    }

    return 0;
}
