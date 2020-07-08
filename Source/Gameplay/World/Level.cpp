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
		m_tileset = TilesetManager(source[source.length() - 6] - '0');

		m_level_size = sf::Vector2i(json_file["width"].get<int>(), json_file["height"].get<int>());

		for (auto layer : json_file["layers"])
		{
			if (layer["type"] == "tilelayer")
			{
				Block** matrix;
				matrix = new Block * [m_level_size.x];
				for (int i = 0; i < m_level_size.x; i++)
					matrix[i] = new Block[m_level_size.y];

				int block_size = json_file["tileheight"];

				int cur_x = 0, cur_y = 0;

				for (auto id : layer["data"])
				{
					if (id != 0)
					{
						matrix[cur_x][cur_y] = m_tileset.getBlock(id - 1, sf::Vector2f(cur_x * block_size, cur_y * block_size));
					}
					cur_x++;
					if (cur_x == m_level_size.x)
					{
						cur_x = 0;
						cur_y++;
					}
				}

				m_layers.push_back(std::move(matrix));

				//std::vector<Block> blocks;

				//int block_size = json_file["tileheight"];

				//int cur_x = 0, cur_y = 0;

				//int counter = 0;

				//for (auto id : layer["data"])
				//{
				//	if (id != 0)
				//	{
				//		m_layers.push_back(m_tileset.getBlock(id - 1, sf::Vector2f(cur_x * block_size, cur_y * block_size)));
				//		counter++;
				//	}
				//	cur_x++;
				//	if (cur_x == m_level_size.x)
				//	{
				//		cur_x = 0;
				//		cur_y++;
				//	}
				//}
				//std::cout << counter << std::endl;

				////m_layers.push_back(std::move(blocks));

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
		for (int x = 0; x < m_level_size.x; x++)
		{
			for (int y = 0; y < m_level_size.y; y++)
			{
				m_p_application->draw(layer[x][y]);
			}
		}
	}

	//for (auto layer : m_layers)
	//{
	//	m_p_application->draw(layer);
	//}
}