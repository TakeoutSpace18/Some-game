#include "Level.h"

Level::Level(Application& app) : m_p_application(&app) 
{
	m_tileset.load(1);
	m_blocks.push_back(m_tileset.getBlock(0, sf::Vector2f(20, 20)));
	m_blocks.push_back(m_tileset.getBlock(2, sf::Vector2f(40, 40)));
	m_blocks.push_back(m_tileset.getBlock(1, sf::Vector2f(40, 20)));
	m_blocks.push_back(m_tileset.getBlock(2, sf::Vector2f(60, 40)));
	m_blocks.push_back(m_tileset.getBlock(0, sf::Vector2f(40, 60)));
	m_blocks.push_back(m_tileset.getBlock(1, sf::Vector2f(20, 40)));
}

void Level::load(unsigned char id)
{
	
}

void Level::render()
{
	for (int i = 0; i < m_blocks.size(); i++)
		m_p_application->draw(m_blocks[i]);
}