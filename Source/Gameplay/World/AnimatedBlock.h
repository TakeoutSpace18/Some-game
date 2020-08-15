#pragma once
#include <SFML/Graphics.hpp>
#include <chrono>

#include "../../Application.h"
#include "../../Resourse_Managers/AnimationManager.h"

using namespace std::chrono;

class AnimatedBlock
{
public:
	AnimatedBlock(short id, sf::Vertex& quad, Application& app);;

	void update();

private:

	std::vector<Frame>::const_iterator m_cur_frame;
	time_point<steady_clock> m_start;

	const std::vector<Frame>* m_p_animation;
	sf::Vertex* m_p_quad;
};
