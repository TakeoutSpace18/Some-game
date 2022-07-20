#pragma once
#include <map>
#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>

#include "../Application.h"

using json = nlohmann::json;

struct Block_properties {
    bool isSolid = false;
    bool hasCollision = false;
    bool hasCustomSize = false;
    bool isBreakable = false;
    bool isTransparent = false;
    bool isAnimated = false;
};

class TilesetManager {
   public:
    TilesetManager(short tileset_id, Textures texture_place, Application& app)
        : _application(&app) {
        load(tileset_id, texture_place);
    };

    void load(short tileset_id, Textures texture_place);

    sf::Vector2u getBlockUV(short id);
    std::vector<sf::IntRect> getBlockCollisions(short id);
    const Block_properties getBlockProperties(short id);

   private:
    std::map<short, Block_properties> m_properties;
    std::map<short, std::vector<sf::IntRect>> m_block_collisions;
    short m_columns;

    Application* _application;
};
