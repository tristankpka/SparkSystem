//
// Created by Tristan Klempka on 22/07/2024.
//

#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <memory>
#include <SFML/Graphics/Shape.hpp>

struct Shape {
    std::unique_ptr<sf::Shape> shape{};
};

#endif //DRAWABLE_H
