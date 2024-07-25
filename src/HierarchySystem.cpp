//
// Created by Tristan Klempka on 25/07/2024.
//

#include "HierarchySystem.h"

#include <iostream>           // for basic_ostream, operator<<, char_traits
#include <utility>            // for move
#include "EventDispatcher.h"  // for Event, EventDispatcher, EventType

HierarchySystem::HierarchySystem(QueryFunction query, EventDispatcher& dispatcher)
    : m_query(std::move(query)) {
    dispatcher.subscribe(EventType::EntityChildAdded, [this](const Event& event) {
        onEventEntityChildAdded(event.parentId.value(), event.childId.value());
    });
    dispatcher.subscribe(EventType::EntityCreated, [this](const Event& event) {
        onEventEntityCreated(event.entityId);
    });
    dispatcher.subscribe(EventType::GlobalTransformChanged, [this](const Event& event) {
        onEventGlobalTransformChanged(event.entityId);
    });
    dispatcher.subscribe(EventType::LocalTransformChanged, [this](const Event& event) {
        onEventLocalTransformChanged(event.entityId);
    });
}

void HierarchySystem::update() {
    // No operation
}

void HierarchySystem::onEventEntityCreated(const Entity::Id entityId) {
    std::cout << "Adding entity to HierarchySystem: " << entityId << std::endl;
    m_query([this](const Entity::Id id, const Node& node) {
        if (!m_parentMap.contains(id)) {
            m_rootNodes.insert(id);
            m_nodeTransforms[id] = node.global_transform;
            std::cout << "Root node detected and added for entity: " << id << std::endl;
            const auto matrix = node.global_transform.getMatrix();
            std::cout << "Created entity: " << id << " with global transform (" << matrix[12] << ", " << matrix[13] << ")\n";
        }
    }, std::unordered_set<Entity::Id>{entityId});
}

void HierarchySystem::onEventEntityChildAdded(const Entity::Id parentId, const Entity::Id childId) {
    std::cout << "ChildAdded event received. Parent: " << parentId << ", Child: " << childId << std::endl;
    m_childNodes[parentId].push_back(childId);
    m_parentMap[childId] = parentId;
    propagateTransform(childId, m_nodeTransforms[parentId]);
}

void HierarchySystem::propagateTransform(const Entity::Id parentId, const sf::Transform& parentTransform) {
    std::cout << "Propagating transform for parent ID: " << parentId << std::endl;
    m_query([this, &parentTransform](const Entity::Id id, Node& node) {
        sf::Transform combinedTransform = parentTransform * node.local_transform;
        m_nodeTransforms[id] = combinedTransform;
        node.global_transform = combinedTransform; // Update the node's transform
        const auto matrix = combinedTransform.getMatrix();
        std::cout << "Updated entity: " << id << " with combined transform (" << matrix[12] << ", " << matrix[13] << ")\n";

        if (m_childNodes.contains(id)) {
            for (auto childId : m_childNodes[id]) {
                std::cout << "Propagating to child ID: " << childId << " of parent ID: " << id << std::endl;
                propagateTransform(childId, combinedTransform);
            }
        }
    }, std::unordered_set<Entity::Id>{parentId});
}

void HierarchySystem::onEventGlobalTransformChanged(const Entity::Id entityId) {
    m_query([this](const Entity::Id id, const Node& node) {
        if (m_rootNodes.contains(id)) {
            m_nodeTransforms[id] = node.global_transform;
            auto matrix = m_nodeTransforms[id].getMatrix();
            std::cout << "Updated entity: " << id << " with global transform (" << matrix[12] << ", " << matrix[13] << ")\n";
            if (m_childNodes.contains(id)) {
                for (const auto childId : m_childNodes[id]) {
                    std::cout << "Propagating to child ID: " << childId << " of parent ID: " << id << std::endl;
                    propagateTransform(childId, m_nodeTransforms[id]);
                }
            }
        }
    }, std::unordered_set<Entity::Id>{entityId});
}

void HierarchySystem::onEventLocalTransformChanged(const Entity::Id entityId) {
    std::cout << "LocalTransformChanged event received for entity: " << entityId << std::endl;
    if (m_parentMap.contains(entityId)) {
        const Entity::Id parentId = m_parentMap[entityId];
        propagateTransform(entityId, m_nodeTransforms[parentId]);
    }
}