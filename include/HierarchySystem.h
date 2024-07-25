//
// Created by Tristan Klempka on 24/07/2024.
//

#ifndef HIERARCHYSYSTEM_H
#define HIERARCHYSYSTEM_H

#include <SFML/Graphics/Transform.hpp>  // for Transform
#include <functional>                   // for function
#include <optional>                     // for optional
#include <unordered_map>                // for unordered_map
#include <unordered_set>                // for unordered_set
#include <vector>                       // for vector
#include "Entity.h"                     // for Entity
#include "System.h"                     // for System
#include "components/Node.h"            // for Node
class EventDispatcher;

class HierarchySystem : public System {
public:
    using QueryFunction = std::function<void(std::function<void(Entity::Id, Node&)>,
                                             std::optional<std::unordered_set<Entity::Id>>)>;

    explicit HierarchySystem(QueryFunction query, EventDispatcher& dispatcher);

    void update() override;

private:
    QueryFunction m_query;
    std::unordered_set<Entity::Id> m_rootNodes;
    std::unordered_map<Entity::Id, sf::Transform> m_nodeTransforms;
    std::unordered_map<Entity::Id, Entity::Id> m_parentMap;
    std::unordered_map<Entity::Id, std::vector<Entity::Id>> m_childNodes;

    void onEventEntityCreated(Entity::Id entityId);
    void onEventEntityChildAdded(Entity::Id parentId, Entity::Id childId);
    void propagateTransform(Entity::Id parentId, const sf::Transform& parentTransform);
    void onEventGlobalTransformChanged(Entity::Id entityId);
    void onEventLocalTransformChanged(Entity::Id entityId);
};

#endif //HIERARCHYSYSTEM_H
