#include "State_Base.h"
#include "../Application.h"
#include "../Window.h"

State::Base::Base(Application& app) : _application(&app) {}

void State::Base::setViewSize(sf::View view) {
    Window::setView(view);
    onWindowResize();
}
