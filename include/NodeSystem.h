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
class EventDispatcher;  // lines 18-18
class World;

class NodeSystem : public System {
public:
    using QueryFunction = std::function<void(std::function<void(Entity::Id, Node&)>,
                                             std::optional<std::unordered_set<Entity::Id>>)>;

    explicit NodeSystem(World& world, EventDispatcher& dispatcher);

    void update() override;

private:
    QueryFunction m_query;

    void onEventEntityChildAdded(Entity::Id parentId, Entity::Id childId) const;
};

#endif //HIERARCHYSYSTEM_H
