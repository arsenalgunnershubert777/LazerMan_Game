#pragma once

#include <SFML/Graphics.hpp>
#include "DEFINITIONS.hpp"
#include "Game.hpp"
#include <vector>
#include "Bullet.hpp"
#include <set>
#include "Enemies.hpp"
/*
 BossOne.hpp
 Purpose: to keep all the declaration of variables and fuction of BossOne
 
 */
namespace g35 {
    
    class BossOne: public Enemies {
    public:
        BossOne(GameDataRef data);
        ~BossOne();
        void Draw();
        
        void Update(float dt, float * mainCharacterPosition, sf::FloatRect mainCharacterRect);
        void Move(int direction);
        sf::Sprite &GetSprite();
        
        
        float* getPosition();
        void setHealth(float health);
        float getHealth();
        float getDistance(float* BossOneMovePosition, float* targetPosition);
        std::set<int> getImpossibleMoves();
        
        int findMoveToTarget(float * BossOnePosition, float * targetPosition, std::set<int> impossibleMoves);
        const bool _canFreeze = false;
        
        
        
    private:
        GameDataRef _data;
        sf::Sprite _BossOneSprite;
        sf::Clock _clock;
        float _health;
        bool _isChasing;
        
        
        
        
        
        
    };
    
}
