#pragma once
class Tile
{
private:

	sf::Texture texture;
	sf::IntRect textureRect;
	sf::Sprite sprite;
	bool damaging;
	sf::Vector2f position;
	

public:
	Tile();
	Tile(const unsigned& posX,const unsigned& posY, const int&  tile_Size, sf::Texture* texture_sheet, sf::IntRect texture_rect, bool damaging = false);
	~Tile();

	//Accessors
	const sf::FloatRect getGlobalBounds() const;
	const sf::Vector2f getPosition() const;

	void update();
	void render(sf::RenderTarget& target);
};

