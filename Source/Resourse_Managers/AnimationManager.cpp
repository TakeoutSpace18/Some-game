#include "AnimationManager.h"

#include "TilesetManager.h"

void AnimationManager::load(const std::string& name, json& animation, TilesetManager& tileset)
{
	std::vector<Frame> frames;
	for (auto &j_frame : animation)
	{
		frames.push_back(Frame{milliseconds(j_frame["duration"]), tileset.getBlockUV(j_frame["tileid"])});
	}
	m_animations.insert(std::make_pair(name, std::make_unique<std::vector<Frame>>(frames)));
}

const std::vector<Frame>& AnimationManager::get(std::string name) const
{
	auto found = m_animations.find(name);
	if (found == m_animations.end())
		throw std::runtime_error("Animation was not loaded.");

	return *found->second;
}
