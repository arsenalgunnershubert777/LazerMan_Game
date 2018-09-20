#pragma once
#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"
#include "SpongeBob.hpp"
#include "JellyFish.hpp"
#include "JellyFishAI.hpp"
#include "DamageInteractions.hpp"
#include "DEFINITIONS.hpp"
#include "MainMenuState.hpp"
#include "GameOverState.hpp"
#include "GameWinState.hpp"
#include "BossManager.hpp"
namespace g35 {
    
    class GameState : public State
    {
    
    public:
        GameState(GameDataRef data);
        void Init();
        void HandleInput();
        void Update(float dt);
        void Draw(float dt);
        void drawHealthBars();
        void drawRoundLabels();

        
    private:
        GameDataRef _data;
        sf::Sprite _background;
        sf::Sprite _pauseButton;
        sf::Sprite _playButton;
        sf::Sprite _exitButton;
        SpongeBob * spongebob;
        sf::Clock _clock;
        BossManager * bossManager;
        int gameLevel;
        
        DamageInteractions * damageInteractions;
        JellyFishAI * jellyfishAI;
        bool introTextFinished;
        bool isPaused;
        bool intoPauseState;
        

        
        
        
        
        
    };
}

