#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Player.h"

class Game
{
private:
    unsigned int windowWidth;
    unsigned int windowHeight;
    std::string windowTitle;
    Player player;
    sf::RenderWindow window;

	sf::Clock clock;

    void initWindow();
    void pollEvents();
    void update();
    void render();

public:
    Game(const std::string& title = "SFML Window", int width = 960, int height = 640);
    ~Game();
    void run();
};