#pragma once
#include <SFML/Graphics.hpp>

class ColorFadeManager {
   public:
    ColorFadeManager(){};
    ColorFadeManager(sf::Time duration, sf::Color start_color, sf::Color target_color);

    sf::Color getCurrentColor();
    sf::Color getFinalColor() { return m_target_color; }
    bool isOver();

   private:
    sf::Clock m_clock;
    sf::Time m_duration{};
    sf::Color m_start_color;
    sf::Color m_target_color;
};
