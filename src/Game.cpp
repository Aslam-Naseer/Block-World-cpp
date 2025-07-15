#include "Game.h"
#include <iostream>

void Game::initWindow() {
    window = sf::RenderWindow(sf::VideoMode({ windowWidth, windowHeight }), windowTitle);
    window.setFramerateLimit(144);
}

void Game::pollEvents() {
    while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }
        else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
                window.close();
            }
        }
    }
}

void Game::update() {
    window.clear();

}

void Game::render() {
    player.draw(window);
    window.display();
}

Game::Game(const std::string& title, int width, int height) :
    windowWidth(width), windowHeight(height), windowTitle(title), player("assets/Player", 8)
{
    initWindow();
    player.setPosition(windowWidth / 2.f, windowHeight / 2.f);
}

Game::~Game() {
}

void Game::run() {
    while (window.isOpen()) {
        pollEvents();
        update();
        render();
    }
}