//
// Created by Klemp on 11-Jul-24.
//

#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H

#include <unordered_map>
#include <array>
#include <bitset>
#include <cstdint>

#include "Entity.h"
#include "Component.h"

constexpr std::uint8_t MAX_COMPONENTS_PER_ENTITY = 128;

template<typename T>
concept ComponentType = ValidComponent<T>;

class ComponentManager {
public:
    template<ComponentType T>
    void addComponent(Entity::Id entityId, T component);

    // TODO const ?
    template<ComponentType T>
    T& getComponent(Entity::Id entityId);

    template<ComponentType T>
    bool hasComponent(Entity::Id entityId) const;

    template<ComponentType T>
    void removeComponent(Entity::Id entityId);

    void removeAllComponents(Entity::Id entityId);

private:
    // TODO is the mask necessary ? we could store directly a map with a list of attached component
    std::unordered_map<Entity::Id, std::bitset<MAX_COMPONENTS_PER_ENTITY>> entityComponentMask;

    template<ComponentType T>
    std::unordered_map<Entity::Id, T>& getComponentMap();
};

#include "ComponentManager.tpp"

#endif //COMPONENTMANAGER_H
