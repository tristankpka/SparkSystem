#include <SFML/Window/Event.hpp>      // for Event
#include <SFML/Window/VideoMode.hpp>  // for VideoMode
#include <string>                     // for basic_string
#include "Window.h"                   // for Window
#include "World.h"                    // for World

int main() {
    Window window(sf::VideoMode(800, 600), "My window");
    World world;
    world.init();

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }
    return 0;
}