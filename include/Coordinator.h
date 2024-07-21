//
// Created by Tristan Klempka on 18/07/2024.
//

#ifndef COORDINATOR_H
#define COORDINATOR_H

#include "ComponentManager.h"
#include "EntityManager.h"
#include "SystemManager.h"

class Coordinator {
public:
    void init();

    [[nodiscard]] Entity::Id createEntity() const;

    void destroyEntity(Entity::Id entityId) const;

    template<ComponentType T>
    void addComponent(Entity::Id entityId, T component);

    template<ComponentType T>
    void removeComponent(Entity::Id entityId);

    template<ComponentType T>
    T& getComponent(Entity::Id entityId);

    template<ComponentType T>
    const T& getComponent(Entity::Id entityId) const;

    template<ComponentType T>
    [[nodiscard]] bool hasComponent(Entity::Id entityId) const;

    template<typename T, typename... Args>
    std::shared_ptr<T> registerSystem(Args&&... args);

    template<typename... Components>
    auto getComponentQuery();

private:
    std::unique_ptr<ComponentManager> componentManager;
    std::unique_ptr<EntityManager> entityManager;
    std::unique_ptr<SystemManager> systemManager;
};

#include "Coordinator.tpp"

#endif //COORDINATOR_H