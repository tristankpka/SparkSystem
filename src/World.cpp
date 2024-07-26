//
// Created by Tristan Klempka on 18/07/2024.
//

#include "World.h"
#include <stdexcept>           // for runtime_error
#include "ComponentManager.h"  // for ComponentManager

void World::init() {
    m_componentManager = std::make_unique<ComponentManager>();
    m_entityManager = std::make_unique<EntityManager>();
    m_systemManager = std::make_unique<SystemManager>();
    m_eventDispatcher = std::make_unique<EventDispatcher>();
}

Entity::Id World::createEntity() const {
    const auto entityId = m_entityManager->createEntity();
    m_eventDispatcher->dispatch(EventBuilder(EventType::EntityCreated, entityId).build());
    return entityId;
}

void World::destroyEntity(const Entity::Id entityId) const {
    if(m_entityManager->isValid(entityId)) {
        m_entityManager->destroyEntity(entityId);
        // TODO: add destroyed event
        m_componentManager->entityDestroyed(entityId);
        // systemManager->entityDestroyed(entityId);
    } else {
        throw std::runtime_error("Entity is not valid");
    }
}

void World::addChild(const Entity::Id parentId, const Entity::Id childId) const {
    if (m_entityManager->isValid(parentId) && m_entityManager->isValid(childId)) {
        m_eventDispatcher->dispatch(EventBuilder(EventType::EntityChildAdded, parentId).withParentId(parentId).withChildId(childId).build());
    } else {
        throw std::runtime_error("Invalid parent or child entity");
    }
}
