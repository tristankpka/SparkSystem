#include <iostream>               // for basic_ostream, operator<<, char_traits
#include <memory>                 // for shared_ptr
#include <utility>                // for move
#include <variant>                // for get
#include "ComponentManager.h"   // for ComponentManager::getComponent, Com...
#include "Coordinator.h"          // for Coordinator
#include "Coordinator.h"        // for Coordinator::addComponent, Coordina...
#include "Entity.h"               // for Entity
#include "MovementSystem.h"       // for MovementSystem
#include "SystemManager.h"      // for SystemManager::registerSystem
#include "components/Position.h"  // for Position
#include "components/Velocity.h"  // for Velocity


int main() {
    Coordinator coordinator;
    coordinator.init();

    const Entity::Id entityId = coordinator.createEntity();
    coordinator.addComponent<Position>(entityId, {1.0f, 2.0f});
    coordinator.addComponent<Velocity>(entityId, {1.0f, 2.0f});

    MovementSystem::QueryFunction movementQuery = coordinator.getComponentQuery<Position, Velocity>();
    auto movementSystem = coordinator.registerSystem<MovementSystem>(movementQuery);

    auto& position1 = coordinator.getComponent<Position>(entityId);
    std::cout << "Initial Entity position: (" << position1.x << ", " << position1.y << ")\n";

    // Simulate game loop
    for (int i = 0; i < 10; ++i) {
        movementSystem->update();
        auto& position2 = coordinator.getComponent<Position>(entityId);
        std::cout << "Entity position after update " << i << ": (" << position2.x << ", " << position2.y << ")\n";
    }

    return 0;
}