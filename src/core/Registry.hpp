#pragma once
#include "Entity.hpp"
#include "Component.hpp"
#include <unordered_map>
#include <typeindex>
#include <memory>

/// Gerencia entidades e componentes
class Registry {
    std::uint32_t nextId = 1;
    std::unordered_map<std::type_index, std::unique_ptr<IComponentStorage>> storages;

public:
    Entity createEntity() {
        return Entity{ nextId++ };
    }

    template<typename T>
    void addComponent(Entity e, const T& component) {
        auto idx = std::type_index(typeid(T));
        if (!storages.count(idx)) {
            storages[idx] = std::make_unique<ComponentStorage<T>>();
        }
        auto* storage = static_cast<ComponentStorage<T>*>(storages[idx].get());
        storage->add(e.id, component);
    }

    template<typename T>
    bool hasComponent(Entity e) {
        auto idx = std::type_index(typeid(T));
        if (!storages.count(idx)) return false;
        auto* storage = static_cast<ComponentStorage<T>*>(storages[idx].get());
        return storage->has(e.id);
    }

    template<typename T>
    T& getComponent(Entity e) {
        auto idx = std::type_index(typeid(T));
        auto* storage = static_cast<ComponentStorage<T>*>(storages[idx].get());
        return storage->get(e.id);
    }

    template<typename T>
    const std::unordered_map<std::uint32_t, T>& view() {
        auto idx = std::type_index(typeid(T));
        auto* storage = static_cast<ComponentStorage<T>*>(storages[idx].get());
        return storage->all();
    }
};
