#pragma once
#include <algorithm>
#include <string>

class Line {
public:
    enum class Type {
        Algodao,     // mais fraca, mas estável
        Cerol,       // agressiva, desgaste maior
        Chilena,     // cortes críticos, durabilidade baixa
        Regenerativa // se recupera devagar
    };

    struct Config {
        float maxTension;   // limite antes de romper
        float regenRate;    // taxa de regeneração
        float wearRate;     // desgaste por tensão alta
        std::string name;
    };

private:
    float tension = 0.0f;     // tensão atual [0..max]
    float durability = 1.0f;  // 1.0 = intacta, 0 = rompida
    Config config;

public:
    Line(Type type = Type::Algodao) {
        setType(type);
    }

    void setType(Type type) {
        switch (type) {
            case Type::Algodao:
                config = {1.0f, 0.2f, 0.3f, "Algodão"};
                break;
            case Type::Cerol:
                config = {1.2f, 0.1f, 0.6f, "Cerol"};
                break;
            case Type::Chilena:
                config = {1.5f, 0.05f, 0.8f, "Chilena"};
                break;
            case Type::Regenerativa:
                config = {1.0f, 0.4f, 0.25f, "Regenerativa"};
                break;
        }
    }

    void update(float dt, bool pulling) {
        if (pulling) {
            tension += dt * 0.5f; // puxando aumenta
        } else {
            tension -= dt * 0.3f; // soltar diminui
        }
        tension = std::clamp(tension, 0.0f, config.maxTension);

        // desgaste cumulativo
        if (tension >= config.maxTension * 0.95f) {
            durability -= dt * config.wearRate;
        } else {
            durability = std::min(1.0f, durability + config.regenRate * dt);
        }

        // se rompeu → reset (placeholder)
        if (durability <= 0.0f) {
            tension = 0.0f;
            durability = 1.0f;
        }
    }

    float getTension() const { return tension; }
    float getDurability() const { return durability; }
    float getStress() const { return tension / config.maxTension; } // normalizado
    const std::string& getName() const { return config.name; }
};
