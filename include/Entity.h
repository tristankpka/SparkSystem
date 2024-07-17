//
// Created by Klemp on 11-Jul-24.
//

#ifndef ENTITY_H
#define ENTITY_H

#include <cstdint>
#include <functional>

class Entity {
public:
    using Id = std::uint32_t;

    Entity() = delete;
    explicit Entity(Id id);

    [[nodiscard]] Id getId() const;

    bool operator==(const Entity& other) const;
    bool operator!=(const Entity& other) const;
    bool operator<(const Entity& other) const;

private:
    Id id;
};

// Custom hash function for Entity
template <>
struct std::hash<Entity> {
    std::size_t operator()(const Entity& entity) const noexcept {
        return std::hash<Entity::Id>()(entity.getId());
    }
};

#endif //ENTITY_H
