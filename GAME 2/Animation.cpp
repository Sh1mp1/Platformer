#include "stdafx.h"
#include "Animation.h"



void Animation::initVariables()
{
	this->runTimerMax = 20;
	this->runTimer = this->runTimerMax;
	this->runFrameCount = 0;

	this->shootFrameCount = 0;
 

	this->idleTimerMax = 20;
	this->idleTimer = this->idleTimerMax;
	this->idleFrameCount = 0;

	this->shootTimerMax = 20;
	this->shootTimer = 0;
	this->shootFrameCount = 0;

	this->reloadTimerMax = 20;
	this->reloadTimer = this->reloadTimerMax;
	this->reloadFrameCount = 0;
}

void Animation::initPositions()
{
	//IDLE
	this->idleSize = sf::Vector2i(50, 63);
	this->idleHeight = 191;
	this->idlePosX.push_back(45);
	this->idlePosX.push_back(172);
	this->idlePosX.push_back(300);
	this->idlePosX.push_back(428);
	this->idlePosX.push_back(556);
	this->idlePosX.push_back(684);
	this->idlePosX.push_back(812);


	//RUNNING
	this->runSize = sf::Vector2i(42, 66);
	this->runHeight = 446;
	this->runPosX.push_back(45);
	this->runPosX.push_back(157);
	this->runPosX.push_back(293);
	this->runPosX.push_back(420);
	this->runPosX.push_back(543);
	this->runPosX.push_back(677);


	//Shooting
	this->shootSize = sf::Vector2i(71, 66);
	this->shootHeight = 574;
	this->shootPosX.push_back(43);
	this->shootPosX.push_back(171);
	this->shootPosX.push_back(300);
	this->shootPosX.push_back(428);

	//Reloading
	this->reloadSize = sf::Vector2i(42, 80);
	this->reloadHeight = 818;
	this->reloadPosX.push_back(45);
	this->reloadPosX.push_back(169);
	this->reloadPosX.push_back(299);
	this->reloadPosX.push_back(426);
	this->reloadPosX.push_back(554);
	this->reloadPosX.push_back(682);
	this->reloadPosX.push_back(811);
	this->reloadPosX.push_back(935);
}

Animation::Animation()
{
	this->currentFrame = sf::IntRect(0, 0, 0, 0);
	this->initVariables();
	this->initPositions();
}

Animation::Animation(int posX, int posY, int width, int height)
{
	this->currentFrame = sf::IntRect(posX, posY, width, height);
	this->initVariables();
	this->initPositions();
}

Animation::~Animation()
{
}

const sf::IntRect Animation::getFrame() const
{
	return this->currentFrame;
}

void Animation::update(int state)
{
	if (state == STATE::DEFAULT || state == STATE::IDLE)
	{
		this->idleTimer += 1;
		
		if (this->idleTimer >= this->idleTimerMax)
		{
			this->currentFrame.left = this->idlePosX[this->idleFrameCount];
			this->currentFrame.top = this->idleHeight;
			this->currentFrame.width = this->idleSize.x;
			this->currentFrame.height = this->idleSize.y;
			this->idleTimer = 0;
			this->idleFrameCount += 1;
		}

		if (this->idleFrameCount >= this->idlePosX.size())
		{
			this->idleFrameCount = 0;
		}
	}
	else
	{
		this->idleFrameCount = 0;
	}


	if (state == STATE::RUN)
	{
		this->runTimer += 1;

		if (runTimer >= runTimerMax)
		{
			this->currentFrame.left = this->runPosX[this->runFrameCount];
			this->currentFrame.top = this->runHeight;
			//this->currentFrame.width = this->runSize.x;
			//this->currentFrame.height = this->runSize.y;
			this->runTimer = 0;
			this->runFrameCount += 1;
		}

		if (this->runFrameCount >= this->runPosX.size())
		{
			this->runFrameCount = 0;
		}
	}
	else
	{
		this->runFrameCount = 0;
	}

	if (state == STATE::SHOOT)
	{
		this->shootTimer += 1;

		if (this->shootTimer >= this->shootTimerMax)
		{
			this->currentFrame.left = this->shootPosX[this->shootFrameCount];
			this->currentFrame.top = this->shootHeight;
			//this->currentFrame.width = this->shootSize.x;
			//this->currentFrame.height = this->shootSize.y;
			this->shootTimer = 0;
			this->shootFrameCount += 1;
		}

		if (this->shootFrameCount >= this->shootPosX.size())
		{
			this->shootFrameCount = 0;
		}

		
	}
	else
	{
		this->shootFrameCount = 0;
	}

	if (state == STATE::RELOAD)
	{
		this->reloadTimer += 1;
		if (this->reloadTimer >= this->reloadTimerMax)
		{
			this->currentFrame.left = this->reloadPosX[this->reloadFrameCount];
			this->currentFrame.top = this->reloadHeight;
			//this->currentFrame.width = this->reloadSize.x;
			//this->currentFrame.height = this->reloadSize.y;
			this->reloadTimer = 0;
			this->reloadFrameCount += 1;
		}

		if (this->reloadFrameCount >= this->reloadPosX.size())
		{
			this->reloadFrameCount = 0;
		}
	}
	else
	{
		this->reloadFrameCount = 0;
	}
}

const bool Animation::playShootSound(sf::Sound sound) const
{
	if (this->shootFrameCount == 2 && sound.getStatus() != sf::SoundSource::Playing)
	{
		return true;
	}
	else
	{
		return false;
	}
}
