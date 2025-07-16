#include "Game.h"
#include <iostream>
#include <SFML/Graphics.hpp>

void Game::initWindow() {
    window = sf::RenderWindow(sf::VideoMode().getDesktopMode(), windowTitle, sf::Style::Default, sf::State::Fullscreen);
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
    float deltaTime = clock.restart().asSeconds();
    player.handleInput(deltaTime);
}

void Game::render() {
    player.draw(window);
    window.display();
}

Game::Game(const std::string& title, int width, int height) :
    windowTitle(title), player("assets/Player", 0.05, 500.f)
{
    initWindow();
	windowWidth = window.getSize().x;
	windowHeight = window.getSize().y;
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