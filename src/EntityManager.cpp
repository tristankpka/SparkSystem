//
// Created by Klemp on 12-Jul-24.
//

#include "EntityManager.h"

Entity::Id EntityManager::createEntity() {
    const Entity entity(m_nextId++);
    m_entities.insert(entity);
    return entity.getId();
}


void EntityManager::destroyEntity(const Entity::Id entityId) {
    auto it = m_entities.find(Entity(entityId));
    if (it != m_entities.end()) {
        m_entities.erase(it);
    }
}

bool EntityManager::isValid(const Entity::Id entityId) const {
    return m_entities.contains(Entity(entityId));
}

const std::unordered_set<Entity>& EntityManager::getEntities() const {
    return m_entities;
}
