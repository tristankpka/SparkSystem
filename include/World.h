//
// Created by Tristan Klempka on 18/07/2024.
//

#ifndef COORDINATOR_H
#define COORDINATOR_H

#include <memory>              // for unique_ptr, shared_ptr
#include "ComponentManager.h"  // for ComponentType, ComponentManager
#include "Entity.h"            // for Entity
#include "EntityManager.h"     // for EntityManager
#include "EventDispatcher.h"   // for EventDispatcher
#include "SystemManager.h"     // for SystemManager

class World {
public:
    void init();

    [[nodiscard]] Entity::Id createEntity() const;

    void destroyEntity(Entity::Id entityId) const;

    void addChild(Entity::Id parentId, Entity::Id childId) const;

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

    [[nodiscard]] EventDispatcher& getEventDispatcher() const {
        return *m_eventDispatcher;
    }

private:
    std::unique_ptr<ComponentManager> m_componentManager;
    std::unique_ptr<EntityManager> m_entityManager;
    std::unique_ptr<SystemManager> m_systemManager;
    std::unique_ptr<EventDispatcher> m_eventDispatcher;
};

#include "World.tpp"

#endif //COORDINATOR_H