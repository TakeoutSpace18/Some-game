#include "Level.h"
#include <iostream>

Level::Level(Application& app) : m_p_application(&app)
{
	load(1);
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

		for (auto layer : json_file["layers"])
		{
			if (layer["type"] == "tilelayer")
			{
				sf::VertexArray vertices{ sf::Quads, std::size_t(m_level_size.x * m_level_size.y * 4) };

				int cur_x = 0, cur_y = 0, index = 0;

				for (auto id : layer["data"])
				{
					if (id != 0)
					{
						sf::Vertex* quad = &vertices[index];

						quad[0].position = sf::Vector2f(cur_x * block_size, cur_y * block_size);
						quad[1].position = sf::Vector2f((cur_x + 1) * block_size, cur_y * block_size);
						quad[2].position = sf::Vector2f((cur_x + 1) * block_size, (cur_y + 1) * block_size);
						quad[3].position = sf::Vector2f(cur_x * block_size, (cur_y + 1) * block_size);

						sf::Vector2u block_uv = tileset.getBlockUV(id - 1);

						quad[0].texCoords = sf::Vector2f(block_uv.x, block_uv.y);
						quad[1].texCoords = sf::Vector2f(block_uv.x + block_size, block_uv.y);
						quad[2].texCoords = sf::Vector2f(block_uv.x + block_size, block_uv.y + block_size);
						quad[3].texCoords = sf::Vector2f(block_uv.x, block_uv.y + block_size);

						index += 4;
					}

					cur_x++;
					if (cur_x == m_level_size.x)
					{
						cur_x = 0;
						cur_y++;
					}
				}
				vertices.resize(index);
				m_layers.push_back(std::move(vertices));
			}
		}
	}
	else
		throw std::runtime_error("Failed to load level" + std::to_string(level_id));
}

void Level::render()
{
	for (auto layer : m_layers)
	{
		m_p_application->draw(layer, m_renderstates);
	}
}