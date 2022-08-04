#pragma once
#include <SFML/Graphics.hpp>

#include <deque>
#include <memory>

#include "Resourse_Managers/Resourses.hpp"
#include "Settings.h"
#include "Signal.hpp"
#include "States/State_Base.h"
#include "Tools/Statistics.h"

class Application {
   public:
    Application();

    void draw(const sf::Drawable& obj, const sf::RenderStates& states = sf::RenderStates::Default);

    void pushState(std::unique_ptr<State::Base> state);
    void popState();
    void handleSignal(Signal signal);

    // Remove
    ResourseHolder& getResourses() { return m_resourses; }

    // Remove
    const sf::Texture& getTexture(Textures id) const { return m_resourses.textures.get(id); }
    // Remove
    const sf::Font& getFont(Fonts id) const { return m_resourses.fonts.get(id); }
    // Remove
    const std::vector<Frame>& getAnimation(std::string name) {
        return m_resourses.animations.get(name);
    }
    // Remove
    void loadTexture(Textures id, const std::string& filename) {
        m_resourses.textures.load(id, filename);
    }

    // Remove
    void loadAnimation(const std::string& name, json& animation, TilesetManager& tileset) {
        m_resourses.animations.load(name, animation, tileset);
    }

   private:
    void runMainLoop();
    void handleEvents();

    ResourseHolder m_resourses;
    Statistics _statistics{*this};

    std::deque<std::unique_ptr<State::Base>> _states;
};
