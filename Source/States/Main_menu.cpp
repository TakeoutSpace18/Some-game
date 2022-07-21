#include "Main_menu.h"

#include "Playing_state.h"
#include "Constants.hpp"
#include "Window.h"
#include "Application.h"
#include "UI/Button.h"

State::Main_menu::Main_menu(Application& app) : Base(app) {
    _mode = Mode::Active;
    _background.setFillColor(sf::Color::White);
    onWindowResize();
}

void State::Main_menu::onWindowResize() {
    _background.setSize(Window::getSize());

    float scale_factor = _application->computeScaleFactor();
    _buttons.clear();
    _buttons.emplace_back(Button(
        Button::ID::Play,
        sf::Vector2f(Window::getSize().x / 2,
                     Window::getSize().y / 2 - (button_size.y + button_spacing) * scale_factor),
        button_size, "Play", 26, scale_factor, *_application));
    _buttons.emplace_back(Button(Button::ID::Settings,
                                 sf::Vector2f(Window::getSize().x / 2, Window::getSize().y / 2),
                                 button_size, "Settings", 26, scale_factor, *_application));
    _buttons.emplace_back(Button(
        Button::ID::Exit,
        sf::Vector2f(Window::getSize().x / 2,
                     Window::getSize().y / 2 + (button_size.y + button_spacing) * scale_factor),
        button_size, "Exit", 26, scale_factor, *_application));
}

void State::Main_menu::update(float dt) {
    switch (_mode) {
        case Mode::Active:
            for (int i = 0; i < _buttons.size(); i++) {
                _buttons[i].update();
            }
            break;

        case Mode::FadeOut:
            if (_fade.isOver()) {
                _application->popState();
                break;
            }
            sf::Uint8 opacity = _fade.getCurrentValue();
            _background.setFillColor(sf::Color(255, 255, 255, opacity));
            for (int i = 0; i < _buttons.size(); i++) {
                _buttons[i].setOpacity(opacity);
            }
            break;
    }
}

void State::Main_menu::input(sf::Event& event) {
    for (auto& button : _buttons) {
        button.input(event, _buttons);
    }
}

void State::Main_menu::handleSignal(Signal signal) {
    if (signal.type == Signal::ButtonClicked) {
        if (signal.button.id == Button::ID::Play) {
            _application->pushState(std::make_unique<Playing>(*_application));
            _fade = FadeManager(sf::seconds(Constants::stateChangeDuration), 255, 0);
            _mode = Mode::FadeOut;
        }
    }
}

void State::Main_menu::render() {
    Window::draw(_background);
    for (auto& button : _buttons) {
        Window::draw(button);
    }
}
