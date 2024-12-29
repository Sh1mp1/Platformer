#pragma once
#include "Animation.h"
#include "TileMap.h"
class Player
{
private:
	//player bounds
	sf::CircleShape topLeft;
	sf::CircleShape topRight;
	sf::CircleShape bottomLeft;
	sf::CircleShape bottomRight;

	sf::Font font;
	sf::Text movementText;

	float jumpStrength;
	float movementSpeed;
	float gravity;
	sf::Vector2f velocity;
	sf::Vector2f maxVelocity;
	sf::Vector2f minVelocity;
	float drag;

	sf::Sprite sprite;
	sf::Texture texture;

	Animation animation;

	sf::SoundBuffer shootBuffer;
	sf::Sound shootSound;

	sf::SoundBuffer reloadSoundBuffer;
	sf::Sound reloadSound;

	bool isFlipped;

	bool grounded;

	int state;
	bool moving;
	bool shooting;

	int reloadTimerMax;
	int reloadTimer;

	int shootTimerMax;
	int shootTimer;

	
	void initSprite();
	void initVariables();
	void initAudio();
	void initText();
	void initCircle();

public:
	Player();
	~Player();

	//Accessors
	const sf::Vector2f getPosition() const;
	const sf::Vector2f getVelocity() const;
	const sf::FloatRect getGlobalBounds() const;

	//Functions 
	void updateText();
	void updateMaxVelocity();
	void updateInput(sf::RenderWindow& window);
	void updateMovement(TileMap* tile);
	void jump();
	void updateState();
	void updateAnimation();
	void playSound();
	void updateWindowBoundsCollision(sf::RenderWindow& window);
	void updateCircle();

	void move(sf::Vector2f offset);


	void update(sf::RenderWindow& window, TileMap* tile);
	void render(sf::RenderTarget& target);
};

