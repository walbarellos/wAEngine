#pragma once

struct GameState {
    float kiteX = 0.0f;
    float kiteY = 0.5f;
    bool pulling = false;
    bool paused = false;

    void reset() {
        kiteX = 0.0f;
        kiteY = 0.5f;
        pulling = false;
        paused = false;
    }
};
