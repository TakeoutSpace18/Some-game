#pragma once
#include <SFML/Graphics.hpp>

#include "ResourseManager.h"

enum class Textures
{
	Logo
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
		load(Textures::Logo, "data/textures/logo.png");
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