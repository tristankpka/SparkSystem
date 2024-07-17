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
        componentManager.removeAllComponents(entityId);
    }
}

bool EntityManager::isValid(const Entity::Id entityId) const {
    return entities.find(Entity(entityId)) != entities.end();
}

const std::unordered_set<Entity>& EntityManager::getEntities() const {
    return entities;
}
