#pragma once
#include <SDL2/SDL.h>
#include <unordered_map>

class Input {
public:
    void beginFrame() {
        pressed.clear();
        released.clear();
    }

    void handleEvent(const SDL_Event& e) {
        if (e.type == SDL_KEYDOWN && !e.key.repeat) {
            keys[e.key.keysym.sym] = true;
            pressed[e.key.keysym.sym] = true;
        }
        if (e.type == SDL_KEYUP) {
            keys[e.key.keysym.sym] = false;
            released[e.key.keysym.sym] = true;
        }
    }

    bool isDown(SDL_Keycode key) const {
        auto it = keys.find(key);
        return it != keys.end() && it->second;
    }

    bool isPressed(SDL_Keycode key) const {
        return pressed.count(key);
    }

    bool isReleased(SDL_Keycode key) const {
        return released.count(key);
    }

private:
    std::unordered_map<SDL_Keycode,bool> keys;
    std::unordered_map<SDL_Keycode,bool> pressed;
    std::unordered_map<SDL_Keycode,bool> released;
};
