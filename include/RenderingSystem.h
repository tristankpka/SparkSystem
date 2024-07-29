//
// Created by Tristan Klempka on 25/07/2024.
//

#ifndef RENDERINGSYSTEM_H
#define RENDERINGSYSTEM_H

#include <functional>          // for function
#include <optional>            // for optional
#include <unordered_map>       // for unordered_map
#include <unordered_set>       // for unordered_set
#include "Entity.h"            // for Entity
#include "System.h"            // for System
#include "components/Node.h"   // for Node
#include "components/Shape.h"  // for Shape
class World;
namespace sf { class Shape; }
namespace sf { class RenderWindow; }
namespace sf { class Transform; }

class RenderingSystem : public System {
public:
    using QueryFunction = std::function<void(std::function<void(Entity::Id, Node&, Shape&)>,
                                             std::optional<std::unordered_set<Entity::Id>>)>;

    explicit RenderingSystem(World& world, sf::RenderWindow& window);

    void update() override;

private:
    QueryFunction m_query;
    sf::RenderWindow& m_window;
    std::unordered_map<Entity::Id, sf::Drawable*> m_renderables;

    void doDraw(Entity::Id id, const sf::Transform& parentTransform);
};

#endif // RENDERINGSYSTEM_H
