//
// Created by Klemp on 11-Jul-24.
//

#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H

#include <cstdint>                // for uint8_t
#include <memory>                 // for unique_ptr
#include <typeindex>              // for type_index
#include <unordered_map>          // for unordered_map
#include <variant>                // for variant
#include "Component.h"            // for Component, ValidComponent
#include "Entity.h"               // for Entity
#include "components/Position.h"  // for Position
#include "components/Velocity.h"  // for Velocity

constexpr std::uint8_t MAX_COMPONENTS_PER_ENTITY = 128;

template<typename T>
concept ComponentType = ValidComponent<T>;

class ComponentManager {
public:
    template<ComponentType T>
    void addComponent(Entity::Id entityId, T component);

    template<ComponentType T>
    T& getComponent(Entity::Id entityId);

    template<ComponentType T>
    const T& getComponent(Entity::Id entityId) const;

    template<ComponentType T>
    [[nodiscard]] bool hasComponent(Entity::Id entityId) const;

    template<ComponentType T>
    void removeComponent(Entity::Id entityId);

    void entityDestroyed(Entity::Id entityId);

private:
    using ComponentVariant = std::variant<std::unique_ptr<Component<Position>>, std::unique_ptr<Component<Velocity>>>;
    std::unordered_map<Entity::Id, std::unordered_map<std::type_index, ComponentVariant>> m_componentMaps;
};

#include "ComponentManager.tpp"

#endif //COMPONENTMANAGER_H
