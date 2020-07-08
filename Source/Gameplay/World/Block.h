#pragma once
#include <SFML/Graphics.hpp>

struct Block_properties
{
	bool isSolid       = false;
	bool isBreakable   = false;
	bool isTransparent = false;
};

class Block : public sf::Drawable
{
public:
	Block() {};
	Block(const sf::Texture& texture, Block_properties& properties, sf::Vector2f position);

	sf::FloatRect getRect() { return m_sprite.getGlobalBounds(); }

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::Sprite m_sprite;
	Block_properties* m_p_properties;
};