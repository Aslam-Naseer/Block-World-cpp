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

Player::Player(const std::string& dirPath, float maxDelay, float speed) :
	sprite(idleTexture), maxDelay(maxDelay), delay(0.f), speed(speed),
	state(PlayerState::Idle), isFacingRight(false), currentFrame(0), 
	frameCount(IDLEFRAMECOUNT)
{
    loadTextures(dirPath);
	frameWidth = idleTexture.getSize().x / IDLEFRAMECOUNT;
	frameHeight = idleTexture.getSize().y;

    sprite.setOrigin({ static_cast<float>(frameWidth / 4), static_cast<float>(frameHeight / 2) });
    sprite.setTextureRect(sf::IntRect({ 0, 0 }, { frameWidth, frameHeight }));

}

void Player::handleInput(float deltatime) {

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A)) {
		run(false, deltatime);
    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D)) {
		run(true, deltatime);
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
    frameCount = IDLEFRAMECOUNT;

}

void Player::run(bool faceRight, float deltatime) {

	sprite.move({ (faceRight ? 1 : -1) * speed * deltatime , 0.f });
    if(state == PlayerState::Running && isFacingRight == faceRight)
		return;

	state = PlayerState::Running;
	isFacingRight = faceRight;
	sprite.setTexture(runTexture);
    currentFrame = 0;
    frameCount = RUNFRAMECOUNT;

    if(isFacingRight) {
        sprite.setScale({ -1.f, 1.f });
    } else {
        sprite.setScale({ 1.f, 1.f });
	}
}