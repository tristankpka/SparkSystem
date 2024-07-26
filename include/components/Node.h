//
// Created by Tristan Klempka on 22/07/2024.
//

#ifndef NODE_H
#define NODE_H

#include <unordered_set>
#include <SFML/Graphics.hpp>

#include "Entity.h"

struct Node {
    sf::Transform transform = sf::Transform::Identity;
    Entity::Id parent = 0;
    std::unordered_set<Entity::Id> children = {};
};

#endif //NODE_H
