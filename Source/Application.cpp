#include "Application.h"

#include <iostream>

#include "Resourse_Managers/TilesetManager.h"
#include "Settings.h"
#include "Signal.hpp"
#include "States/Test_state.h"
#include "States/Playing_state.h"
#include "States/Splash_screen.h"
#include "Tools/Random.hpp"
#include "Window.h"

Application::Application() {
    Settings::load();
    Window::init();
    Random::init();

    // loading main tileset with entities
    TilesetManager tileset{2, Textures::Main_tileset, *this};
    pushState(std::make_unique<State::Test>(*this));
    // pushState(std::make_unique<State::Splash_screen>(*this));
    runMainLoop();
}

void Application::runMainLoop() {
    sf::Clock clock;

    while (Window::isOpen()) {
        float delta = clock.restart().asSeconds();

        handleEvents();
        Window::clear();

        for (auto& state : _states)
            state->update(delta);

        for (auto& state : _states)
            state->render();

        if (Settings::get("showStatistics")) {
            _statistics.update(delta);
            _statistics.render();
        }

        Window::display();
    }
    Settings::save();
}

void Application::handleEvents() {
    sf::Event event;

    while (Window::pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            Window::close();
        } else if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::F11) {
                Window::toggleFullscreen();
                sf::Vector2f newSize = Window::getSize();
                for (auto& state : _states) {
                    state->resize(newSize);
                }
            }
        } else if (event.type == sf::Event::Resized) {
            sf::Vector2f newSize(event.size.width, event.size.height);
            sf::Vector2f finalSize = Window::setSize(newSize);

            for (auto& state : _states) {
                state->resize(finalSize);
            }
        }
        _states.front()->handleEvents(event);
    }
}

void Application::handleSignal(Signal signal) {
    if (signal.type == Signal::ButtonClicked) {
        if (signal.button.id == Button::ID::Exit) {
            Window::close();
        }
    }
    _states.front()->handleSignal(signal);
}

void Application::pushState(std::unique_ptr<State::Base> state) {
    _states.push_front(std::move(state));
}

void Application::popState() {
    _states.pop_back();
}
