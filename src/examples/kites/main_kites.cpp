#include <SFML/Graphics.hpp>
#include "KiteEntity.hpp"
#include "ReelEntity.hpp"
#include "LineEntity.hpp"
#include <cmath> // sin, cos

int main() {
    // Construtor SFML 3: recebe Vector2u diretamente
    sf::RenderWindow window(
    sf::VideoMode({1000u, 650u}, 32u),
    "wAEngine • Exemplo de Pipas (SFML 3)",
    sf::State::Windowed
	);
    window.setFramerateLimit(60);

    // ==== Jogador A ====
    ReelEntity reelA({250.f, 560.f});
    reelA.setAngularSpeed(0.f);
    KiteEntity kiteA({300.f, 260.f}, sf::Color(220, 20, 60), KiteEntity::Model::Losango);
    LineEntity lineA;
    lineA.setLengthLimit(360.f);

    // ==== Oponente / IA simples ====
    ReelEntity reelB({750.f, 560.f});
	KiteEntity kiteB({600.f, 260.f}, sf::Color(30, 144, 255), KiteEntity::Model::Raia);

    LineEntity lineB;
    lineB.setLengthLimit(360.f);

    sf::Clock clock;
    float t = 0.f;

    while (window.isOpen()) {
        // Eventos no SFML 3: pollEvent() -> std::optional<Event>
        while (auto ev = window.pollEvent()) {
            if (ev->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        const float dt = clock.restart().asSeconds();
        t += dt;

        // ===== Input Jogador A (WASD) =====
        sf::Vector2f forceA{0.f, 0.f};
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) forceA.y -= 60.f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) forceA.y += 60.f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) forceA.x -= 60.f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) forceA.x += 60.f;
        kiteA.addForce(forceA);

        // ===== “IA” rudimentar p/ B (oscila c/ senos) =====
        const float sx = static_cast<float>(std::sin(t * 1.3f) * 35.0);
        const float sy = static_cast<float>(std::cos(t * 0.9f) * 20.0);
        sf::Vector2f windB(sx, sy);
        kiteB.addForce(windB);

        // ===== Atualizar entidades =====
        kiteA.update(dt);
        kiteB.update(dt);

        lineA.setEndpoints(reelA.getPosition(), kiteA.getPosition());
        lineB.setEndpoints(reelB.getPosition(), kiteB.getPosition());
        lineA.update(dt);
        lineB.update(dt);

        // Tensionamento → rotação do carretel quando próximo/ultrapassa limite
        reelA.setAngularSpeed(lineA.tension() > 0.95f ? 120.f : 0.f);
        reelB.setAngularSpeed(lineB.tension() > 0.95f ? 120.f : 0.f);
        reelA.update(dt);
        reelB.update(dt);

        // ===== Render =====
        window.clear(sf::Color(110, 180, 220)); // “céu”
        lineA.draw(window);
        lineB.draw(window);
        reelA.draw(window);
        reelB.draw(window);
        kiteA.draw(window);
        kiteB.draw(window);
        window.display();
    }
    return 0;
}
