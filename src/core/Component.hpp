#pragma once
#include <unordered_map>
#include <typeindex>
#include <memory>

/// Armazena qualquer tipo de componente de forma genérica
class IComponentStorage {
public:
    virtual ~IComponentStorage() = default;
};

template<typename T>
class ComponentStorage : public IComponentStorage {
    std::unordered_map<std::uint32_t, T> data;
public:
    void add(std::uint32_t entityId, const T& component) {
        data[entityId] = component;
    }

    bool has(std::uint32_t entityId) const {
        return data.find(entityId) != data.end();
    }

    T& get(std::uint32_t entityId) {
        return data.at(entityId);
    }

    const std::unordered_map<std::uint32_t, T>& all() const {
        return data;
    }
};
