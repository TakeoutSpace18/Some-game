#pragma once
#include "SFML/Graphics.hpp"
#include "Gameplay/AnimationHandler.h"
#include "Tools/Math.hpp"

enum class Direction { LEFT, RIGHT, UP, DOWN };

class Entity : public sf::Drawable {
   public:
    Entity(std::vector<sf::FloatRect>& collision_rects, std::string name, Application& app);

    void input(const sf::Event& event);  // call if entity is controlled by player
    void update(float dt);
    inline void check_collision();

    void setDirection(unsigned short degrees);
    void setSpeed(float speed,
                  bool controlled_entity = false);  // set true if entity is controlled by player

    void setScale(float scale);
    void setTextureSize(sf::Vector2i size) { m_animation_handler.setTextureSize(size); }
    void setTexture(Textures texture_id);
    void setPosition(const sf::Vector2f& pos) { m_sprite.setPosition(pos); }

    float getDirection() { return toDeg<float>(m_direction); }
    float getSpeed() { return m_speed; }

   protected:
    Application* _application;

   private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::Sprite m_sprite;
    AnimationHandler m_animation_handler;

    std::string m_name;

    sf::Vector2f m_targetVelocity;
    sf::Vector2f m_currentVelocity;

    float m_direction = toRad<float>(90);  // in radians

    float m_speed = 170;
    float m_acceleration = 0.35;  // value from 0 to 1
    float m_threshold = 0.2;

    static constexpr float s_ideal_fps = 1.f / 60.f;

    std::vector<sf::FloatRect>* m_p_collision_rects;
};
