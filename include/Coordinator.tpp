#ifndef COORDINATOR_TPP
#define COORDINATOR_TPP

template<ComponentType T>
void Coordinator::addComponent(const Entity::Id entityId, T component) {
    if(m_entityManager->isValid(entityId)) {
        m_componentManager->addComponent<T>(entityId, std::move(component));
    } else {
        throw std::runtime_error("Entity is not valid");
    }
}

template<ComponentType T>
void Coordinator::removeComponent(const Entity::Id entityId) {
    if(m_entityManager->isValid(entityId)) {
        m_componentManager->removeComponent<T>(entityId);
    } else {
        throw std::runtime_error("Entity is not valid");
    }
}

template<ComponentType T>
T& Coordinator::getComponent(const Entity::Id entityId) {
    if(m_entityManager->isValid(entityId)) {
        return m_componentManager->getComponent<T>(entityId);
    }
    throw std::runtime_error("Entity is not valid");
}

template<ComponentType T>
const T& Coordinator::getComponent(const Entity::Id entityId) const {
    if(m_entityManager->isValid(entityId)) {
        return m_componentManager->getComponent<T>(entityId);
    }
    throw std::runtime_error("Entity is not valid");
}

template<ComponentType T>
[[nodiscard]] bool Coordinator::hasComponent(const Entity::Id entityId) const {
    if(m_entityManager->isValid(entityId)) {
        return m_componentManager->hasComponent<T>(entityId);
    }
    throw std::runtime_error("Entity is not valid");
}

template<typename T, typename... Args>
std::shared_ptr<T> Coordinator::registerSystem(Args&&... args) {
    return m_systemManager->registerSystem<T>(std::forward<Args>(args)...);
}

template<typename... Components>
auto Coordinator::getComponentQuery() {
    return [this](auto func) {
        for (const auto& entity : m_entityManager->getEntities()) {
            if ((this->hasComponent<Components>(entity.getId()) && ...)) {
                func(this->getComponent<Components>(entity.getId())...);
            }
        }
    };
}
#endif // COORDINATOR_TPP
