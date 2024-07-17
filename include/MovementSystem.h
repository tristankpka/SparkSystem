//
// Created by Klemp on 12-Jul-24.
//

#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H

#include <EntityManager.h>

#include "System.h"

class MovementSystem final : public System {
public:
    void update(EntityManager& entityManager, ComponentManager& manager) override;
};

#endif //MOVEMENTSYSTEM_H
