#include "Player.h"

Player::Player(std::vector<sf::FloatRect>& collision_rects, Application& app) : Entity(collision_rects, "player", app)
{
	setTexture(Textures::Main_tileset);
	setPosition(sf::Vector2f(8, 8));
}

void Player::input(sf::Event& event)
{
	Entity::input(event);
}

void Player::update(float dt)
{
	Entity::update(dt);

}
