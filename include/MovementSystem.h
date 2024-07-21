//
// Created by Klemp on 12-Jul-24.
//

#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H

#include <functional>             // for function
#include <utility>                // for move
#include "System.h"               // for System
#include "components/Position.h"  // for Position
#include "components/Velocity.h"  // for Velocity

class MovementSystem : public System {
public:
    using QueryFunction = std::function<void(std::function<void(Position&, const Velocity&)>)>;

    explicit MovementSystem(QueryFunction query) : m_query(std::move(query)) {}

    void update() override {
        m_query([](Position& position, const Velocity& velocity) {
            position.x += velocity.dx;
            position.y += velocity.dy;
        });
    }
private:
    QueryFunction m_query;
};

#endif //MOVEMENTSYSTEM_H
