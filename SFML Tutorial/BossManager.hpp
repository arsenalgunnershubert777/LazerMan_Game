#pragma once
#include "Game.hpp"
#include "JellyFish.hpp"
#include <SFML/Graphics.hpp>
#include "DEFINITIONS.hpp"
#include <vector>
#include <set>
#include "BossOne.hpp"
#include "Enemies.hpp"
#include "BossThree.hpp"
#include "BossTwo.hpp"
#include "BossFour.hpp"
namespace g35{
    
    class BossManager{
    public:
        BossManager(GameDataRef data);
        void Draw();
        void Update(float dt, float *mainCharacterPosition,sf::FloatRect mainCharacterRect);
        int getCurrentGameLevel();
        std::vector<sf::FloatRect> getRectVector();
        void Init();
        Enemies * boss;
        void setMovingStates(bool movingStates);
        
        
        
        
    private:
        GameDataRef _data;
        int _currGameLevel;
        bool movingStates;
        sf::Clock _clock;
        
        
        
    };
    
}
