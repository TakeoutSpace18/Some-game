#include "TestElement.h"

TestElement::TestElement() {
    _shape.setSize({150, 150});
    _shape.setFillColor(sf::Color::Red);
    _shape.setOutlineThickness(15);
    _shape.setOutlineColor(sf::Color::Green);
    
    bindDrawable(&_shape);
}

