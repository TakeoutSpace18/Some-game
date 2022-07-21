#include "Statistics.h"

#include <iostream>

#include "Application.h"
#include "Window.h"
#include "Resourse_Managers/Resourses.hpp"

Statistics::Statistics(Application& app) : _application(&app) {
    _frames = 0;
    _text.setFont(_application->getFont(Fonts::SegoeUI));
    _text.setPosition(10, 10);
    _text.setCharacterSize(20);
    _text.setFillColor(sf::Color::Red);
}

void Statistics::update(float delta) {
    _updateTime += delta;
    _frames++;

    // after 1 sec
    if (_updateTime > 1) {
        _curFps = _frames;
        _frames = 0;
        _updateTime -= 1;
    }

    setString();
}

void Statistics::setString() {
    std::string str = "FPS: ";
    str += std::to_string(_curFps);
    str += "\nDCpF: ";
    str += std::to_string(Window::currentDrawCallsAmount());
    _text.setString(str);
}

void Statistics::render() {
    Window::draw(_text);
}
