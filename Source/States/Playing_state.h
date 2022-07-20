#pragma once
#include "State_Base.h"
#include "../Gameplay/Entities/Player.h"
#include "../Gameplay/World/Level.h"

namespace State {
class Playing : public Base {
   public:
    Playing(Application& app);

    void update(float dt) override;
    void input(sf::Event& event) override;
    void handleSignal(Signal signal) override;
    void render() override;

   private:
    void onWindowResize() override;

    Level _level;
    Player _player;
};
}
