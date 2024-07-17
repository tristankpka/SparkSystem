// ComponentManager.tpp

#include <typeinfo>

template<ComponentType T>
void ComponentManager::addComponent(const Entity::Id entityId, T component) {
    auto& componentArray = getComponentMap<T>();
    componentArray[entityId] = component;
    entityComponentMask[entityId].set(Component<T>::getId());
}

template<ComponentType T>
T& ComponentManager::getComponent(const Entity::Id entityId) {
    auto& componentArray = getComponentMap<T>();
    return componentArray[entityId];
}

template<ComponentType T>
bool ComponentManager::hasComponent(const Entity::Id entityId) const {
    return entityComponentMask.at(entityId).test(Component<T>::getId());
}

template<ComponentType T>
void ComponentManager::removeComponent(const Entity::Id entityId) {
    auto& componentMap = getComponentMap<T>();
    componentMap.erase(entityId);
    entityComponentMask[entityId].reset(Component<T>::getComponentType());
}

template<ComponentType T>
std::unordered_map<Entity::Id, T>& ComponentManager::getComponentMap() {
    static std::unordered_map<Entity::Id, T> componentArray;
    return componentArray;
}