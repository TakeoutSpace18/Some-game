#pragma once
#include "State_Base.h"
#include "Gameplay/Entities/Player.h"
#include "Gameplay/World/Level.h"

namespace State {
class Playing : public Base {
   public:
    Playing(Application& app);

    void update(float dt) override;
    void handleEvents(const sf::Event& event) override;
    void handleSignal(Signal signal) override;
    void render() override;

    void resize(sf::Vector2f newSize) override;

   private:
    Level _level;
    Player _player;
};

} // namespace State
