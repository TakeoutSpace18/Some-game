#include "AnimatedBlock.h"

#include "Resourse_Managers/TilesetManager.h"
#include "Tools/Random.hpp"
#include "Constants.hpp"

AnimatedBlock::AnimatedBlock(short id, sf::Vertex& quad, Application& app) : m_p_quad(&quad) {
    m_p_animation = &app.getAnimation(std::to_string(id));
    m_p_quad = &quad;
    m_cur_frame = m_p_animation->cbegin();
    m_start = steady_clock::now() -
              milliseconds(Random::IntInRange(0, m_cur_frame->dur.count() * 100) * 10);
}

void AnimatedBlock::update() {
    if (duration_cast<milliseconds>(steady_clock::now() - m_start) >= m_cur_frame->dur) {
        m_start = steady_clock::now();
        ++m_cur_frame;

        if (m_cur_frame == m_p_animation->cend())
            m_cur_frame = m_p_animation->cbegin();

        m_p_quad[0].texCoords = sf::Vector2f(m_cur_frame->uv.x, m_cur_frame->uv.y);
        m_p_quad[1].texCoords =
            sf::Vector2f(m_cur_frame->uv.x + Constants::tileSize, m_cur_frame->uv.y);
        m_p_quad[2].texCoords = sf::Vector2f(m_cur_frame->uv.x + Constants::tileSize,
                                             m_cur_frame->uv.y + Constants::tileSize);
        m_p_quad[3].texCoords =
            sf::Vector2f(m_cur_frame->uv.x, m_cur_frame->uv.y + Constants::tileSize);
    }
}
