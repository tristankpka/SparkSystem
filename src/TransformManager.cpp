//
// Created by Tristan Klempka on 26/07/2024.
//

#include "TransformManager.h"
#include <SFML/Graphics/Transform.hpp>  // for Transform
#include "ComponentManager.h"         // for ComponentManager::getComponent
#include "World.h"                      // for World
#include "components/Node.h"            // for Node

TransformManager::TransformManager(World& world)
    : m_query(world.getComponentQuery<Node>()) {}

void TransformManager::applyRotation(const Entity::Id entityId, const float angle) const {
    m_query([this, angle](const Entity::Id, Node& node) {
        m_query([&node, angle](const Entity::Id, const Node& parentNode) {
            node.transform.rotate(angle, parentNode.transform.transformPoint(0, 0));
        }, std::unordered_set<Entity::Id>{node.parent});
    }, std::unordered_set<Entity::Id>{entityId});
}

void TransformManager::applyTranslation(const Entity::Id entityId, const float x, const float y) const {
    m_query([x, y](const Entity::Id, Node& node) {
        node.transform.translate(x, y);
    }, std::unordered_set<Entity::Id>{entityId});
}

void TransformManager::applyTransformation(const Entity::Id entityId, const float angle, const float x, const float y) const {
    m_query([this, angle, x, y](const Entity::Id, Node& node) {
        m_query([&node, angle, x, y](const Entity::Id, const Node& parentNode) {
            node.transform.rotate(angle, parentNode.transform.transformPoint(0, 0)).translate(x, y);
        }, std::unordered_set<Entity::Id>{node.parent});
    }, std::unordered_set<Entity::Id>{entityId});
}