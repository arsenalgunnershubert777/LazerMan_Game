#pragma once

#include <SFML/Graphics.hpp>
#include "DEFINITIONS.hpp"
#include "Game.hpp"

namespace g35 {
    
    class JellyFish{
    public:
        JellyFish(GameDataRef data);
        JellyFish();
        void Draw();
        
        void Move(int direction);
       
        
        sf::Sprite &GetSprite();
        float* getPosition();
        
        float getHealth();
        void setHealth(float health);
        float getTarget();
        void setTarget(float target);
        void setIsTargeted(bool targeted);
        
        
        
        
    private:
        GameDataRef _data;
        
        sf::Sprite _JellyFishSprite;
        //sf::Clock _movementClock;
        //int _JellyFishState;
       
        float _target;
        int _health;
        bool _isTargeted;
        
        
        
    };
    
}
