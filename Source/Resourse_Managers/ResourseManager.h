#pragma once
#include <map>
#include <memory>
#include <stdexcept>
#include <string>

#include <SFML/Graphics.hpp>

template <typename Identifier, typename Resourse_type>
class ResourseManager
{
public:

	void load(Identifier id, const std::string& filename)
	{
		std::unique_ptr<Resourse_type> res = std::make_unique<Resourse_type>();
		if (!res->loadFromFile(filename))
			throw std::runtime_error("Failed to load " + filename);

		m_resourses.insert(std::make_pair(id, std::move(res)));
	}

	const Resourse_type& get(Identifier id) const
	{
		auto found = m_resourses.find(id);
		if (found == m_resourses.end())
			throw std::runtime_error("Resourse was not loaded.");

		return *found->second;
	}

private:
	std::map<Identifier, std::unique_ptr<Resourse_type>> m_resourses;
};