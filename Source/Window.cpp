#include "Window.h"
#include "Constants.hpp"
#include "Settings.h"
#include "Icon.h"

void Window::init() {
    createWindow();
    _drawCallsCounter = 0;
}

void Window::createWindow() {
    if (Settings::get<bool>("isFullscreen")) {
        sf::VideoMode videomode = sf::VideoMode::getDesktopMode();
        _renderWindow.create(videomode, Constants::windowTitle, sf::Style::Fullscreen);
    } else {
        sf::VideoMode videomode(Settings::get<uint32_t>("windowedModeWidth"),
                                Settings::get<uint32_t>("windowedModeHeight"));
        _renderWindow.create(videomode, Constants::windowTitle, sf::Style::Default);
    }

    _renderWindow.setIcon(icon.width, icon.height, icon.pixel_data);
    _renderWindow.setKeyRepeatEnabled(false);
    _renderWindow.setVerticalSyncEnabled(false);
}

void Window::draw(sf::Drawable& drawable, const sf::RenderStates& states) {
    _renderWindow.draw(drawable, states);
    _drawCallsCounter++;
}

void Window::clear() {
    _renderWindow.clear();
    _drawCallsCounter = 0;
}

void Window::display() {
    _renderWindow.display();
}

void Window::toggleFullscreen() {
    Settings::get("isFullscreen") = !Settings::get("isFullscreen");
    createWindow();
}

uint32_t Window::currentDrawCallsAmount() {
    return _drawCallsCounter;
}

bool Window::isOpen() {
    return _renderWindow.isOpen();
}

void Window::close() {
    _renderWindow.close();
}

sf::Vector2f Window::setSize(const sf::Vector2f& size) {
    sf::Vector2f finalSize;
    if (size.x < Settings::get<uint32_t>("minimalWindowWidth")) {
        finalSize.x = Settings::get<uint32_t>("minimalWindowWidth");
    } else {
        finalSize.x = size.x;
    }
    if (size.y < Settings::get<uint32_t>("minimalWindowHeight")) {
        finalSize.y = Settings::get<uint32_t>("minimalWindowHeight");
    } else {
        finalSize.y = size.y;
    }
    Settings::get("windowedModeWidth") = size.x;
    Settings::get("windowedModeHeight") = size.y;
    _renderWindow.setSize(sf::Vector2u(finalSize.x, finalSize.y));
    return finalSize;
}

void Window::setView(sf::View view) {
    _renderWindow.setView(view);
}

const sf::View& Window::getDefaultView() {
    return _renderWindow.getDefaultView();
}

bool Window::pollEvent(sf::Event& event) {
    return _renderWindow.pollEvent(event);
}

sf::Vector2i Window::getMousePosition() {
    return sf::Mouse::getPosition(_renderWindow);
}

sf::Vector2f Window::getSize() {
    sf::Vector2u size = _renderWindow.getSize();
    return sf::Vector2f(size.x, size.y);
}
