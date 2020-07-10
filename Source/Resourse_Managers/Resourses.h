#pragma once
#include <SFML/Graphics.hpp>

#include "ResourseManager.h"

enum class Textures
{
	Logo,
	Tileset
};

enum class Fonts
{
	SegoeUI
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
		load(Fonts::SegoeUI, "data/fonts/Segoe-ui.ttf");
	}
};

struct ResourseHolder
{
	TextureManager textures;
	FontManager    fonts;
};