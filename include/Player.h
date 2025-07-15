#pragma once
#include <SFML/Graphics.hpp>
#include <string>


class Player
{
private:
    sf::Texture idleTexture;
    sf::Texture runTexture;
    sf::Sprite sprite;
    int frameWidth;
    int frameHeight;

    void loadTextures(const std::string& dirPath);

public:
    Player(const std::string& dirPath, int initFrameCount);
    ~Player() = default;

    sf::Vector2f getPosition() const { return sprite.getPosition(); }
    void setPosition(float x, float y) { sprite.setPosition({ x, y }); }
    void draw(sf::RenderWindow& window) { window.draw(sprite); }

    // Future methods for animation
    // void idle();
    // void run();
};