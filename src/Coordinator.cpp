//
// Created by Tristan Klempka on 18/07/2024.
//

#include "Coordinator.h"

void Coordinator::init() {
    componentManager = std::make_unique<ComponentManager>();
    entityManager = std::make_unique<EntityManager>();
    systemManager = std::make_unique<SystemManager>();
}

Entity::Id Coordinator::createEntity() const {
    return entityManager->createEntity();
}

void Coordinator::destroyEntity(const Entity::Id entityId) const {
    if(entityManager->isValid(entityId)) {
        entityManager->destroyEntity(entityId);
        // TODO: add destroyed event
        componentManager->entityDestroyed(entityId);
        // systemManager->entityDestroyed(entityId);
    } else {
        throw std::runtime_error("Entity is not valid");
    }
}