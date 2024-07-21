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
    [[nodiscard]] bool isValid(Entity::Id entityId) const;
    [[nodiscard]] const std::unordered_set<Entity>& getEntities() const;

private:
    Entity::Id nextId = 1;
    std::unordered_set<Entity> entities;
};

#include "EntityManager.tpp"

#endif //ENTITYMANAGER_H
