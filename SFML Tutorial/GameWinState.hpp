#pragma once
#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"

namespace g35 {
    class GameWinState : public State
    {
    public:
        GameWinState(GameDataRef data);
        void Init();
        void HandleInput();
        void Update(float dt);
        void Draw(float dt);
        
    private:
        GameDataRef _data;
        sf::Sprite _background;
        sf::Clock _clock;
        
    };
}

