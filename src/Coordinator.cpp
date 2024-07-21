//
// Created by Tristan Klempka on 18/07/2024.
//

#include "Coordinator.h"
#include <stdexcept>  // for runtime_error

void Coordinator::init() {
    m_componentManager = std::make_unique<ComponentManager>();
    m_entityManager = std::make_unique<EntityManager>();
    m_systemManager = std::make_unique<SystemManager>();
}

Entity::Id Coordinator::createEntity() const {
    return m_entityManager->createEntity();
}

void Coordinator::destroyEntity(const Entity::Id entityId) const {
    if(m_entityManager->isValid(entityId)) {
        m_entityManager->destroyEntity(entityId);
        // TODO: add destroyed event
        m_componentManager->entityDestroyed(entityId);
        // systemManager->entityDestroyed(entityId);
    } else {
        throw std::runtime_error("Entity is not valid");
    }
}