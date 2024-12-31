#pragma once
#include "stdafx.h"
#include "Player.h"
#include "TileMap.h"
class Game
{
private:



	sf::RenderWindow window;
	sf::RectangleShape ground;

	sf::SoundBuffer startSoundBuffer;
	sf::Sound startSound;

	sf::SoundBuffer uiSoundBuffer;
	sf::Sound uiSound;

	std::vector<bool> uiHasPlayed;
	
	//Player
	Player* player;
	int playerJumpTimerMax;
	int playerJumpTimer;

	//Textures
	sf::Texture backgroundTexture;
	sf::Sprite menuBackground;
	sf::Texture tileSheet;

	sf::Font font;
	std::vector<sf::Text> menuText;

	//TileMap
	TileMap* tileMap;

	//Binds
	std::map <std::string, sf::Mouse::Button> mouseKeybinds;

	sf::Vector2i mousePos;
	sf::Vector2f mouseView;


	void initWindow();
	void initInput();
	void initPlayer();
	void initText();
	void initMenuBackground();
	void initAudio();
	void initTileSheet();
	void initTileMap();
	

public:
	Game();
	~Game();


	//Accessors
	const sf::RenderWindow& getWindow() const;


	//Functions
	void pollEvents();
	bool canJump();

	void updateTileMap();
	void updateMousePos();
	void updateInput();
	void update();

	void renderTileMap();
	void render();


	//Start menu
	void renderMenuBackground();
	void updateMenuBackground(sf::Vector2f mouse);
	void start();


	void run();
};

