#pragma once
#include "UIElement.h"

class TestElement : public UIElement {
   public:
    TestElement();

   private:
    sf::RectangleShape _shape;
};