//
// Created by Klemp on 12-Jul-24.
//

#include "EntityManager.h"

Entity::Id EntityManager::createEntity() {
    const Entity entity(nextId++);
    entities.insert(entity);
    return entity.getId();
}


void EntityManager::destroyEntity(const Entity::Id entityId) {
    auto it = entities.find(Entity(entityId));
    if (it != entities.end()) {
        entities.erase(it);
    }
}

bool EntityManager::isValid(const Entity::Id entityId) const {
    return entities.contains(Entity(entityId));
}

const std::unordered_set<Entity>& EntityManager::getEntities() const {
    return entities;
}
