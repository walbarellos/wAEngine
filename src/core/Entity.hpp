#pragma once
#include <cstdint>

/// Representa uma entidade do jogo.
/// Apenas um identificador único.
struct Entity {
    std::uint32_t id;

    bool operator==(const Entity& other) const { return id == other.id; }
    bool operator!=(const Entity& other) const { return id != other.id; }
};
