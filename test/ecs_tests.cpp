//
// Created by Tristan Klempka on 20/07/2024.
//

#include <catch2/catch_test_macros.hpp>  // for operator""_catch_sr, StringRef
#include <memory>                        // for shared_ptr
#include <utility>                       // for move
#include <variant>                       // for get
#include "ComponentManager.h"          // for ComponentManager::hasComponent
#include "Coordinator.h"                 // for Coordinator
#include "Coordinator.h"               // for Coordinator::hasComponent
#include "MovementSystem.h"              // for MovementSystem
#include "SystemManager.h"             // for SystemManager::registerSystem
#include "components/Position.h"         // for Position
#include "components/Velocity.h"         // for Velocity

TEST_CASE("CreateEntity") {
    Coordinator coordinator;
    coordinator.init();

    auto entityId = coordinator.createEntity();
    REQUIRE(entityId != 0);
}

TEST_CASE("AddAndGetComponent") {
    Coordinator coordinator;
    coordinator.init();

    auto entityId = coordinator.createEntity();
    Position position{1.0f, 2.0f};
    coordinator.addComponent<Position>(entityId, position);

    auto& retrievedPosition = coordinator.getComponent<Position>(entityId);
    REQUIRE(retrievedPosition.x == 1.0f);
    REQUIRE(retrievedPosition.y == 2.0f);
}

TEST_CASE("HasComponent") {
    Coordinator coordinator;
    coordinator.init();

    auto entityId = coordinator.createEntity();
    Position position{1.0f, 2.0f};
    coordinator.addComponent<Position>(entityId, position);

    REQUIRE(coordinator.hasComponent<Position>(entityId));
}

TEST_CASE("RemoveComponent") {
    Coordinator coordinator;
    coordinator.init();

    auto entityId = coordinator.createEntity();
    Position position{1.0f, 2.0f};
    coordinator.addComponent<Position>(entityId, position);
    REQUIRE(coordinator.hasComponent<Position>(entityId));

    coordinator.removeComponent<Position>(entityId);
    REQUIRE_FALSE(coordinator.hasComponent<Position>(entityId));
}

TEST_CASE("MovementSystemUpdate") {
    Coordinator coordinator;
    coordinator.init();

    auto entityId = coordinator.createEntity();
    coordinator.addComponent<Position>(entityId, {1.0f, 2.0f});
    coordinator.addComponent<Velocity>(entityId, {1.0f, 2.0f});

    auto movementQuery = coordinator.getComponentQuery<Position, Velocity>();
    auto movementSystem = coordinator.registerSystem<MovementSystem>(movementQuery);

    movementSystem->update();

    auto& position = coordinator.getComponent<Position>(entityId);
    REQUIRE(position.x == 2.0f);
    REQUIRE(position.y == 4.0f);
}