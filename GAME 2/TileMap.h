#pragma once
#include "stdafx.h"
#include "Tile.h"

class TileMap
{
private:

	std::vector<std::vector<Tile*>> tiles;
	sf::Texture* tileSheet;
	unsigned tileSize;

public:
	TileMap();
	TileMap(unsigned width, unsigned height, sf::Texture* tile_sheet, unsigned tileSize);
	~TileMap();

	//Inline function
	inline const unsigned& getTileSize() { return this->tileSize; };

	//Functions
	void addTile(unsigned x, unsigned y);
	void removeTile(unsigned x, unsigned y);
	bool isGrounded(sf::FloatRect playerBounds);

	const sf::Vector2f update(sf::FloatRect playerBounds) const;
	void render(sf::RenderTarget& target);
};

