#pragma once
#include <vector>

#include "State_Base.h"
#include "UI/Button.h"
#include "Tools/FadeManager.h"

const sf::Vector2f button_size(155, 40);
const int button_spacing(12);

namespace State {
class Main_menu : public Base {
   public:
    Main_menu(Application& app);

    void update(float dt) override;
    void handleEvents(const sf::Event& event) override;
    void handleSignal(Signal signal) override;
    void render() override;

    void resize(sf::Vector2f newSize) override;

   private:
    enum class Mode { Active, FadeOut };

    Mode _mode;
    FadeManager _fade;
    std::vector<Button> _buttons;
    sf::RectangleShape _background;
};

} // namespace State
