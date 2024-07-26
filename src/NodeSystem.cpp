//
// Created by Tristan Klempka on 25/07/2024.
//

#include "NodeSystem.h"
#include <iostream>              // for basic_ostream, char_traits, operator<<
#include "ComponentManager.h"  // for ComponentManager::getComponent, Comp...
#include "EventDispatcher.h"     // for Event, EventDispatcher, EventType
#include "World.h"               // for World

NodeSystem::NodeSystem(World& world, EventDispatcher& dispatcher)
    : m_query(world.getComponentQuery<Node>()) {
    dispatcher.subscribe(EventType::EntityChildAdded, [this](const Event& event) {
        onEventEntityChildAdded(event.parentId.value(), event.childId.value());
    });
}

void NodeSystem::update() {
    // No operation
}

void NodeSystem::onEventEntityChildAdded(const Entity::Id parentId, const Entity::Id childId) const {
    std::cout << "ChildAdded event received. Parent: " << parentId << ", Child: " << childId << std::endl;
    m_query([childId](const Entity::Id, Node& node) {
        node.children.insert(childId);
    }, std::unordered_set<Entity::Id>{parentId});
}