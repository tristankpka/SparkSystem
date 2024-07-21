// ComponentManager.tpp

#include <typeinfo>
#include <variant>

template<ComponentType T>
void ComponentManager::addComponent(const Entity::Id entityId, T component) {
    componentMaps[entityId][typeid(T)] = std::make_unique<Component<T>>(std::move(component));
}

template<ComponentType T>
void ComponentManager::removeComponent(const Entity::Id entityId) {
    if (hasComponent<T>(entityId)) {
        auto& entityComponents = componentMaps.at(entityId);
        entityComponents.erase(typeid(T));
    }
    else
        throw std::runtime_error("Component not found for entity");
}

template<ComponentType T>
T& ComponentManager::getComponent(const Entity::Id entityId){
    if (hasComponent<T>(entityId)) {
        auto& entityComponents = componentMaps.at(entityId);
        auto& componentVariant = entityComponents.at(typeid(T));
        return std::get<std::unique_ptr<Component<T>>>(componentVariant)->value;
    }
    throw std::runtime_error("Component not found for entity");
}

template<ComponentType T>
const T& ComponentManager::getComponent(const Entity::Id entityId) const {
    if (hasComponent<T>(entityId)) {
        const auto& entityComponents = componentMaps.at(entityId);
        const auto& componentVariant = entityComponents.at(typeid(T));
        return std::get<std::unique_ptr<Component<T>>>(componentVariant)->value;
    }
    throw std::runtime_error("Component not found for entity");
}

template<ComponentType T>
bool ComponentManager::hasComponent(const Entity::Id entityId) const {
    const auto entityIt = componentMaps.find(entityId);
    const auto& innerMap = entityIt->second;
    return innerMap.contains(typeid(T));
}

