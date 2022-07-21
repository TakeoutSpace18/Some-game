#pragma once
#include <fstream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>

#include "AnimatedBlock.h"
#include "Application.h"

using json = nlohmann::json;

class Level : public sf::Transformable {
   public:
    Level(Application& app);

    void load(short id);
    void update();
    void render();

    void setScale(float scale);

    std::vector<sf::FloatRect>& getCollisionRects() { return _collision_rects; }

   private:
    sf::Vector2i _level_size;
    sf::RenderStates _renderstates;

    std::vector<sf::VertexArray> _layers;
    std::vector<AnimatedBlock> _animated_blocks;

    std::vector<sf::RectangleShape> _visible_rects;  // DEBUG

    std::vector<sf::FloatRect> _collision_rects;

    Application* _application;
};
