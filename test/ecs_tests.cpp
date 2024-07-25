//
// Created by Tristan Klempka on 20/07/2024.
//

#include <any>
#include <catch2/catch_test_macros.hpp>  // for operator""_catch_sr, StringRef
#include <memory>                        // for shared_ptr
#include <utility>                       // for move
#include <variant>                       // for get
#include "ComponentManager.h"          // for ComponentManager::hasComponent
#include "HierarchySystem.h"
#include "World.h"                 // for Coordinator
#include "World.h"               // for Coordinator::hasComponent
#include "SystemManager.h"             // for SystemManager::registerSystem
#include "components/Velocity.h"         // for Velocity

TEST_CASE("CreateEntity") {
    World world;
    world.init();

    const auto entityId = world.createEntity();
    REQUIRE(entityId == 1);
}

TEST_CASE("AddAndGetComponent") {
    World coordinator;
    coordinator.init();

    const auto entityId = coordinator.createEntity();
    const Node node;
    coordinator.addComponent<Node>(entityId, node);

    REQUIRE(node.global_transform == sf::Transform());
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
            REQUIRE(event.entityId == 1);
        });

        auto entityId = world.createEntity();
        Node node;
        world.addComponent<Node>(entityId, node);
        REQUIRE(eventTriggered);
    }
}

TEST_CASE("Node hierarchy and transform propagation") {
    // Window window(sf::VideoMode(800, 600), "Test Window");
    World world;
    world.init();
    auto hierarchyQuery = world.getComponentQuery<Node>();
    auto hierarchySystem = world.registerSystem<HierarchySystem>(hierarchyQuery, world.getEventDispatcher());

    // Create grandparent entity
    auto grandparentEntity = world.createEntity();
    world.getComponent<Node>(grandparentEntity).global_transform.translate(5.0f, 5.0f);
    world.getEventDispatcher().dispatch({EventType::GlobalTransformChanged, grandparentEntity});
    // Create parent entity
    auto parentEntity = world.createEntity();
    world.getComponent<Node>(parentEntity).local_transform.translate(3.0f, 3.0f);
    world.getEventDispatcher().dispatch({EventType::LocalTransformChanged, parentEntity});
    // Create child entity
    auto childEntity = world.createEntity();
    world.getComponent<Node>(childEntity).local_transform.translate(1.0f, 1.0f);
    world.getEventDispatcher().dispatch({EventType::LocalTransformChanged, childEntity});

    std::cout << "Initial transforms:" << std::endl;
    std::cout << "Grandparent transform: (" << world.getComponent<Node>(grandparentEntity).global_transform.getMatrix()[12] << ", " << world.getComponent<Node>(grandparentEntity).global_transform.getMatrix()[13] << ")" << std::endl;
    std::cout << "Parent transform: (" << world.getComponent<Node>(parentEntity).local_transform.getMatrix()[12] << ", " << world.getComponent<Node>(parentEntity).local_transform.getMatrix()[13] << ")" << std::endl;
    std::cout << "Child transform: (" << world.getComponent<Node>(childEntity).local_transform.getMatrix()[12] << ", " << world.getComponent<Node>(childEntity).local_transform.getMatrix()[13] << ")" << std::endl;

    // Add parent to grandparent
    world.addChild(grandparentEntity, parentEntity);

    // Add child to parent
    world.addChild(parentEntity, childEntity);

    // Check transforms
    auto& grandparentTransform = world.getComponent<Node>(grandparentEntity).global_transform;
    auto& parentTransform = world.getComponent<Node>(parentEntity).global_transform;
    auto& childTransform = world.getComponent<Node>(childEntity).global_transform;

    // Calculate expected positions
    sf::Transform expectedGrandparentTransform;
    expectedGrandparentTransform.translate(5.0f, 5.0f);

    sf::Transform expectedParentTransform = expectedGrandparentTransform;
    expectedParentTransform.translate(3.0f, 3.0f);

    sf::Transform expectedChildTransform = expectedParentTransform;
    expectedChildTransform.translate(1.0f, 1.0f);

    sf::Vector2f grandparentPosition = grandparentTransform.transformPoint(0, 0);
    sf::Vector2f parentPosition = parentTransform.transformPoint(0, 0);
    sf::Vector2f childPosition = childTransform.transformPoint(0, 0);

    sf::Vector2f expectedGrandparentPosition = expectedGrandparentTransform.transformPoint(0, 0);
    sf::Vector2f expectedParentPosition = expectedParentTransform.transformPoint(0, 0);
    sf::Vector2f expectedChildPosition = expectedChildTransform.transformPoint(0, 0);

    std::cout << "Grandparent position: (" << grandparentPosition.x << ", " << grandparentPosition.y << ")\n";
    std::cout << "Expected Grandparent position: (" << expectedGrandparentPosition.x << ", " << expectedGrandparentPosition.y << ")\n";
    std::cout << "Parent position: (" << parentPosition.x << ", " << parentPosition.y << ")\n";
    std::cout << "Expected Parent position: (" << expectedParentPosition.x << ", " << expectedParentPosition.y << ")\n";
    std::cout << "Child position: (" << childPosition.x << ", " << childPosition.y << ")\n";
    std::cout << "Expected Child position: (" << expectedChildPosition.x << ", " << expectedChildPosition.y << ")\n";

    REQUIRE(grandparentPosition == expectedGrandparentPosition);
    REQUIRE(parentPosition == expectedParentPosition);
    REQUIRE(childPosition == expectedChildPosition);
}

class MockWorld {
public:
    MockWorld() {
        m_dispatcher = std::make_unique<EventDispatcher>();
    }

    Entity::Id createEntity() {
        Entity::Id id = ++m_lastId;
        m_entities.insert(id);
        return id;
    }

    template<typename T>
    void addComponent(Entity::Id entityId, T component) {
        m_components[entityId] = component;
    }

    template<typename T>
    T& getComponent(Entity::Id entityId) {
        return std::any_cast<T&>(m_components[entityId]);
    }

    void addChild(Entity::Id parentId, Entity::Id childId) {
        m_dispatcher->dispatch(EventBuilder(EventType::EntityChildAdded, parentId).withParentId(parentId).withChildId(childId).build());

    }

    EventDispatcher& getEventDispatcher() {
        return *m_dispatcher;
    }

    std::function<void(std::function<void(Entity::Id, Node&)>, std::optional<std::unordered_set<Entity::Id>>)> getComponentQuery() {
        return [this](std::function<void(Entity::Id, Node&)> callback, std::optional<std::unordered_set<Entity::Id>> ids) {
            if (ids.has_value()) {
                for (auto id : ids.value()) {
                    if (m_components.find(id) != m_components.end()) {
                        callback(id, std::any_cast<Node&>(m_components[id]));
                    }
                }
            } else {
                for (auto& [id, component] : m_components) {
                    callback(id, std::any_cast<Node&>(component));
                }
            }
        };
    }

private:
    Entity::Id m_lastId = 0;
    std::unordered_set<Entity::Id> m_entities;
    std::unordered_map<Entity::Id, std::any> m_components;
    std::unique_ptr<EventDispatcher> m_dispatcher;
};

// Test for EntityCreated Event
TEST_CASE("HierarchySystem handles EntityCreated event") {
    MockWorld world;

    auto hierarchyQuery = world.getComponentQuery();
    auto hierarchySystem = std::make_shared<HierarchySystem>(hierarchyQuery, world.getEventDispatcher());

    // Create an entity
    auto entity = world.createEntity();
    Node node;
    node.global_transform.translate(5.0f, 5.0f);
    world.addComponent<Node>(entity, node);
    world.getEventDispatcher().dispatch(Event{EventType::EntityCreated, entity});

    // Verify the transform
    auto& transform = world.getComponent<Node>(entity).global_transform;
    sf::Vector2f position = transform.transformPoint(0, 0);
    REQUIRE(position == sf::Vector2f(5.0f, 5.0f));
}

// Test for EntityChildAdded Event
TEST_CASE("HierarchySystem handles EntityChildAdded event") {
    MockWorld world;

    auto hierarchyQuery = world.getComponentQuery();
    auto hierarchySystem = std::make_shared<HierarchySystem>(hierarchyQuery, world.getEventDispatcher());

    // Create parent and child entities
    auto parentEntity = world.createEntity();
    Node parentNode;
    parentNode.global_transform.translate(5.0f, 5.0f);
    world.addComponent<Node>(parentEntity, parentNode);
    world.getEventDispatcher().dispatch(Event{EventType::EntityCreated, parentEntity});

    auto childEntity = world.createEntity();
    Node childNode;
    childNode.local_transform.translate(3.0f, 3.0f);
    world.addComponent<Node>(childEntity, childNode);
    world.getEventDispatcher().dispatch(Event{EventType::EntityCreated, childEntity});

    // Add child to parent
    world.addChild(parentEntity, childEntity);

    // Verify the transform
    auto& transform = world.getComponent<Node>(childEntity).global_transform;
    sf::Vector2f position = transform.transformPoint(0, 0);
    REQUIRE(position == sf::Vector2f(8.0f, 8.0f));
}

// Test for GlobalTransformChanged Event
TEST_CASE("HierarchySystem handles GlobalTransformChanged event") {
    MockWorld world;

    auto hierarchyQuery = world.getComponentQuery();
    auto hierarchySystem = std::make_shared<HierarchySystem>(hierarchyQuery, world.getEventDispatcher());

    // Create an entity
    auto entity = world.createEntity();
    Node node;
    node.global_transform.translate(5.0f, 5.0f);
    world.addComponent<Node>(entity, node);
    world.getEventDispatcher().dispatch(Event{EventType::EntityCreated, entity});

    // Change the global transform
    world.getComponent<Node>(entity).global_transform.translate(2.0f, 2.0f);
    world.getEventDispatcher().dispatch(Event{EventType::GlobalTransformChanged, entity});

    // Verify the transform
    auto& transform = world.getComponent<Node>(entity).global_transform;
    sf::Vector2f position = transform.transformPoint(0, 0);
    REQUIRE(position == sf::Vector2f(7.0f, 7.0f));
}

// Test for LocalTransformChanged Event
TEST_CASE("HierarchySystem handles LocalTransformChanged event") {
    MockWorld world;

    auto hierarchyQuery = world.getComponentQuery();
    auto hierarchySystem = std::make_shared<HierarchySystem>(hierarchyQuery, world.getEventDispatcher());

    // Create parent and child entities
    auto parentEntity = world.createEntity();
    Node parentNode;
    parentNode.global_transform.translate(5.0f, 5.0f);
    world.addComponent<Node>(parentEntity, parentNode);
    world.getEventDispatcher().dispatch(Event{EventType::EntityCreated, parentEntity});

    auto childEntity = world.createEntity();
    Node childNode;
    childNode.local_transform.translate(3.0f, 3.0f);
    world.addComponent<Node>(childEntity, childNode);
    world.getEventDispatcher().dispatch(Event{EventType::EntityCreated, childEntity});

    // Add child to parent
    world.addChild(parentEntity, childEntity);

    // Change the local transform
    world.getComponent<Node>(childEntity).local_transform.translate(1.0f, 1.0f);
    world.getEventDispatcher().dispatch(Event{EventType::LocalTransformChanged, childEntity});

    // Verify the transform
    auto& transform = world.getComponent<Node>(childEntity).global_transform;
    sf::Vector2f position = transform.transformPoint(0, 0);
    REQUIRE(position == sf::Vector2f(9.0f, 9.0f));
}