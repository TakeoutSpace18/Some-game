#include "AnimationHandler.h"

#include <iostream>

#include "Constants.hpp"

AnimationHandler::AnimationHandler(sf::Sprite& sprite, Application& app)
    : m_p_sprite(&sprite), _application(&app) {
    // Texture size is set to the size of the block by default
    setTextureSize(sf::Vector2i(Constants::tileSize, Constants::tileSize));
}

AnimationHandler::AnimationHandler(sf::Sprite& sprite, sf::Vector2i texture_size, Application& app)
    : m_p_sprite(&sprite), _application(&app) {
    setTextureSize(texture_size);
}

void AnimationHandler::setTextureSize(sf::Vector2i size) {
    m_texture_rect.width = size.x;
    m_texture_rect.height = size.y;
    m_p_sprite->setTextureRect(m_texture_rect);
}

void AnimationHandler::setAnimation(std::string name, bool flipX, bool flipY, bool endless) {
    m_is_endless = endless;
    m_flipped_x = flipX;
    m_flipped_y = flipY;

    m_p_cur_animation = &_application->getAnimation(name);
    m_cur_frame = m_p_cur_animation->cbegin();

    m_texture_rect.width = abs(m_texture_rect.width);  // to erase previous flip state
    m_texture_rect.height = abs(m_texture_rect.height);

    if (m_flipped_x) {
        m_texture_rect.left = m_texture_rect.width + m_cur_frame->uv.x;
        m_texture_rect.width *= -1;
    } else
        m_texture_rect.left = m_cur_frame->uv.x;

    if (m_flipped_y) {
        m_texture_rect.top = m_texture_rect.height + m_cur_frame->uv.y;
        m_texture_rect.height *= -1;
    } else
        m_texture_rect.top = m_cur_frame->uv.y;

    m_p_sprite->setTextureRect(m_texture_rect);
}

void AnimationHandler::update() {
    if (duration_cast<milliseconds>(steady_clock::now() - m_start) >= m_cur_frame->dur &&
        m_cur_frame != m_p_cur_animation->cend()) {
        m_start = steady_clock::now();
        ++m_cur_frame;

        if (m_cur_frame == m_p_cur_animation->cend() && m_is_endless)
            m_cur_frame = m_p_cur_animation->cbegin();

        if (m_flipped_x)
            m_texture_rect.left = abs(m_texture_rect.width) + m_cur_frame->uv.x;
        else
            m_texture_rect.left = m_cur_frame->uv.x;

        if (m_flipped_y)
            m_texture_rect.top = abs(m_texture_rect.height) + m_cur_frame->uv.y;
        else
            m_texture_rect.top = m_cur_frame->uv.y;

        m_p_sprite->setTextureRect(m_texture_rect);
    }
}
