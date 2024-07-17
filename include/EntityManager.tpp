// EntityManager.tpp

#include <stdexcept>

template<ComponentType T>
void EntityManager::addComponent(Entity::Id entityId, T component) {
    if (isValid(entityId)) {
        componentManager.addComponent<T>(entityId, component);
    } else {
        throw std::runtime_error("Attempted to add a component to an invalid entity.");
    }
}

template<ComponentType T>
T& EntityManager::getComponent(Entity::Id entityId) {
    if (isValid(entityId)) {
        return componentManager.getComponent<T>(entityId);
    } else {
        throw std::runtime_error("Attempted to get a component from an invalid entity.");
    }
}

template<ComponentType T>
bool EntityManager::hasComponent(Entity::Id entityId) const {
    if (isValid(entityId)) {
        return componentManager.hasComponent<T>(entityId);
    } else {
        throw std::runtime_error("Attempted to check a component for an invalid entity.");
    }
}

template<ComponentType T>
void EntityManager::removeComponent(Entity::Id entityId) {
    if (isValid(entityId)) {
        componentManager.removeComponent<T>(entityId);
    } else {
        throw std::runtime_error("Attempted to remove a component from an invalid entity.");
    }
}