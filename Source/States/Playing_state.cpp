#include "Playing_state.h"
#include "../Window.h"
#include "../Resourse_Managers/TilesetManager.h"

State::Playing::Playing(Application& app)
    : Base{app},
      _level{app},
      _player{_level.getCollisionRects(), *_application} {
    _level.load(1);
    onWindowResize();
}

void State::Playing::update(float dt) {
    _level.update();
    _player.update(dt);
}

void State::Playing::input(sf::Event& event) {
    _player.input(event);
}

void State::Playing::handleSignal(Signal signal) {}

void State::Playing::render() {
    _level.render();
    Window::draw(_player);
}

void State::Playing::onWindowResize() {
    float scale_factor = _application->computeScaleFactor();
    _level.setScale(scale_factor);
    _player.setScale(scale_factor);
}
