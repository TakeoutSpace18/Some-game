#include "Test_state.h"

#include "SFML/Graphics.hpp"

#include "Application.h"
#include "UI/Elements.hpp"
#include "Window.h"


State::Test::Test(Application& app) : Base(app) {
    auto element1 = std::make_unique<TestElement>();
    auto element2 = std::make_unique<TestElement>();
    auto element3 = std::make_unique<TestElement>();
    auto element4 = std::make_unique<TestElement>();
    auto element5 = std::make_unique<TestElement>();
    auto element6 = std::make_unique<TestElement>();
    auto element7 = std::make_unique<TestElement>();
    auto element8 = std::make_unique<TestElement>();
    auto element9 = std::make_unique<TestElement>();

    element1->resize({150, 150});
    element2->resize({150, 150});
    element3->resize({150, 150});
    element4->resize({150, 150});
    element5->resize({150, 150});
    element6->resize({150, 150});
    element7->resize({150, 150});
    element8->resize({150, 150});
    element9->resize({150, 150});

    element1->setAlign(UIElement::Align::Top);
    element2->setAlign(UIElement::Align::Bottom);
    element3->setAlign(UIElement::Align::Left);
    element4->setAlign(UIElement::Align::Right);
    element5->setAlign(UIElement::Align::TopLeft);
    element6->setAlign(UIElement::Align::TopRight);
    element7->setAlign(UIElement::Align::BottomLeft);
    element8->setAlign(UIElement::Align::BottomRight);
    element9->setAlign(UIElement::Align::Center);

    _canvas.addChild(std::move(element1));
    _canvas.addChild(std::move(element2));
    _canvas.addChild(std::move(element3));
    _canvas.addChild(std::move(element4));
    _canvas.addChild(std::move(element5));
    _canvas.addChild(std::move(element6));
    _canvas.addChild(std::move(element7));
    _canvas.addChild(std::move(element8));
    _canvas.addChild(std::move(element9));

    _canvas.setPosition({0, 0});
    _canvas.resize(Window::getSize());
}

void State::Test::update(float dt) {}

void State::Test::handleEvents(const sf::Event& event) {}

void State::Test::handleSignal(Signal signal) {}

void State::Test::render() {
    Window::draw(_canvas);
}

void State::Test::resize(sf::Vector2f newSize) {
    float scaleFactor = Window::getScaleFactor();
    //_canvas.setScaleFactor(scaleFactor);
    _canvas.resize(newSize);
}
