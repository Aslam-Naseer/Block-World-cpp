#include "Player.h"
#include <iostream>

void Player::loadTextures(const std::string& dirPath) {
    // Load textures from the specified directory
    if (!idleTexture.loadFromFile(dirPath + "/idle.png")) {
        std::cerr << "Error loading idle texture from " << dirPath << "/idle.png" << std::endl;
    }
    if (!runTexture.loadFromFile(dirPath + "/run.png")) {
        std::cerr << "Error loading run texture from " << dirPath << "/run.png" << std::endl;
    }
}

Player::Player(const std::string& dirPath) :
    frameWidth(72), frameHeight(64), sprite(idleTexture)
{
    loadTextures(dirPath);

    sprite.setTexture(idleTexture);
    sprite.setOrigin({ static_cast<float>(frameWidth / 2), static_cast<float>(frameHeight / 2) });
    sprite.setScale({ 2.f, 2.f });
    sprite.setTextureRect(sf::IntRect({ 0, 0 }, { frameWidth, frameHeight }));


    std::cout << "Player created with texture from: " << dirPath << std::endl;
}