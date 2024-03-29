#pragma once
#include <chrono>
#include <map>
#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace std::chrono;

class TilesetManager;

struct Frame {
    duration<float> dur;
    sf::Vector2u uv;
};

class AnimationManager {
   public:
    AnimationManager(){};

    void load(const std::string& name, json& animation, TilesetManager& tileset);

    const std::vector<Frame>& get(std::string name);

   private:
    std::map<std::string, std::unique_ptr<std::vector<Frame>>> m_animations;
};
