#pragma once
#include <unordered_map>
#include <typeindex>
#include <cstddef>
#include "ecs/Entity.hpp"

class Registry {
    Entity nextId = 1;
    std::unordered_map<std::type_index, std::unordered_map<Entity, void*>> components;

public:
    ~Registry() {
        for (auto & [type, table] : components) {
            for (auto & [e, ptr] : table) delete static_cast<char*>(ptr);
        }
    }

    Entity create() { return nextId++; }

    template<typename T>
    void add(Entity e, const T& comp) {
        components[typeid(T)][e] = new T(comp);
    }

    template<typename T>
    bool hasComponent(Entity e) {
        auto it = components.find(typeid(T));
        if (it == components.end()) return false;
        return it->second.count(e) > 0;
    }

    template<typename T>
    T& getComponent(Entity e) {
        return *static_cast<T*>(components.at(typeid(T)).at(e));
    }

    template<typename T>
    T* get(Entity e) {
        auto it = components.find(typeid(T));
        if (it == components.end()) return nullptr;
        auto it2 = it->second.find(e);
        if (it2 == it->second.end()) return nullptr;
        return static_cast<T*>(it2->second);
    }

    template<typename T>
    std::unordered_map<Entity, T*> view() {
        std::unordered_map<Entity, T*> out;
        auto it = components.find(typeid(T));
        if (it != components.end()) {
            for (auto & [e, ptr] : it->second)
                out[e] = static_cast<T*>(ptr);
        }
        return out;
    }

    void destroy(Entity e) {
        for (auto& [type, table] : components) {
            auto it = table.find(e);
            if (it != table.end()) {
                delete static_cast<char*>(it->second);
                table.erase(it);
            }
        }
    }

    std::size_t countEntities() const {
        std::size_t total = 0;
        for (auto & [type, table] : components)
            total += table.size();
        return total;
    }
};
