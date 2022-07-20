#pragma once
#include "State_Base.h"
#include "../Tools/FadeManager.h"

namespace State {
class Splash_screen : public Base {
   public:
    Splash_screen(Application& app);

    void update(float dt) override;
    void input(sf::Event& event) override;
    void handleSignal(Signal signal) override;
    void render() override;

   private:
    void onWindowResize() override;

    enum class Mode { Waiting, FadeIn, FadeOut };

    Mode _mode;
    FadeManager _fade;
    sf::Sprite _logo;
    sf::RectangleShape _background;
};
}
