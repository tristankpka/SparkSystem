//
// Created by Tristan Klempka on 25/07/2024.
//

#include "RenderingSystem.h"
#include <SFML/Graphics/RenderWindow.hpp>  // for RenderWindow
#include <SFML/Graphics/Shape.hpp>         // for Shape
#include <SFML/Graphics/Transform.hpp>     // for Transform, operator*
#include <memory>                          // for unique_ptr
#include "ComponentManager.h"            // for ComponentManager::getCompo...
#include "World.h"                         // for World
#include "World.h"                       // for World::getComponentQuery

RenderingSystem::RenderingSystem(World& world, sf::RenderWindow& window)
    : m_query(world.getComponentQuery<Node, Shape>()), m_window(window) {}

void RenderingSystem::update() {

    m_window.clear();
    // TODO remove macgic cst
    doDraw(Entity::Id{0}, sf::Transform::Identity);
    m_window.display();
}

void RenderingSystem::doDraw(const Entity::Id id, const sf::Transform& parentTransform) {
    m_query([this, parentTransform](Entity::Id, const Node& node, const Shape& renderable) {
            m_window.draw(*renderable.shape, node.transform * parentTransform);
        for (const auto child: node.children) {
            doDraw(child, node.transform * parentTransform);
        }
    }, std::unordered_set<Entity::Id>{id});
}
