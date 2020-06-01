#pragma once
#include <SFML/Graphics.hpp>

#include "ResourseManager.h"

enum class Textures
{

};

enum class Fonts
{
	Sansation
};


class TextureManager : public ResourseManager<Textures, sf::Texture>
{
public:
	TextureManager()
	{

	}
};

class FontManager : public ResourseManager<Fonts, sf::Font>
{
public:
	FontManager()
	{
		load(Fonts::Sansation, "data/fonts/Sansation.ttf");
	}
};

struct ResourseHolder
{
	TextureManager textures;
	FontManager    fonts;
};