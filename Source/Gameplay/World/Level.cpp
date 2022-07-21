#include "Level.h"

#include <iostream>

#include "Resourse_Managers/TilesetManager.h"
#include "Constants.hpp"
#include "Window.h"

Level::Level(Application& app) : _application(&app) {}

void Level::load(short level_id) {
    std::ifstream input("data/levels/level_" + std::to_string(level_id) + ".json");
    if (input.is_open()) {
        json json_file;
        input >> json_file;
        input.close();

        std::string source = json_file["tilesets"][0]["source"].get<std::string>();
        TilesetManager tileset = TilesetManager(source[source.length() - 6] - '0',
                                                Textures::Level_tileset, *_application);

        for (auto i = 0; i <= 29; i++) {
            if (tileset.getBlockProperties(i).hasCollision) {
                for (auto& rect : tileset.getBlockCollisions(i)) {
                    std::cout << rect.left << " " << rect.top << " " << rect.width << " "
                              << rect.height << std::endl;
                }
                std::cout << std::endl;
            }
        }

        _renderstates.texture = &_application->getTexture(Textures::Level_tileset);

        _level_size = sf::Vector2i(json_file["width"].get<int>(), json_file["height"].get<int>());
        int block_size = json_file["tileheight"];

        bool** solid_blocks_map;
        solid_blocks_map = new bool*[_level_size.x];
        for (int i = 0; i < _level_size.x; i++) {
            solid_blocks_map[i] = new bool[_level_size.y];
            for (int j = 0; j < _level_size.y; j++) {
                solid_blocks_map[i][j] = false;
            }
        }

        for (auto& layer : json_file["layers"]) {
            if (layer["type"] == "tilelayer") {
                sf::VertexArray vertices{sf::Quads, std::size_t(_level_size.x * _level_size.y * 4)};

                sf::Vector2i block_pos{0, 0};
                int index = 0;

                for (short id : layer["data"]) {
                    if (id != 0) {
                        id--;  // tileset ids start with zero

                        sf::Vertex* quad = &vertices[index];

                        quad[0].position = sf::Vector2f(block_pos.x, block_pos.y);
                        quad[1].position = sf::Vector2f(block_pos.x + block_size, block_pos.y);
                        quad[2].position =
                            sf::Vector2f(block_pos.x + block_size, block_pos.y + block_size);
                        quad[3].position = sf::Vector2f(block_pos.x, block_pos.y + block_size);

                        sf::Vector2u block_uv = tileset.getBlockUV(id);

                        quad[0].texCoords = sf::Vector2f(block_uv.x, block_uv.y);
                        quad[1].texCoords = sf::Vector2f(block_uv.x + block_size, block_uv.y);
                        quad[2].texCoords =
                            sf::Vector2f(block_uv.x + block_size, block_uv.y + block_size);
                        quad[3].texCoords = sf::Vector2f(block_uv.x, block_uv.y + block_size);

                        index += 4;

                        Block_properties block_properties = tileset.getBlockProperties(id);

                        if (block_properties.isSolid) {
                            solid_blocks_map[block_pos.x / block_size][block_pos.y / block_size] =
                                true;
                        }

                        if (block_properties.isAnimated) {
                            _animated_blocks.emplace_back(AnimatedBlock(id, *quad, *_application));
                        }
                    }

                    block_pos.x += block_size;

                    if (block_pos.x == _level_size.x * block_size) {
                        block_pos.x = 0;
                        block_pos.y += block_size;
                    }
                }
                vertices.resize(index);
                _layers.push_back(std::move(vertices));
            }
        }

        // collision rects merge
        sf::Vector2f pos, size;

        for (int y = 0; y < _level_size.y; y++) {
            for (int x = 0; x < _level_size.x - 1; x++) {
                if (solid_blocks_map[x][y] && solid_blocks_map[x + 1][y]) {
                    pos = sf::Vector2f(x, y);
                    pos *= static_cast<float>(block_size);

                    do {
                        solid_blocks_map[x][y] = false;
                        x++;
                        if (x == _level_size.x)
                            break;
                    } while (solid_blocks_map[x][y]);

                    size = sf::Vector2f(x * block_size - pos.x, block_size);
                    _collision_rects.emplace_back(sf::FloatRect(pos, size));
                }
            }
        }

        for (int x = 0; x < _level_size.x; x++) {
            for (int y = 0; y < _level_size.y; y++) {
                if (solid_blocks_map[x][y]) {
                    pos = sf::Vector2f(x, y);
                    pos *= static_cast<float>(block_size);

                    while (solid_blocks_map[x][y]) {
                        y++;
                        if (y == _level_size.y)
                            break;
                    }

                    size = sf::Vector2f(block_size, y * block_size - pos.y);
                    _collision_rects.emplace_back(sf::FloatRect(pos, size));
                }
            }
        }

        for (int i = 0; i < _level_size.x; i++)
            delete[] solid_blocks_map[i];
        delete[] solid_blocks_map;
    } else
        throw std::runtime_error("Failed to load level" + std::to_string(level_id));
}

void Level::update() {
    for (auto& animated_block : _animated_blocks) {
        animated_block.update();
    }
}

void Level::render() {
    for (auto& layer : _layers) {
        Window::draw(layer, _renderstates);
    }

    /*for (auto &rect : _visible_rects)
    {
        _application->draw(rect);
    }*/
}

void Level::setScale(float scale) {
    _visible_rects.clear();  // DEBUG//

    scale *= Constants::pixelScaleFactor;
    float factor = scale / getScale().x;

    for (int i = 0; i < _collision_rects.size(); i++) {
        _collision_rects[i].left *= factor;
        _collision_rects[i].top *= factor;
        _collision_rects[i].width *= factor;
        _collision_rects[i].height *= factor;

        // DEBUG //
        sf::RectangleShape rect_shape =
            sf::RectangleShape(sf::Vector2f(_collision_rects[i].width, _collision_rects[i].height));
        rect_shape.setPosition(_collision_rects[i].left, _collision_rects[i].top);
        rect_shape.setOutlineColor(sf::Color::Red);
        rect_shape.setFillColor(sf::Color(0, 0, 0, 0));
        rect_shape.setOutlineThickness(-1);
        _visible_rects.push_back(rect_shape);
        // DEBUG //
    }

    Transformable::setScale(scale, scale);
    _renderstates.transform = getTransform();
}
