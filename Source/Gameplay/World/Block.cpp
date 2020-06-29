#include "Block.h"

Block::Block(const sf::Texture& texture, Block_properties& properties, sf::Vector2f position)
	: m_p_properties(&properties)
{
	m_sprite.setTexture(texture);
	m_sprite.setPosition(position);
}

void Block::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_sprite, states);
}