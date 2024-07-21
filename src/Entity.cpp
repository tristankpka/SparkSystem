//
// Created by Klemp on 12-Jul-24.
//

#include "Entity.h"

Entity::Entity(const Id id) : m_id(id) {}

Entity::Id Entity::getId() const {
    return m_id;
}

bool Entity::operator==(const Entity& other) const {
    return m_id == other.m_id;
}

bool Entity::operator!=(const Entity& other) const {
    return m_id != other.m_id;
}

bool Entity::operator<(const Entity& other) const {
    return m_id < other.m_id;
}