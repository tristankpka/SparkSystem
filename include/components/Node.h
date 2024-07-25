//
// Created by Tristan Klempka on 22/07/2024.
//

#ifndef NODE_H
#define NODE_H

#include <SFML/Graphics.hpp>

struct Node {
    sf::Transform global_transform = sf::Transform::Identity;
    sf::Transform local_transform = sf::Transform::Identity;
};

#endif //NODE_H
