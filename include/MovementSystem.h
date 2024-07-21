//
// Created by Klemp on 12-Jul-24.
//

#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H

#include <EntityManager.h>

#include "System.h"
#include "components/Position.h"
#include "components/Velocity.h"

class MovementSystem : public System {
public:
    using QueryFunction = std::function<void(std::function<void(Entity::Id, Position&, const Velocity&)>)>;

    explicit MovementSystem(QueryFunction query) : query(std::move(query)) {}

    void update() override {
        query([](Entity::Id entityId, Position& position, const Velocity& velocity) {
            position.x += velocity.dx;
            position.y += velocity.dy;
        });
    }
private:
    QueryFunction query;
};

#endif //MOVEMENTSYSTEM_H
