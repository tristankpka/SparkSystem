//
// Created by Tristan Klempka on 20/07/2024.
//

#include <any>
#include <catch2/catch_test_macros.hpp>  // for operator""_catch_sr, StringRef
#include <catch2/catch_approx.hpp>
#include <memory>                        // for shared_ptr
#include <utility>                       // for move
#include <variant>                       // for get
#include "ComponentManager.h"          // for ComponentManager::hasComponent
#include "EntityFactory.h"
#include "NodeSystem.h"
#include "World.h"                 // for Coordinator
#include "World.h"               // for Coordinator::hasComponent
#include "SystemManager.h"             // for SystemManager::registerSystem
#include "components/Velocity.h"
#include "TransformManager.h"
#include "EventDispatcher.h"// for Velocity

TEST_CASE("CreateEntity") {
    World world;
    world.init();

    const auto entityId = world.createEntity();
    REQUIRE(entityId == 0);
}

TEST_CASE("AddAndGetComponent") {
    World coordinator;
    coordinator.init();

    const auto entityId = coordinator.createEntity();
    const Node node;
    coordinator.addComponent<Node>(entityId, node);

    REQUIRE(node.transform == sf::Transform());
}

TEST_CASE("HasComponent") {
    World coordinator;
    coordinator.init();

    const auto entityId = coordinator.createEntity();
    const Node node;
    coordinator.addComponent<Node>(entityId, node);

    REQUIRE(coordinator.hasComponent<Node>(entityId));
}

TEST_CASE("RemoveComponent") {
    World world;
    world.init();

    const auto entityId = world.createEntity();
    const Node node;
    world.addComponent<Node>(entityId, node);
    REQUIRE(world.hasComponent<Node>(entityId));

    world.removeComponent<Node>(entityId);
    REQUIRE_FALSE(world.hasComponent<Node>(entityId));
}

TEST_CASE("Event Dispatcher") {
    World world;
    world.init();
    auto& dispatcher = world.getEventDispatcher();

    SECTION("ComponentAdded event") {
        bool eventTriggered = false;
        dispatcher.subscribe(EventType::EntityUpdated, [&](const Event& event) {
            eventTriggered = true;
            REQUIRE(event.entityId == 0);
        });

        auto entityId = world.createEntity();
        Node node;
        world.addComponent<Node>(entityId, node);
        REQUIRE(eventTriggered);
    }
}

class MockWorld {
public:
    void init() {
        // Initialization logic if necessary
    }

    Entity::Id createEntity() {
        Entity::Id newId = nextEntityId++;
        entities[newId] = {};
        return newId;
    }

    template <typename T>
    void addComponent(Entity::Id entityId, T component) {
        entities[entityId].emplace(typeid(T).hash_code(), std::make_any<T>(std::move(component)));
    }

    template <typename T>
    T& getComponent(Entity::Id entityId) {
        return std::any_cast<T&>(entities[entityId][typeid(T).hash_code()]);
    }

    void addChild(Entity::Id parentId, Entity::Id childId) {
        getComponent<Node>(parentId).children.insert(childId);
        getComponent<Node>(childId).parent = parentId;
    }

    EventDispatcher& getEventDispatcher() {
        return dispatcher;
    }

    auto getComponentQuery() {
        return [this](auto callback, auto filter) {
            for (auto& [entityId, components] : entities) {
                if (filter.has_value()) {
                    if (filter->count(entityId) == 0) {
                        continue;
                    }
                }
                if (components.count(typeid(Node).hash_code()) > 0) {
                    callback(entityId, std::any_cast<Node&>(components[typeid(Node).hash_code()]));
                }
            }
        };
    }

private:
    Entity::Id nextEntityId = 1;
    std::unordered_map<Entity::Id, std::unordered_map<size_t, std::any>> entities;
    EventDispatcher dispatcher;
};

TEST_CASE("TransformManager applyTransformation", "[TransformManager]") {
    World world;
    world.init();
    const TransformManager transformManager(world);
    const EntityFactory factory(world);

    // Create origin
    const auto origin = factory.createCircleEntity(1.0f, sf::Color::White);
    transformManager.applyTranslation(origin, 400.f, 300.f);
    transformManager.applyRotation(origin, 0.f);

    // Create blue circle
    const auto parentEntity = factory.createCircleEntity(25.0f, sf::Color::Transparent, sf::Color::Blue, 1.0f);
    world.addChild(origin, parentEntity);
    transformManager.applyTransformation(parentEntity, 90.f, 100.f, 0.f);

    // Get the transformed point
    const auto& originTransform = world.getComponent<Node>(origin).transform;
    const auto& childTransform = world.getComponent<Node>(parentEntity).transform;
    const sf::Vector2f transformedPoint = childTransform.transformPoint(originTransform.transformPoint(0, 0));

    // Expected position after 90 degree rotation around the parent (400, 300)
    const sf::Vector2f expectedPoint(400.f, 400.f);

    REQUIRE(transformedPoint.x == Catch::Approx(expectedPoint.x).margin(1e-5));
    REQUIRE(transformedPoint.y == Catch::Approx(expectedPoint.y).margin(1e-5));
}