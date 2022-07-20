#pragma once
#include <SFML/Graphics.hpp>

#include "AnimationManager.h"
#include "ResourseManager.h"

enum class Textures { Logo, Level_tileset, Main_tileset };

enum class Fonts { SegoeUI, TerminalGrotesque };

class TextureManager : public ResourseManager<Textures, sf::Texture> {
   public:
    TextureManager() { load(Textures::Logo, "data/textures/logo.png"); }
};

class FontManager : public ResourseManager<Fonts, sf::Font> {
   public:
    FontManager() {
        load(Fonts::SegoeUI, "data/fonts/Segoe-ui.ttf");
        load(Fonts::TerminalGrotesque, "data/fonts/terminal-grotesque.grotesque-regular.ttf");
    }
};

struct ResourseHolder {
    TextureManager textures;
    FontManager fonts;
    AnimationManager animations;
};
