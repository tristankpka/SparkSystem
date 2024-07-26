//
// Created by Tristan Klempka on 26/07/2024.
//

#ifndef TRANSFORMMANAGER_H
#define TRANSFORMMANAGER_H

#include <functional>     // for function
#include <optional>       // for optional
#include <unordered_set>  // for unordered_set
#include "Entity.h"       // for Entity
class World;
struct Node;

class TransformManager {
public:
    explicit TransformManager(World& world);

    void applyRotation(Entity::Id entityId, float angle) const;
    void applyTranslation(Entity::Id entityId, float x, float y) const;
    void applyTransformation(Entity::Id entityId, float angle, float x, float y) const;

private:
    std::function<void(std::function<void(Entity::Id, Node&)>, std::optional<std::unordered_set<Entity::Id>>)> m_query;
};

#endif // TRANSFORMMANAGER_H
