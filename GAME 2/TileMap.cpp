#include "stdafx.h"
#include "TileMap.h"

TileMap::TileMap()
{
	this->tileSheet = nullptr;
	this->tileSize = 0;
	
}

TileMap::TileMap(unsigned width, unsigned height, sf::Texture* tile_sheet, unsigned tileSize)
{
	//Initialize tilemap

	//0  1   2  3  4 5  6  7  8     //Size of the vector containing a vector (width)
	//[] [] [] [] [] [] [] [] []	//Size of the individual vectors is height
	//[] [] [] [] [] [] [] [] []
	//[] [] [] [] [] [] [] [] []
	//[] [] [] [] [] [] [] [] []
	//[] [] [] [] [] [] [] [] []
	this->tiles.resize(width);
	for (int i = 0; i < this->tiles.size(); i++)
	{
		this->tiles[i].resize(height, nullptr);	
	}

	this->tileSize = tileSize;
	this->tileSheet = tile_sheet;
}

TileMap::~TileMap()
{
	for (int i = 0; i < this->tiles.size(); i++)
	{
		for (int j = 0; j < this->tiles[i].size(); j++)
		{
			delete this->tiles[i][j];
		}
	}
}

void TileMap::addTile(unsigned x, unsigned y)
{
	//Return if out of range
	if (x >= this->tiles.size() && x >= 0)
	{
		return;
	}
	if (y >= this->tiles[x].size() && y >= 0)
	{
		return;
	}

	//Add tile
	if (this->tiles[x][y] == nullptr)
	{
		this->tiles[x][y] = new Tile(x, y, this->tileSize,this->tileSheet,  sf::IntRect(0, 0, this->tileSize, this->tileSize), false);
		//this->tiles[x][y] = new Tile(x ,y, this->tileSize, this->tileSheet, sf::IntRect(45, 191, 50, 63), false);
	}
}

void TileMap::removeTile(unsigned x, unsigned y)
{
	//Return if out of range
	if (x >= this->tiles.size() && x >= 0)
	{
		return;
	}
	if (y >= this->tiles[x].size() && y >= 0)
	{
		return;
	}

	//Remove tile
	if (this->tiles[x][y] != nullptr)
	{
		this->tiles[x][y] = nullptr;
		delete this->tiles[x][y];
	}
}



bool TileMap::isGrounded(sf::FloatRect playerBounds)
{
	for (int i = 0; i < this->tiles.size(); i++)
	{
		for (int j = 0; j < this->tiles[i].size(); j++)
		{
			if (this->tiles[i][j] != nullptr)
			{
				sf::FloatRect tileBounds = this->tiles[i][j]->getGlobalBounds();
				std::cout << tileBounds.top << '\n';

				if (tileBounds.intersects(playerBounds))
				{
					if (int (playerBounds.top + playerBounds.height) <= int (tileBounds.top))
					{
						std::cout << "#######";
						return true;
					}
				}
			}
		}
	}
	return false;
}

const sf::Vector2f TileMap::update(sf::FloatRect playerBounds) const
{
	for (int i = 0; i < this->tiles.size(); i++)
	{
		for (int j = 0; j < this->tiles[i].size(); j++)
		{
			if (this->tiles[i][j] != nullptr)
			{
				//Check intersection
				if (this->tiles[i][j]->getGlobalBounds().intersects(playerBounds))
				{
					sf::FloatRect obstacleBounds = this->tiles[i][j]->getGlobalBounds();

					//Check overlap on each side
					float overlapLeft = playerBounds.left + playerBounds.width - obstacleBounds.left;
					float overlapRight = obstacleBounds.left + obstacleBounds.width - playerBounds.left;
					float overlapTop = playerBounds.top + playerBounds.height - obstacleBounds.top;
					float overlapBottom = obstacleBounds.top + obstacleBounds.height - playerBounds.top;

					// check which side has minimum overlap
					float smallestOverlap = std::min({ overlapLeft, overlapRight, overlapTop, overlapBottom });

					if (smallestOverlap == overlapLeft) {
						return sf::Vector2f(-overlapLeft, 0);
					}
					else if (smallestOverlap == overlapRight) {
						
						return sf::Vector2f(overlapRight, 0);
					}
					else if (smallestOverlap == overlapTop) {
						//std::cout << obstacleBounds.top << '\n';
						return sf::Vector2f(0, -overlapTop);
					}
					else if (smallestOverlap == overlapBottom) {
						return sf::Vector2f(0, overlapBottom);
					}
				}
			}
			
		}
	}
	return sf::Vector2f(0, 0);
}

void TileMap::render(sf::RenderTarget& target)
{
	for (int i = 0; i < this->tiles.size(); i++)
	{
		for (int j = 0; j < this->tiles[i].size(); j++)
		{
			if (this->tiles[i][j] != nullptr)
			{
				this->tiles[i][j]->render(target);
			}
		}
	}
}


