#pragma once
#include <SFML/Graphics.hpp>
#include <algorithm>

class LineEntity {
public:
    LineEntity();

    // Define os pontos de ancoragem (carretel ↔ pipa)
    void setEndpoints(sf::Vector2f start, sf::Vector2f end);

    // Limite de comprimento “ideal” (para calcular tensão)
    void setLengthLimit(float limit) { lengthLimit_ = limit; }
    float getLengthLimit() const { return lengthLimit_; }

    // Fator de tensão [0..N] (>=1 indica esticada além do limite)
    float tension() const { return currentLength_ / std::max(1.f, lengthLimit_); }

    void update(float dt);
    void draw(sf::RenderTarget& rt) const;

private:
    sf::VertexArray line_;
    float lengthLimit_{300.f};
    float currentLength_{0.f};

    static float distance(sf::Vector2f a, sf::Vector2f b);
};
