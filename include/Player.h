#pragma once
#include <SFML/Graphics.hpp>
#include <string>

enum class PlayerState {
    Idle,
    Running
};

class Player
{
private:
    sf::Texture idleTexture;
    sf::Texture runTexture;
    sf::Sprite sprite;

    int frameWidth;
    int frameHeight;
	int frameCount;
	int currentFrame;

	float maxDelay;
	float delay;

	PlayerState state;
	bool isFacingRight;

    void loadTextures(const std::string& dirPath);
    void updateAnimation(float deltaTime);

public:
    Player(const std::string& dirPath, int initFrameCount, float maxDelay);
    ~Player() = default;

    sf::Vector2f getPosition() const { return sprite.getPosition(); }
    void setPosition(float x, float y) { sprite.setPosition({ x, y }); }
    void draw(sf::RenderWindow& window) { window.draw(sprite); }

	void handleInput(float deltaTime);
    void idle();
    void run(bool faceRight);
};