#pragma once
#include "ecs/Registry.hpp"

class DebugSystem {
public:
    void tick(Registry& reg, bool force);
    void toggle() { enabled = !enabled; }
    bool isEnabled() const { return enabled; }

    // novo: pedir dump forçado em um único frame
    void requestDumpOnce() { dumpOnce = true; }

private:
    bool enabled      = false;
    bool dumpOnce     = false;
    int  frameCounter = 0;
};
