//
// Created by Tristan Klempka on 25/07/2024.
//

#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H

#include <SFML/Graphics/CircleShape.hpp>     // for CircleShape
#include <SFML/Graphics/Color.hpp>           // for Color
#include <SFML/Graphics/RectangleShape.hpp>  // for RectangleShape
#include <SFML/System/Vector2.hpp>           // for Vector2f
#include <memory>                            // for unique_ptr
#include "Entity.h"                          // for Entity
class World;

class EntityFactory {
public:
    explicit EntityFactory(World& world);

    [[nodiscard]] Entity::Id createCircleEntity(float radius, sf::Color fillColor, sf::Color outlineColor = sf::Color::Transparent, float outlineThickness = 0.0f) const;
    [[nodiscard]] Entity::Id createRectangleEntity(const sf::Vector2f& size, const sf::Color& fillColor, const sf::Color& outlineColor = sf::Color::Transparent, float outlineThickness = 0.0f) const;

private:
    World& world;

    static std::unique_ptr<sf::CircleShape> createCircle(float radius, sf::Color fillColor, sf::Color outlineColor = sf::Color::Transparent, float outlineThickness = 0.0f);
    static std::unique_ptr<sf::RectangleShape> createRectangle(const sf::Vector2f& size, const sf::Color& fillColor, const sf::Color& outlineColor = sf::Color::Transparent, float outlineThickness = 0.0f);
};

#endif // ENTITYFACTORY_H
