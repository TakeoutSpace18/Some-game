#include "UIElement.h"

#include <memory>
#include <iostream>

void UIElement::setScaleFactor(float factor) {
    _scaleFactorTransform = sf::Transform();
    _scaleFactorTransform.scale({factor, factor});
    for (auto& child : _children) {
        child->setScaleFactor(factor);
    }
    _size *= factor;
}

void UIElement::setAlign(UIElement::Align align) {
    _align = align;
}

void UIElement::resize(sf::Vector2f newSize) {
    _size = newSize;
    for (auto& child : _children) {
        child->updatePosition(_size);
    }
}

void UIElement::addChild(std::unique_ptr<UIElement> child) {
    _children.push_back(std::move(child));
}

void UIElement::bindDrawable(sf::Drawable* drawable) {
    _drawableShapes.push_back(drawable);
}

void UIElement::updatePosition(const sf::Vector2f& parentSize) {
    sf::Vector2f newPosition;
    // Set vertical position
    switch (_align) {
    case Align::None:
        break;
    case Align::Top:
    case Align::TopLeft:
    case Align::TopRight:
        newPosition.y = 0;
        break;
    case Align::Center:
    case Align::Left:
    case Align::Right:
        newPosition.y = (parentSize.y - _size.y) / 2.0f;
        break;
    case Align::Bottom:
    case Align::BottomLeft:
    case Align::BottomRight:
        newPosition.y = parentSize.y - _size.y;
        break;
    }
    
    // Set horizontal position
    switch (_align) {
    case Align::None:
        break;
    case Align::Left:
    case Align::TopLeft:
    case Align::BottomLeft:
        newPosition.x = 0;
        break;
    case Align::Center:
    case Align::Top:
    case Align::Bottom:
        newPosition.x = (parentSize.x - _size.x) / 2.0f;
        break;
    case Align::Right:
    case Align::TopRight:
    case Align::BottomRight:
        newPosition.x = parentSize.x - _size.x;
        break;
    }

    sf::Transformable::setPosition(newPosition);
}

void UIElement::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    sf::RenderStates newStates = states;
    // Draw UIElement itself
    newStates.transform *= sf::Transformable::getTransform();
    newStates.transform *= _scaleFactorTransform;
    for (auto& shape : _drawableShapes) {
        target.draw(*shape, newStates);
    }
    // DEBUG
    sf::RectangleShape shape;
    shape.setOutlineColor(sf::Color::Red);
    shape.setOutlineThickness(2);
    shape.setSize(_size);
    shape.setFillColor(sf::Color::Transparent);
    target.draw(shape, newStates); 

    // Draw it's children
    newStates = states;
    newStates.transform *= sf::Transformable::getTransform();
    for (auto& child : _children) {
        target.draw(*child, newStates);
    }
}