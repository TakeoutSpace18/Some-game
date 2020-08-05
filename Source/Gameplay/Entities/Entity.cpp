#include "Entity.h"

#include <iostream>

inline void Entity::check_collision()
{
	
}

Entity::Entity(std::vector<sf::FloatRect>& collision_rects, std::string name, Application& app):
	m_p_collision_rects(&collision_rects), m_p_application(&app), m_name(name)
{
	//m_animation_handler.setAnimation("4");
}

void Entity::input(sf::Event& event)
{
	static bool moves_diagonal;
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::S)
		{
			m_targetVelocity.y = m_speed * m_sprite.getScale().x;
		}
		else if (event.key.code == sf::Keyboard::W)
		{
			m_targetVelocity.y = -m_speed * m_sprite.getScale().x;
		}
		else if (event.key.code == sf::Keyboard::A)
		{
			m_targetVelocity.x = -m_speed * m_sprite.getScale().x;
		}
		else if (event.key.code == sf::Keyboard::D)
		{
			m_targetVelocity.x = m_speed * m_sprite.getScale().x;
		}

		if (m_targetVelocity.x != 0 && m_targetVelocity.y != 0)
		{
			moves_diagonal = true;
			m_targetVelocity *= (float)0.7071;
		}
	}
	else if (event.type == sf::Event::KeyReleased)
	{
		if (event.key.code == sf::Keyboard::S && m_targetVelocity.y > 0)
		{
			m_targetVelocity.y = 0;
		}
		else if (event.key.code == sf::Keyboard::W && m_targetVelocity.y < 0)
		{
			m_targetVelocity.y = 0;
		}
		else if (event.key.code == sf::Keyboard::A && m_targetVelocity.x < 0)
		{
			m_targetVelocity.x = 0;
		}
		else if (event.key.code == sf::Keyboard::D && m_targetVelocity.x > 0)
		{
			m_targetVelocity.x = 0;
		}
		if (moves_diagonal && (m_targetVelocity.x == 0 || m_targetVelocity.y == 0))
		{
			moves_diagonal = false;
			m_targetVelocity *= (float)1.4144;
		}
	}
}

void Entity::update(float dt)
{
	auto a = (m_acceleration / s_ideal_fps) * dt;
	m_currentVelocity.x = a * m_targetVelocity.x + (1 - a) * m_currentVelocity.x;
	m_currentVelocity.y = a * m_targetVelocity.y + (1 - a) * m_currentVelocity.y;
	
	if (abs(m_currentVelocity.x) < m_threshold)
		m_currentVelocity.x = 0;
	if (abs(m_currentVelocity.y) < m_threshold)
		m_currentVelocity.y = 0;

	//m_animation_handler.update();

	m_sprite.move(m_currentVelocity * dt);
}

void Entity::setDirection(unsigned short degrees)
{
	m_direction = toRad<float>(degrees);
	m_targetVelocity.x = sin(m_direction) * m_speed * m_sprite.getScale().x;
	m_targetVelocity.y = -cos(m_direction) * m_speed * m_sprite.getScale().x;
}

void Entity::setSpeed(float speed, bool controlled_entity)
{
	if (controlled_entity)
	{
		auto factor = speed / m_speed;
		m_targetVelocity *= factor;
	}
	else
	{
		m_targetVelocity.x = sin(m_direction) * speed * m_sprite.getScale().x;
		m_targetVelocity.y = -cos(m_direction) * speed * m_sprite.getScale().x;
	}
	m_speed = speed;
}

void Entity::setScale(float scale)
{
	scale *= g_pixel_scale_factor;
	float factor = scale / m_sprite.getScale().x;
	
	m_sprite.setScale(scale, scale);
	m_sprite.setPosition(m_sprite.getPosition() * factor);
	m_targetVelocity *= factor;
	m_threshold *= factor;
}

void Entity::setTexture(Textures texture_id)
{
	m_sprite.setTexture(m_p_application->getTexture(texture_id));
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_sprite, states);
}
