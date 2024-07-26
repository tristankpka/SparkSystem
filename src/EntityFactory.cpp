//
// Created by Tristan Klempka on 26/07/2024.
//

#include "EntityFactory.h"
#include <SFML/Graphics/Shape.hpp>  // for Shape
#include <utility>                  // for move
#include "ComponentManager.h"     // for ComponentManager::addComponent
#include "World.h"                  // for World
#include "World.tpp"                // for World::addComponent
#include "components/Node.h"        // for Node
#include "components/Shape.h"       // for Shape

EntityFactory::EntityFactory(World& world) : world(world) {}

Entity::Id EntityFactory::createCircleEntity(const float radius, const sf::Color fillColor, const sf::Color outlineColor, const float outlineThickness) const {
    const auto entityId = world.createEntity();
    const Node node;
    world.addComponent<Node>(entityId, node);  // Add Node component by default
    Shape renderable;
    renderable.shape = createCircle(radius, fillColor, outlineColor, outlineThickness);
    world.addComponent<Shape>(entityId, std::move(renderable));
    return entityId;
}

Entity::Id EntityFactory::createRectangleEntity(const sf::Vector2f& size, const sf::Color& fillColor, const sf::Color& outlineColor, const float outlineThickness) const {
    const auto entityId = world.createEntity();
    const Node node;
    world.addComponent<Node>(entityId, node);  // Add Node component by default
    Shape renderable;
    renderable.shape = createRectangle(size, fillColor, outlineColor, outlineThickness);
    world.addComponent<Shape>(entityId, std::move(renderable));
    return entityId;
}

std::unique_ptr<sf::CircleShape> EntityFactory::createCircle(float radius, const sf::Color fillColor, const sf::Color outlineColor, const float outlineThickness) {
    auto circle = std::make_unique<sf::CircleShape>(radius);
    circle->setFillColor(fillColor);
    circle->setOutlineColor(outlineColor);
    circle->setOutlineThickness(outlineThickness);
    circle->setOrigin(radius, radius); // Set origin to center of the circle
    return circle;
}

std::unique_ptr<sf::RectangleShape> EntityFactory::createRectangle(const sf::Vector2f& size, const sf::Color& fillColor, const sf::Color& outlineColor, const float outlineThickness) {
    auto rectangle = std::make_unique<sf::RectangleShape>(size);
    rectangle->setFillColor(fillColor);
    rectangle->setOutlineColor(outlineColor);
    rectangle->setOutlineThickness(outlineThickness);
    rectangle->setOrigin(size.x / 2.0f, size.y / 2.0f); // Set origin to center of the rectangle
    return rectangle;
}