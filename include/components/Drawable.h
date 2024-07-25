//
// Created by Tristan Klempka on 22/07/2024.
//

#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <SFML/Graphics/Drawable.hpp>

struct Drawable {
    std::unique_ptr<sf::Drawable> drawable;
};

#endif //DRAWABLE_H
