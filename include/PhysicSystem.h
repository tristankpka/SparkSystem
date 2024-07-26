//
// Created by Tristan Klempka on 25/07/2024.
//

#ifndef PHYSICSYSTEM_H
#define PHYSICSYSTEM_H

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <iostream>

#include "System.h"
#include "Entity.h"
#include "EventDispatcher.h"
#include "World.h"
#include "components/Node.h"
#include "components/Velocity.h"

class PhysicsSystem : public System {
public:
    using QueryFunction = std::function<void(std::function<void(Entity::Id, Node&, const Velocity&)>,
                                             std::optional<std::unordered_set<Entity::Id>>)>;

    explicit PhysicsSystem(World& world, EventDispatcher& dispatcher)
        : m_query(world.getComponentQuery<Node, Velocity>()), m_dispatcher(dispatcher) {}

    void update() override {
        m_query([this](const Entity::Id id, Node& node, const Velocity& velocity) {
            node.transform = node.transform.rotate(velocity.dtheta).translate(velocity.dx, velocity.dy);
            m_dispatcher.dispatch(EventBuilder(EventType::TransformChanged, id).build());
        }, std::nullopt);
    }

private:
    QueryFunction m_query;
    EventDispatcher& m_dispatcher;
};

#endif //PHYSICSYSTEM_H
