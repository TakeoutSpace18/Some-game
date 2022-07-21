#pragma once
#include <SFML/Graphics.hpp>

#include "Tools/ColorFadeManager.h"

const sf::Color outline_color(117, 117, 117);
const sf::Color non_active_fill_color(214, 214, 214);
const sf::Color active_fill_color(166, 166, 166);
const sf::Color text_color(sf::Color::Black);
const float press_coef(0.93);

class Application;

class Button : public sf::Drawable {
   public:
    enum class ID { Play, Settings, Exit };

    Button(ID id,
           sf::Vector2f center,
           sf::Vector2f size,
           const std::string& text,
           unsigned int text_size,
           float scale_factor,
           Application& app);

    void input(sf::Event& event, std::vector<Button>& other_buttons);
    void update();

    void setOpacity(sf::Uint8 value);

    bool isPressed() { return m_isPressed; }

   private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    bool m_isActive;
    bool m_isPressed;
    bool m_inFade;

    ID m_id;
    std::string m_name;
    sf::Text m_text;
    sf::RectangleShape m_shape;
    sf::FloatRect m_rect;
    ColorFadeManager m_fade;
    Application* _application;
};
