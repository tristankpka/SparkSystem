//
// Created by Tristan Klempka on 22/07/2024.
//

#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/Graphics/RenderWindow.hpp>  // for RenderWindow
#include <SFML/System/String.hpp>          // for String
#include <SFML/Window/VideoMode.hpp>       // for VideoMode
#include <string>                          // for string
namespace sf { class Event; }

class Window {
public:
    Window(const sf::VideoMode& mode, const std::string& title)
        : m_window(mode, title) {}

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;
    Window(Window&&) = delete;
    Window& operator=(Window&&) = delete;

    bool isOpen() const { return m_window.isOpen(); }
    bool pollEvent(sf::Event& event) { return m_window.pollEvent(event); }
    void close() { m_window.close(); }
    sf::RenderWindow& getRenderWindow() {
        return m_window;
    }

private:
    sf::RenderWindow m_window;
};

#endif //WINDOW_H
