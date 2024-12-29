#pragma once


enum STATE {DEFAULT = 0, IDLE, RUN, SHOOT, RELOAD, DEAD};

class Animation
{
private:



	sf::IntRect currentFrame;



	sf::Vector2i idleSize;
	int idleHeight;
	std::vector<int> idlePosX;

	sf::Vector2i runSize;
	int runHeight;
	std::vector<int> runPosX;

	sf::Vector2i shootSize;
	int shootHeight;
	std::vector<int> shootPosX;

	sf::Vector2i reloadSize;
	int reloadHeight;
	std::vector<int> reloadPosX;




	int idleTimerMax;
	int idleTimer;
	int idleFrameCount;

	int runTimer;
	int runTimerMax;
	int runFrameCount;

	int shootFrameCount;
	int shootTimerMax;
	int shootTimer;

	int reloadFrameCount;
	int reloadTimerMax;
	int reloadTimer;


	void initVariables();
	void initPositions();
	void initCircle();

public:
	Animation();
	Animation(int posX, int posY, int width, int height);
	~Animation();

	//Accessors
	const sf::IntRect getFrame() const;
	void update(int state);
	const bool playShootSound(sf::Sound sound) const;
};

