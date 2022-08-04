#pragma once
#include <memory>

#include "State_Base.h"
#include "UI/Elements.hpp"

namespace State {
class Test : public Base {
   public:
    Test(Application& app);

    void update(float dt) override;
    void handleEvents(const sf::Event& event) override;
    void handleSignal(Signal signal) override;
    void render() override;

    void resize(sf::Vector2f newSize) override;

   private:
    EmptyElement _canvas;
};

} // namespace State
