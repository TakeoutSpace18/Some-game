#include "Playing_state.h"

#include "Window.h"
#include "Resourse_Managers/TilesetManager.h"

State::Playing::Playing(Application& app)
    : Base(app),
      _level{app},
      _player{_level.getCollisionRects(), *_application} {
    _level.load(1);
    resize(Window::getSize());
}

void State::Playing::update(float dt) {
    _level.update();
    _player.update(dt);
}

void State::Playing::handleEvents(const sf::Event& event) {
    _player.input(event);
}

void State::Playing::handleSignal(Signal signal) {}

void State::Playing::render() {
    _level.render();
    Window::draw(_player);
}

void State::Playing::resize(sf::Vector2f newSize) {
    float scale_factor = Window::getScaleFactor();
    _level.setScale(scale_factor);
    _player.setScale(scale_factor);
}
