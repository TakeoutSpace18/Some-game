#include "AnimationHandler.h"

AnimationHandler::AnimationHandler(Application& app): m_p_application((&app))
{
	//Texture size is set to the size of the block by default
	int texture_size = g_tilesize;
	setTextureSize(sf::Vector2i(texture_size, texture_size));
}

AnimationHandler::AnimationHandler(sf::Sprite& sprite, Application& app): m_p_application(&app), m_p_sprite(&sprite)
{
	int texture_size = m_p_application->getSettings()["block_size"];
	setTextureSize(sf::Vector2i(texture_size, texture_size));
}

AnimationHandler::AnimationHandler(sf::Sprite& sprite, sf::Vector2i texture_size, Application& app)
: m_p_application(&app), m_p_sprite(&sprite)
{
	setTextureSize(texture_size);
}

void AnimationHandler::setTextureSize(sf::Vector2i size)
{
	m_texture_rect.width = size.x;
	m_texture_rect.height = size.y;
}

void AnimationHandler::setAnimation(std::string& name, bool endless)
{
	m_is_endless = endless;
	*m_p_cur_animation = m_p_application->getAnimation(name);
	m_cur_frame = m_p_cur_animation->cbegin();

	m_texture_rect.left = m_cur_frame->uv.x;
	m_texture_rect.top = m_cur_frame->uv.y;
}

void AnimationHandler::update()
{
	if (duration_cast<milliseconds>(steady_clock::now() - m_start) >= m_cur_frame->duration && m_cur_frame != m_p_cur_animation->cend())
	{
		m_start = steady_clock::now();
		++m_cur_frame;
		
		if (m_cur_frame == m_p_cur_animation->cend() && !m_is_endless)
			m_cur_frame = m_p_cur_animation->cbegin();

		m_texture_rect.left = m_cur_frame->uv.x;
		m_texture_rect.top  = m_cur_frame->uv.y;

		m_p_sprite->setTextureRect(m_texture_rect);
	}
}
