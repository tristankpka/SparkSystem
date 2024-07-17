#include <iostream>

#include "ComponentManager.h"
#include "MovementSystem.h"
#include "components/Position.h"
#include "components/Velocity.h"

int main() {
    EntityManager entityManager;
    // MovementSystem movementSystem(entityManager);

    Entity::Id e1 = entityManager.createEntity();
    Entity::Id e2 = entityManager.createEntity();

    entityManager.addComponent<Position>(e1, Position{0.0f, 0.0f});
    entityManager.addComponent<Velocity>(e1, Velocity{1.0f, 1.0f});

    entityManager.addComponent<Position>(e2, Position{10.0f, 10.0f});
    entityManager.addComponent<Velocity>(e2, Velocity{0.5f, -0.5f});

    // Output initial positions
    if (entityManager.hasComponent<Position>(e1)) {
        const auto& pos = entityManager.getComponent<Position>(e1);
        std::cout << "Entity 1 Position: (" << pos.x << ", " << pos.y << ")\n";
    }

    if (entityManager.hasComponent<Position>(e2)) {
        const auto& pos = entityManager.getComponent<Position>(e2);
        std::cout << "Entity 2 Position: (" << pos.x << ", " << pos.y << ")\n";
    }

    //
    //
    // // Update movement system to move entities
    // movementSystem.update();

    // Output updated positions
    if (entityManager.hasComponent<Position>(e1)) {
        const auto& pos = entityManager.getComponent<Position>(e1);
        std::cout << "Entity 1 Position: (" << pos.x << ", " << pos.y << ")\n";
    }

    if (entityManager.hasComponent<Position>(e2)) {
        const auto& pos = entityManager.getComponent<Position>(e2);
        std::cout << "Entity 2 Position: (" << pos.x << ", " << pos.y << ")\n";
    }

    // Destroy an entity
    entityManager.destroyEntity(e1);

    // Check if entity 1 is valid
    if (!entityManager.isValid(e1)) {
        std::cout << "Entity 1 has been destroyed.\n";
    }

    // Attempt to access a component of the destroyed entity (should throw an error)
    try {
        entityManager.getComponent<Position>(e1);
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;  // Output: Attempted to get a component from an invalid entity.
    }

    return 0;
}
