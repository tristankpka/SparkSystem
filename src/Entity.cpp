//
// Created by Klemp on 12-Jul-24.
//

#include "Entity.h"

Entity::Entity(const Id id) : id(id) {}

Entity::Id Entity::getId() const {
    return id;
}

bool Entity::operator==(const Entity& other) const {
    return id == other.id;
}

bool Entity::operator!=(const Entity& other) const {
    return id != other.id;
}

bool Entity::operator<(const Entity& other) const {
    return id < other.id;
}