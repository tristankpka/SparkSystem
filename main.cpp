#include <SFML/Graphics/Color.hpp>         // for Color
#include <SFML/Graphics/RenderWindow.hpp>  // for RenderWindow
#include <SFML/System/String.hpp>          // for String
#include <SFML/Window/Event.hpp>           // for Event
#include <SFML/Window/VideoMode.hpp>       // for VideoMode
#include <memory>                          // for shared_ptr
#include "EntityFactory.h"                 // for EntityFactory
#include "NodeSystem.h"                    // for NodeSystem
#include "RenderingSystem.h"               // for RenderingSystem
#include "SystemManager.h"               // for SystemManager::registerSystem
#include "TransformManager.h"              // for TransformManager
#include "World.h"                         // for World

int main() {
    // Create a render window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Hierarchy Example");

    // Create the world
    World world;
    world.init();

    // Register systems
    const auto nodeSystem = world.registerSystem<NodeSystem>(world, world.getEventDispatcher());
    const auto renderingSystem = world.registerSystem<RenderingSystem>(world, window);

    // Create an entity factory
    const EntityFactory factory(world);
    const TransformManager transformManager(world);

    // Create origin
    auto origin = factory.createCircleEntity(1.0f, sf::Color::White);
    transformManager.applyTranslation(origin, 400.f, 300.f);

    // Create blue circle
    auto parentEntity = factory.createCircleEntity(25.0f, sf::Color::Transparent, sf::Color::Blue, 1.0f);
    world.addChild(origin, parentEntity);
    transformManager.applyTransformation(parentEntity, 90.f, 100.f, 0.f);

    // Main loop
    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // physicsSystem->update();
        renderingSystem->update();
    }

    return 0;
}
