#pragma once
#include "Entity.h"

class Player : public Entity {
   public:
    Player(std::vector<sf::FloatRect>& collision_rects, Application& app);

    void input(sf::Event& event);
    void update(float dt);

   private:
};
