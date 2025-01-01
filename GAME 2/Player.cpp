#include "stdafx.h"
#include "Player.h"



void Player::initSprite()
{
	if (!this->texture.loadFromFile("Textures/Soldier.png"))
	{
		std::cout << "ERROR::PLAYER::INITTEXTURES::COULDNT INITIALIZE TEXTURE SHEET" << "\n";
	}

	this->sprite.setTexture(this->texture);
	this->animation = Animation(44, 186, 52, 68);
	this->sprite.setTextureRect(this->animation.getFrame());
	this->sprite.setPosition(sf::Vector2f(200.f, 100.f));
	this->sprite.setScale(sf::Vector2f(2, 2));


	this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 4, 0);

}

void Player::initVariables()
{
	this->grounded = false;
	this->jumpStrength = -20;
	this->velocity.x = 0;
	this->velocity.y = 0;
	this->movementSpeed = 1;
	this->gravity = 0.3;
	this->drag = 0.9;
	this->maxVelocity.x = 5.f;
	this->minVelocity.x = 0.1f;

	this->minVelocity.y = 0.f;
	this->maxVelocity.y = 11.f;

	this->moving = false;
	this->state = STATE::DEFAULT;
	this->shooting = false;
	this->isFlipped = false;

	this->reloadTimerMax = 120;
	this->reloadTimer = 140;

	this->shootTimerMax = 80;
	this->shootTimer = 90;


}

void Player::initAudio()
{
	if (!this->shootBuffer.loadFromFile("Sound/pew.mp3"))
	{
		std::cout << "ERROR::PLAYER::INITAUDIO::COULDNT LOAD SOUND" << '\n';
	}
	this->shootSound.setBuffer(this->shootBuffer);

	if (!this->reloadSoundBuffer.loadFromFile("Sound/coverme.mp3"))
	{
		std::cout << "ERROR::PLAYER::INITAUDIO::COULDNT LOAD SOUND" << '\n';
	}
	this->reloadSound.setBuffer(this->reloadSoundBuffer);
}

void Player::initText()
{
	if (!this->font.loadFromFile("Font/Roboto-Black.ttf"))
	{
		std::cout << "ERROR::PLAYER::INITTEXT::COULDNT LOAD FONT" << '\n';
	}
	this->movementText.setFont(this->font);
	this->movementText.setPosition(10, 10);
}

void Player::initCircle()
{
	this->topLeft.setRadius(2.f);
	this->topLeft.setFillColor(sf::Color::White);

	this->topRight = this->topLeft;
	this->bottomLeft = this->topLeft;
	this->bottomRight = this->topLeft;

	sf::FloatRect bounds = this->sprite.getGlobalBounds();

	this->topLeft.setPosition(bounds.left, bounds.top);
	this->topRight.setPosition(bounds.left + bounds.width, bounds.top);
	this->bottomLeft.setPosition(bounds.left, bounds.top + bounds.height);
	this->bottomRight.setPosition(bounds.left + bounds.width, bounds.top + bounds.height);
}

Player::Player()
{
	this->initVariables();
	this->initSprite();
	this->initAudio();
	this->initText();
	this->initCircle();
}

Player::~Player()
{
}

const sf::Vector2f Player::getPosition() const
{
	return this->sprite.getPosition();
}

const sf::Vector2f Player::getVelocity() const
{
	return this->velocity;
}

const sf::FloatRect Player::getGlobalBounds() const
{
	return this->sprite.getGlobalBounds();
}

void Player::updateText()
{
	std::stringstream ss;
	ss << "X : " << this->sprite.getGlobalBounds().left  << " Y : " << this->sprite.getGlobalBounds().top + this->sprite.getGlobalBounds().height << "\n"
		<<"VelX : " << this->velocity.x << " VelY : " << this->velocity.y << '\n';
	this->movementText.setString(ss.str());
}

void Player::updateMaxVelocity()
{
	

	if (std::abs(this->velocity.x) >= this->maxVelocity.x)
	{
		if (this->velocity.x > 0)
		{
			this->velocity.x = this->maxVelocity.x;
		}
		else
		{
			this->velocity.x = -this->maxVelocity.x;
		}
	}

	if (std::abs(this->velocity.x) <= this->minVelocity.x)
	{
		this->velocity.x = 0;
	}
	else
	{
		this->velocity.x *= this->drag;
	}


	if (this->velocity.y >= this->maxVelocity.y)
	{
		this->velocity.y = this->maxVelocity.y;
	}
	this->velocity.y *= this->drag;

	
}

void Player::updateInput(sf::RenderWindow& window)
{
	this->moving = false;
	this->shooting = false;


	//check movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		this->velocity.x -= this->movementSpeed;
		
		this->moving = true;

		if (!this->isFlipped)
		{
			this->sprite.setScale(sf::Vector2f(-this->sprite.getScale().x, this->sprite.getScale().y));
			//this->sprite.move(this->sprite.getGlobalBounds().width, 0.f);
			this->isFlipped = true;
		}

		//this->sprite.setScale(sf::Vector2f(-this->sprite.getScale().x, this->sprite.getScale().y));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		this->velocity.x += this->movementSpeed;
		this->moving = true;

		if (isFlipped)
		{
			this->sprite.setScale(sf::Vector2f(-this->sprite.getScale().x, this->sprite.getScale().y));
			//this->sprite.move(-this->sprite.getGlobalBounds().width, 0.f);
			this->isFlipped = false;
		}

		//this->sprite.setScale(sf::Vector2f(-this->sprite.getScale().x, this->sprite.getScale().y));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		//this->sprite.move(sf::Vector2f(0.f , -this->movementSpeed));
		
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		//this->sprite.move(sf::Vector2f(0.f , this->movementSpeed));
	}

	//check shooting
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		this->shooting = true;
	}
}

void Player::updateMovement(TileMap* tile)
{
	this->sprite.move(this->velocity);

	if (tile->isGrounded(this->sprite.getGlobalBounds()))
	{
		this->velocity.y = 0;
	}
	else
	{
		this->velocity.y += this->gravity;
	}
}

void Player::jump()
{
	this->velocity.y = this->jumpStrength;
}

void Player::updateState()
{
	if (this->moving)
	{
		this->state = STATE::RUN;
	}
	else
	{
		this->state = STATE::DEFAULT;
	}

	if (this->shooting)
	{
		this->state = STATE::SHOOT;
		this->shootTimer = 0;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		if (this->reloadSound.getStatus() != sf::SoundSource::Playing)
		{
			this->reloadSound.play();
		}
		this->state = STATE::RELOAD;
		this->reloadTimer = 0;
	}

	if (this->shootTimer <= this->shootTimerMax)
	{
		this->shootTimer += 1;
		this->state = STATE::SHOOT;
	}

	if (this->reloadTimer <= this->reloadTimerMax)
	{
		this->reloadTimer += 1;
		this->state = STATE::RELOAD;
	}
}

void Player::updateAnimation()
{
	this->animation.update(this->state);

	this->sprite.setTextureRect(this->animation.getFrame());
}

void Player::playSound()
{
	if (this->animation.playShootSound(this->shootSound))
	{
		if (this->shootSound.getStatus() != sf::SoundSource::Playing)
		{
			this->shootSound.play();
		}
	}
}

void Player::updateWindowBoundsCollision(sf::RenderWindow& window)
{
	//check top
	if (this->sprite.getGlobalBounds().top  <= 0)
	{
		this->sprite.setPosition(sf::Vector2f(this->sprite.getPosition().x, 0));
	}
	//Check bottom
	else if (this->sprite.getGlobalBounds().top + this->sprite.getGlobalBounds().height >= window.getSize().y)
	{
		this->sprite.setPosition(sf::Vector2f(this->sprite.getPosition().x, window.getSize().y - this->sprite.getGlobalBounds().height));
		this->velocity.y = 0;
	}

	//Check left side
	
	if (this->sprite.getGlobalBounds().left <= 0)
	{
	
		//if (this->isFlipped)
		//{
		//	this->sprite.setPosition(sf::Vector2f(this->sprite.getGlobalBounds().width, this->sprite.getPosition().y));
		//}
		//else
		//{
		//	this->sprite.setPosition(sf::Vector2f(0, this->sprite.getPosition().y));
		//}
		
		this->sprite.setPosition(sf::Vector2f(this->sprite.getGlobalBounds().width / 2, this->sprite.getPosition().y));
	}
	//Check right side
	else if (this->sprite.getGlobalBounds().left + this->sprite.getGlobalBounds().width >= window.getSize().x)
	{
		//if (this->isFlipped)
		//{
		//	this->sprite.setPosition(sf::Vector2f(window.getSize().x, this->sprite.getPosition().y));
		//}
		//else
		//{
		//	this->sprite.setPosition(sf::Vector2f(window.getSize().x - this->sprite.getGlobalBounds().width, this->sprite.getPosition().y));
		//}


		this->sprite.setPosition(sf::Vector2f((window.getSize().x - this->sprite.getGlobalBounds().width / 2), this->sprite.getPosition().y));
	}
}

void Player::updateCircle()
{
	this->topLeft.setPosition(this->sprite.getGlobalBounds().left, this->sprite.getPosition().y);

	this->topRight.setPosition(this->sprite.getGlobalBounds().left + this->sprite.getGlobalBounds().width, this->sprite.getPosition().y);

	this->bottomLeft.setPosition(this->sprite.getGlobalBounds().left, this->sprite.getGlobalBounds().top + this->sprite.getGlobalBounds().height);

	this->bottomRight.setPosition(this->sprite.getGlobalBounds().left + this->sprite.getGlobalBounds().width, this->sprite.getGlobalBounds().top + this->sprite.getGlobalBounds().height);
}



void Player::move(sf::Vector2f offset)
{
	this->sprite.move(offset);
}

void Player::update(sf::RenderWindow& window, TileMap* tile)
{
	this->updateText();
	this->updateInput(window);
	this->updateMaxVelocity();
	
	this->updateMovement(tile);

	this->updateCircle();

	this->updateState();
	this->updateAnimation();

	this->playSound();

	this->updateWindowBoundsCollision(window);

}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->movementText);

	target.draw(this->sprite);

	//target.draw(this->topLeft);
	//target.draw(this->topRight);
	//target.draw(this->bottomLeft);
	//target.draw(this->bottomRight);
	
	//target.draw(this->ground);
}
