// ComponentManager.tpp
#ifndef COMPONENTMANAGER_TPP
#define COMPONENTMANAGER_TPP

template<ComponentType T>
void ComponentManager::addComponent(const Entity::Id entityId, T component) {
    m_componentMaps[entityId][typeid(T)] = std::make_unique<Component<T>>(std::move(component));
}

template<ComponentType T>
void ComponentManager::removeComponent(const Entity::Id entityId) {
    if (hasComponent<T>(entityId)) {
        auto& entityComponents = m_componentMaps.at(entityId);
        entityComponents.erase(typeid(T));
    }
    else
        throw std::runtime_error("Component not found for entity");
}

template<ComponentType T>
T& ComponentManager::getComponent(const Entity::Id entityId){
    if (hasComponent<T>(entityId)) {
        auto& entityComponents = m_componentMaps.at(entityId);
        auto& componentVariant = entityComponents.at(typeid(T));
        return std::get<std::unique_ptr<Component<T>>>(componentVariant)->m_value;
    }
    throw std::runtime_error("Component not found for entity");
}

template<ComponentType T>
const T& ComponentManager::getComponent(const Entity::Id entityId) const {
    if (hasComponent<T>(entityId)) {
        const auto& entityComponents = m_componentMaps.at(entityId);
        const auto& componentVariant = entityComponents.at(typeid(T));
        return std::get<std::unique_ptr<Component<T>>>(componentVariant)->m_value;
    }
    throw std::runtime_error("Component not found for entity");
}

template<ComponentType T>
bool ComponentManager::hasComponent(const Entity::Id entityId) const {
    const auto entityIt = m_componentMaps.find(entityId);
    const auto& innerMap = entityIt->second;
    return innerMap.contains(typeid(T));
}

#endif // COMPONENTMANAGER_TPP
