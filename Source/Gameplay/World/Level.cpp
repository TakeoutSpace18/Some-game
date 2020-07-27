#include "Level.h"
#include <iostream>

#include "../../Resourse_Managers/TilesetManager.h"

Level::Level(Application& app) : m_p_application(&app)
{
}

void Level::load(short level_id)
{
	std::ifstream input("data\\levels\\level_" + std::to_string(level_id) + ".json");
	if (input.is_open())
	{
		json json_file;
		input >> json_file;
		input.close();

		std::string source = json_file["tilesets"][0]["source"].get<std::string>();
		TilesetManager tileset = TilesetManager(source[source.length() - 6] - '0', *m_p_application);
		m_renderstates.texture = &m_p_application->getTexture(Textures::Tileset);

		m_level_size = sf::Vector2i(json_file["width"].get<int>(), json_file["height"].get<int>());
		int block_size = json_file["tileheight"];

		bool** solid_blocks_map;
		solid_blocks_map = new bool * [m_level_size.x];
		for (int i = 0; i < m_level_size.x; i++)
		{
			solid_blocks_map[i] = new bool[m_level_size.y];
			for (int j = 0; j < m_level_size.y; j++)
			{
				solid_blocks_map[i][j] = false;
			}
		}
			
		for (auto &layer : json_file["layers"])
		{
			if (layer["type"] == "tilelayer")
			{
				sf::VertexArray vertices{ sf::Quads, std::size_t(m_level_size.x * m_level_size.y * 4) };

				sf::Vector2i block_pos{ 0, 0 };
				int index = 0;

				for (short id : layer["data"])
				{
					if (id != 0)
					{
						id--; //tileset ids start with zero

						sf::Vertex* quad = &vertices[index];

						quad[0].position = sf::Vector2f(block_pos.x, block_pos.y);
						quad[1].position = sf::Vector2f(block_pos.x + block_size, block_pos.y);
						quad[2].position = sf::Vector2f(block_pos.x + block_size, block_pos.y + block_size);
						quad[3].position = sf::Vector2f(block_pos.x, block_pos.y + block_size);

						sf::Vector2u block_uv = tileset.getBlockUV(id);

						quad[0].texCoords = sf::Vector2f(block_uv.x, block_uv.y);
						quad[1].texCoords = sf::Vector2f(block_uv.x + block_size, block_uv.y);
						quad[2].texCoords = sf::Vector2f(block_uv.x + block_size, block_uv.y + block_size);
						quad[3].texCoords = sf::Vector2f(block_uv.x, block_uv.y + block_size);

						index += 4;

						if (tileset.getBlockProperties(id).isSolid)
						{
							solid_blocks_map[block_pos.x / block_size][block_pos.y / block_size] = true;
						}

						if (tileset.getBlockProperties(id).isAnimated)
						{
							m_animated_blocks.push_back(AnimatedBlock(id, *quad, *m_p_application));
						}

					}

					block_pos.x += block_size;

					if (block_pos.x == m_level_size.x * block_size)
					{
						block_pos.x = 0;
						block_pos.y += block_size;
					}
				}
				vertices.resize(index);
				m_layers.push_back(std::move(vertices));
			}
		}

		// collision rects merge
		sf::Vector2f pos, size;

		for (int y = 0; y < m_level_size.y; y++)
		{
			for (int x = 0; x < m_level_size.x - 1; x++)
			{
				if (solid_blocks_map[x][y] && solid_blocks_map[x + 1][y])
				{
					pos = sf::Vector2f(x,y);
					pos *= (float)block_size;

					do
					{
						solid_blocks_map[x][y] = false;
						x++;
						if (x == m_level_size.x)
							break;
					} while (solid_blocks_map[x][y]);

					size = sf::Vector2f(x * block_size - pos.x, block_size);
					m_collision_rects.push_back(sf::FloatRect(pos, size));
				}
			}
		}

		for (int x = 0; x < m_level_size.x; x++)
		{
			for (int y = 0; y < m_level_size.y; y++)
			{
				if (solid_blocks_map[x][y])
				{
					pos = sf::Vector2f(x, y);
					pos *= (float)block_size;

					while (solid_blocks_map[x][y])
					{	
						y++;
						if (y == m_level_size.y)
							break;
					}

					size = sf::Vector2f(block_size, y * block_size - pos.y);
					m_collision_rects.push_back(sf::FloatRect(pos, size));
				}
			}
		}

		for (int i = 0; i < m_level_size.x; i++)
			delete[] solid_blocks_map[i];
		delete[] solid_blocks_map;
	}
	else
		throw std::runtime_error("Failed to load level" + std::to_string(level_id));
}

void Level::update()
{
	for (auto &animated_block : m_animated_blocks)
	{
		animated_block.update();
	}
}

void Level::render()
{
	for (auto &layer : m_layers)
	{
		m_p_application->draw(layer, m_renderstates);
	}

	/*for (auto &rect : m_visible_rects)
	{
		m_p_application->draw(rect);
	}*/
}

void Level::setScale(float scale)
{
	m_visible_rects.clear(); //DEBUG//

	scale *= 2;

	float factor = scale / getScale().x;

	for (int i = 0; i < m_collision_rects.size(); i++)
	{
		m_collision_rects[i].left   *= factor;
		m_collision_rects[i].top    *= factor;
		m_collision_rects[i].width  *= factor;
		m_collision_rects[i].height *= factor;

		//DEBUG//
		sf::RectangleShape rect_shape = sf::RectangleShape(sf::Vector2f(m_collision_rects[i].width, m_collision_rects[i].height));
		rect_shape.setPosition(m_collision_rects[i].left, m_collision_rects[i].top);
		rect_shape.setOutlineColor(sf::Color::Red);
		rect_shape.setFillColor(sf::Color(0, 0, 0, 0));
		rect_shape.setOutlineThickness(-1);
		m_visible_rects.push_back(rect_shape);
		//DEBUG//
	}

	sf::Transformable::setScale(scale, scale);
	m_renderstates.transform = getTransform();
}
