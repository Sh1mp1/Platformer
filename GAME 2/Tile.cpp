#include "stdafx.h"
#include "Tile.h"

Tile::Tile()
{

}

Tile::Tile(const unsigned& posX,const unsigned& posY, const int& tile_Size, sf::Texture* texture_sheet, sf::IntRect texture_rect, bool damaging)
{
	if (!texture_sheet)
	{
		throw std::runtime_error("Texture sheet is null!");
	}
	this->texture = *texture_sheet;
	this->textureRect = texture_rect;
	this->sprite.setTexture(this->texture);
	this->sprite.setTextureRect(this->textureRect);
	this->damaging = damaging;

	this->sprite.setPosition(sf::Vector2f(posX * tile_Size, posY * tile_Size));
	this->position = sf::Vector2f(posX * tile_Size, posY * tile_Size);
}

Tile::~Tile()
{
}

const sf::FloatRect Tile::getGlobalBounds() const
{

	return this->sprite.getGlobalBounds();
}

const sf::Vector2f Tile::getPosition() const
{
	return this->position;
}



void Tile::update()
{
}

void Tile::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
