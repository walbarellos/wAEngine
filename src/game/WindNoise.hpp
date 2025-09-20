#pragma once
#include <cmath>
#include <random>

// Pequeno Perlin-like 1D Noise
class WindNoise {
public:
    WindNoise(unsigned seed = std::random_device{}()) 
        : rng(seed), dist(-1.0f, 1.0f) {}

    // Retorna força do vento no tempo t
    float sample(double t) {
        // Frequência baixa para dar "brisas"
        double freq = 0.2; // ciclos por segundo
        double phase = t * freq;

        // Ruído suavizado com seno e ruído aleatório
        float base = std::sin(phase * 2.0 * M_PI);
        float jitter = 0.15f * dist(rng);

        return static_cast<float>(base + jitter);
    }

private:
    std::mt19937 rng;
    std::uniform_real_distribution<float> dist;
};
