#include "stdafx.h"
#include "Game.h"

void Game::initWindow()
{
	this->window.create(sf::VideoMode(800, 600), "GAME", sf::Style::Titlebar | sf::Style::Close);
	this->window.setFramerateLimit(144);
	this->window.setVerticalSyncEnabled(true);


	this->ground.setPosition(sf::Vector2f(0, 599));
	this->ground.setSize(sf::Vector2f(this->window.getSize().x, this->window.getSize().y));
}

void Game::initInput()
{
	this->mouseKeybinds["ADD_TILE"] = sf::Mouse::XButton1;
	this->mouseKeybinds["REMOVE_TILE"] = sf::Mouse::Right;
}

void Game::initPlayer()
{
	this->player = new Player();

	this->playerJumpTimerMax = 20;
	this->playerJumpTimer = this->playerJumpTimerMax;
}

void Game::initText()
{
	
	if (!this->font.loadFromFile("Font/Roboto-Black.ttf"))
	{
		std::cout << "ERROR::GAME::INITTEXT::COULDNT LOAD TEXT" << '\n';
	}
	sf::Text menuStartText;
	sf::Text menuExitText;

	menuStartText.setFont(this->font);
	menuStartText.setPosition(sf::Vector2f(100, 200));
	menuStartText.setFillColor(sf::Color::Yellow);
	

	menuExitText.setFont(this->font);
	menuExitText.setPosition(sf::Vector2f(100, 300));
	menuExitText.setFillColor(sf::Color::Yellow);
	
	menuStartText.setString("START");
	menuExitText.setString("EXIT");

	this->menuText.push_back(menuStartText);
	this->menuText.push_back(menuExitText);

	this->uiHasPlayed.push_back(false);
	this->uiHasPlayed.push_back(false);
}

void Game::initMenuBackground()
{
	this->backgroundTexture.loadFromFile("Textures/menuBackground.png");

	this->menuBackground.setTexture(this->backgroundTexture);
	this->menuBackground.setScale(sf::Vector2f(0.86, 0.86));
	
}

void Game::initAudio()
{
	if (!this->startSoundBuffer.loadFromFile("Sound/start.mp3"))
	{
		std::cout << "ERROR::GAME::INITAUDIO::COULDNT LOAD AUDIO" << '\n';
	}
	this->startSound.setBuffer(this->startSoundBuffer);

	if (!this->uiSoundBuffer.loadFromFile("Sound/ui.mp3"))
	{
		std::cout << "ERROR::GAME::INITAUDIO::COULDNT LOAD AUDIO" << '\n';
	}
	this->uiSound.setBuffer(this->uiSoundBuffer);
}

void Game::initTileSheet()
{
	if (!this->tileSheet.loadFromFile("Textures/block.png"))
	{
		std::cout << "ERROR::PLAYER::INITTEXTURES::COULDNT INITIALIZE TEXTURE SHEET" << "\n";
	}
}


void Game::initTileMap()
{
	this->tileMap = new TileMap(20, 20, &this->tileSheet, 50);

}

Game::Game()
{
	this->initWindow();
	this->initInput();
	this->initPlayer();
	this->initText();
	this->initMenuBackground();
	this->initAudio();
	this->initTileSheet();
	this->initTileMap();
}

Game::~Game()
{
	delete this->player;

	delete this->tileMap;
}

const sf::RenderWindow& Game::getWindow() const
{
	return this->window;
}

void Game::pollEvents()
{
	sf::Event e;
	while (this->window.pollEvent(e))
	{
		switch (e.type)
		{
		case sf::Event::Closed:
			this->window.close();
			break;

		case sf::Event::KeyPressed:
			if (e.key.code == sf::Keyboard::Escape)
			{
				this->window.close();
			}
			break;
		}
	}
}

bool Game::canJump()
{
	if (this->player->getGlobalBounds().intersects(this->ground.getGlobalBounds()) || this->tileMap->isGrounded(this->player->getGlobalBounds()))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Game::updateTileMap()
{
	this->player->move(this->tileMap->update(this->player->getGlobalBounds()));

	sf::Vector2f move = this->tileMap->update(this->player->getGlobalBounds());
	
}

void Game::updateMousePos()
{
	this->mousePos = sf::Mouse::getPosition();

	this->mouseView = this->window.mapPixelToCoords(this->mousePos);
}

void Game::updateInput()
{

	int mouseX = int(sf::Mouse::getPosition(this->window).x) / int(this->tileMap->getTileSize());
	int mouseY = int(sf::Mouse::getPosition(this->window).y) / int(this->tileMap->getTileSize());


	if (sf::Mouse::isButtonPressed(this->mouseKeybinds["ADD_TILE"]))
	{
		this->tileMap->addTile(mouseX, mouseY);
	}
	else if (sf::Mouse::isButtonPressed(this->mouseKeybinds["REMOVE_TILE"]))
	{
		this->tileMap->removeTile(mouseX, mouseY);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (this->canJump() && this->playerJumpTimer >= this->playerJumpTimerMax)
		{
			this->player->jump();
			this->playerJumpTimer = 0;
		}
	}

	if (this->playerJumpTimer <= this->playerJumpTimerMax)
	{
		this->playerJumpTimer++;
	}
}



void Game::update()
{
	this->pollEvents();

	this->updateMousePos();

	this->updateInput();

	this->player->update(this->window, this->tileMap);

	this->updateTileMap();
}

void Game::renderTileMap()
{
	this->tileMap->render(this->window);
} 

void Game::render()
{
	this->window.clear();

	this->renderTileMap();

	this->player->render(this->window);

	this->window.display();
}

void Game::renderMenuBackground()
{
	this->window.clear();

	this->window.draw(this->menuBackground);

	for (auto& i : this->menuText)
	{
		this->window.draw(i);
	}

	this->window.display();
}

void Game::updateMenuBackground(sf::Vector2f mouse)
{
	for (int i = 0; i <  this->menuText.size(); i++)
	{
		if (menuText[i].getGlobalBounds().contains(mouse))
		{
			this->menuText[i].setFillColor(sf::Color::Black);

			if (!this->uiHasPlayed[i])
			{
				this->uiSound.play();
				this->uiHasPlayed[i] = true;
			}
		}
		else
		{
			this->menuText[i].setFillColor(sf::Color::Yellow);
			this->uiHasPlayed[i] = false;
		}
	}
	this->renderMenuBackground();
}


void Game::run()
{
	sf::sleep(sf::seconds(0.3));
	this->startSound.play();
	while (this->window.isOpen())
	{
		this->update();

		this->render();
	}
}

void Game::start()
{
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	while (this->window.isOpen())
	{
		 mousePosWindow = sf::Mouse::getPosition(this->window);
		 mousePosView = this->window.mapPixelToCoords(mousePosWindow);

		 this->updateMenuBackground(mousePosView);

		sf::Event e;
		while (this->window.pollEvent(e))
		{
			switch (e.type)
			{
			case sf::Event::Closed:
				this->window.close();
				break;

			case sf::Event::KeyPressed:
				if (e.key.code == sf::Keyboard::Escape)
				{
					this->window.close();
				}
				break;

			case sf::Event::MouseButtonPressed:
				if (e.key.code == sf::Mouse::Left)
				{
					if (this->menuText[0].getGlobalBounds().contains(mousePosView))
					{
						this->run();
					}

					else if (this->menuText[1].getGlobalBounds().contains(mousePosView))
					{
						this->window.close();
					}
				}
				break;
			}
		}
	}
}
