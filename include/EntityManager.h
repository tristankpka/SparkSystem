//
// Created by Klemp on 12-Jul-24.
//

#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <cstdint>        // for uint16_t
#include <unordered_set>  // for unordered_set
#include "Entity.h"       // for hash, Entity

constexpr std::uint16_t MAX_ENTITIES = 65535;

class EntityManager {
public:
    EntityManager() = default;

    Entity::Id createEntity();
    void destroyEntity(Entity::Id entityId);
    [[nodiscard]] bool isValid(Entity::Id entityId) const;
    [[nodiscard]] const std::unordered_set<Entity>& getEntities() const;

private:
    Entity::Id m_nextId = 0;
    std::unordered_set<Entity> m_entities;
};

#endif //ENTITYMANAGER_H
