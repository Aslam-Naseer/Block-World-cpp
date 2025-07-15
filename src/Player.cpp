#include "Player.h"
#include <iostream>
#include <SFML/Graphics.hpp>

void Player::loadTextures(const std::string& dirPath) {
    // Load textures from the specified directory
    if (!idleTexture.loadFromFile(dirPath + "/idle.png")) {
        std::cerr << "Error loading idle texture from " << dirPath << "/idle.png" << std::endl;
    }
    if (!runTexture.loadFromFile(dirPath + "/run.png")) {
        std::cerr << "Error loading run texture from " << dirPath << "/run.png" << std::endl;
    }

    idleTexture.setSmooth(true);
	runTexture.setSmooth(true);
}

void Player::updateAnimation(float deltaTime) {
    
    delay += deltaTime;
    if (delay >= maxDelay) {
		delay -= maxDelay;
		currentFrame = (currentFrame + 1) % frameCount;
        sprite.setTextureRect(sf::IntRect(
            { currentFrame * frameWidth, 0 }, { frameWidth, frameHeight }));
    }
}

Player::Player(const std::string& dirPath, int initFrameCount, float maxDelay) :
	sprite(idleTexture), maxDelay(maxDelay), delay(0.f), currentFrame(0),
	state(PlayerState::Idle), isFacingRight(false)
{
    loadTextures(dirPath);
	frameWidth = idleTexture.getSize().x / initFrameCount;
	frameHeight = idleTexture.getSize().y;

    sprite.setTexture(idleTexture);
    frameCount = 8;
    sprite.setOrigin({ static_cast<float>(frameWidth / 2), static_cast<float>(frameHeight / 2) });

    sprite.setScale({ -2.f, 2.f });
    sprite.setTextureRect(sf::IntRect({ 0, 0 }, { frameWidth, frameHeight }));

}

void Player::handleInput(float deltatime) {

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A)) {
		run(false);
    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D)) {
		run(true);
    } else {
        idle();
	}

	updateAnimation(deltatime);
}

void Player::idle() {
    if (state == PlayerState::Idle)
        return;

	state = PlayerState::Idle;
    sprite.setTexture(idleTexture);
    currentFrame = 0;
    frameCount = 8;

}

void Player::run(bool faceRight) {
    if(state == PlayerState::Running && isFacingRight == faceRight)
		return;

	state = PlayerState::Running;
	isFacingRight = faceRight;
	sprite.setTexture(runTexture);
    currentFrame = 0;
    frameCount = 10;

    if(isFacingRight) {
        sprite.setScale({ -2.f, 2.f });
    } else {
        sprite.setScale({ 2.f, 2.f });
	}
}