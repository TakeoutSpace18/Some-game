#include "Splash_screen.h"
#include "Main_menu.h"
#include "../Window.h"
#include "../Application.h"

State::Splash_screen::Splash_screen(Application& app) : Base(app) {
    _logo.setTexture(_application->getTexture(Textures::Logo));
    _logo.setColor(sf::Color(255, 255, 255, 0));
    _background.setFillColor(sf::Color::White);
    onWindowResize();
    _mode = Mode::FadeIn;
    _fade = FadeManager(sf::seconds(1), 0, 255);
}

void State::Splash_screen::onWindowResize() {
    _background.setSize(Window::getSize());
    float scale_factor = _application->computeScaleFactor();
    _logo.setScale(scale_factor, scale_factor);

    _logo.setPosition(Window::getSize().x / 2 - _logo.getGlobalBounds().width / 2,
                      Window::getSize().y / 2 - _logo.getGlobalBounds().height / 2);
}

void State::Splash_screen::update(float dt) {
    switch (_mode) {
        case Mode::FadeIn:
            if (_fade.isOver()) {
                _logo.setColor(sf::Color(255, 255, 255, 255));
                _fade = FadeManager(sf::seconds(1));
                _mode = Mode::Waiting;
                break;
            }
            _logo.setColor(sf::Color(255, 255, 255, _fade.getCurrentValue()));
            break;

        case Mode::Waiting:
            if (_fade.isOver()) {
                _application->pushState(std::make_unique<Main_menu>(*_application));
                _fade = FadeManager(sf::seconds(1), 255, 0);
                _mode = Mode::FadeOut;
            }
            break;

        case Mode::FadeOut:
            if (_fade.isOver()) {
                _application->popState();
                break;
            }
            _logo.setColor(sf::Color(255, 255, 255, _fade.getCurrentValue()));
            _background.setFillColor(sf::Color(255, 255, 255, _fade.getCurrentValue()));
            break;
    }
}

void State::Splash_screen::input(sf::Event& event) {}

void State::Splash_screen::handleSignal(Signal signal) {}

void State::Splash_screen::render() {
    Window::draw(_background);
    Window::draw(_logo);
}
