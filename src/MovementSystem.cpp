//
// Created by Klemp on 12-Jul-24.
//
//

#include "MovementSystem.h"

// void MovementSystem::update(EntityManager& entityManager, ComponentManager& componentManager) {
//     for (const Entity& entity : entityManager.getEntities()) {
//         if (componentManager.hasComponent<Position>(entity) && componentManager.hasComponent<Velocity>(entity)) {
//             auto& pos = componentManager.getComponent<Position>(entity);
//             auto& vel = componentManager.getComponent<Velocity>(entity);
//
//             pos.x += vel.dx;
//             pos.y += vel.dy;
//         }
//     }
// }