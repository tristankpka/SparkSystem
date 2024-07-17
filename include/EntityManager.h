//
// Created by Klemp on 12-Jul-24.
//

#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include "ComponentManager.h"
#include "Entity.h"

#include <unordered_set>

constexpr std::uint16_t MAX_ENTITIES = 65535;

class EntityManager {
public:
    EntityManager() = default;

    Entity::Id createEntity();
    void destroyEntity(Entity::Id entityId);
    bool isValid(Entity::Id entityId) const;
    const std::unordered_set<Entity>& getEntities() const;

    template<ComponentType T>
    void addComponent(Entity::Id entityId, T component);

    template<ComponentType T>
    T& getComponent(Entity::Id entityId);

    template<ComponentType T>
    bool hasComponent(Entity::Id entityId) const;

    template<ComponentType T>
    void removeComponent(Entity::Id entityId);

private:
    Entity::Id nextId = 1;
    std::unordered_set<Entity> entities;
    ComponentManager componentManager;
};

#include "EntityManager.tpp"

#endif //ENTITYMANAGER_H
