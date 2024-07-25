#ifndef COORDINATOR_TPP
#define COORDINATOR_TPP
#include <iostream>

template<ComponentType T>
void World::addComponent(const Entity::Id entityId, T component) {
    if(m_entityManager->isValid(entityId)) {
        m_componentManager->addComponent<T>(entityId, std::move(component));
        m_eventDispatcher->dispatch(Event{EventType::EntityUpdated, entityId});
    } else {
        throw std::runtime_error("Entity is not valid");
    }
}

template<ComponentType T>
void World::removeComponent(const Entity::Id entityId) {
    if(m_entityManager->isValid(entityId)) {
        m_componentManager->removeComponent<T>(entityId);
    } else {
        throw std::runtime_error("Entity is not valid");
    }
}

template<ComponentType T>
T& World::getComponent(const Entity::Id entityId) {
    if(m_entityManager->isValid(entityId)) {
        return m_componentManager->getComponent<T>(entityId);
    }
    throw std::runtime_error("Entity is not valid");
}

template<ComponentType T>
const T& World::getComponent(const Entity::Id entityId) const {
    if(m_entityManager->isValid(entityId)) {
        return m_componentManager->getComponent<T>(entityId);
    }
    throw std::runtime_error("Entity is not valid");
}

template<ComponentType T>
[[nodiscard]] bool World::hasComponent(const Entity::Id entityId) const {
    if(m_entityManager->isValid(entityId)) {
        return m_componentManager->hasComponent<T>(entityId);
    }
    throw std::runtime_error("Entity is not valid");
}

template<typename T, typename... Args>
std::shared_ptr<T> World::registerSystem(Args&&... args) {
    return m_systemManager->registerSystem<T>(std::forward<Args>(args)...);
}

template<typename... Components>
auto World::getComponentQuery() {
    return [this](auto func, const std::optional<std::unordered_set<Entity::Id>> &filter = std::nullopt) {
        if (filter) {
            for (const auto& entityId : *filter) {
                if ((this->hasComponent<Components>(entityId) && ...)) {
                    func(entityId, this->getComponent<Components>(entityId)...);
                }             }
        } else {
            for (const auto& entity : m_entityManager->getEntities()) {
                if ((this->hasComponent<Components>(entity.getId()) && ...)) {
                    func(entity.getId(), this->getComponent<Components>(entity.getId())...);
                }
            }
        }
    };
}
#endif // COORDINATOR_TPP
