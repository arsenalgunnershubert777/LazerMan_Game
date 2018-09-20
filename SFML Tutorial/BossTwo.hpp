#pragma once

#include <SFML/Graphics.hpp>
#include "DEFINITIONS.hpp"
#include "Game.hpp"
#include <vector>
#include "Bullet.hpp"
#include <set>
#include "Enemies.hpp"

/**
 BossTwo.hpp
 Purpose: to keep all the variable declaration and functions used for BossTwo accesible
 */

namespace g35 {
    
    class BossTwo: public Enemies {
    public:
        ~BossTwo();
        BossTwo(GameDataRef data);
        void Draw();
        
        void Update(float dt, float * mainCharacterPosition, sf::FloatRect mainCharacterRect);
        void Move(int direction);
        sf::Sprite &GetSprite();
        
        
        float* getPosition();
        void setHealth(float health);
        float getHealth();
        float getDistance(float* BossTwoMovePosition, float* targetPosition);
        std::set<int> getImpossibleMoves();
        
        int findMoveToTarget(float * BossTwoPosition, float * targetPosition, std::set<int> impossibleMoves);
        void shootBeam();
        std::vector<Bullet*>* getBulletVector();
        
        
    private:
        GameDataRef _data;
        sf::Sprite _BossTwoSprite;
        sf::Clock _clock;
        float _health;
        sf::Clock _spawnClock;
        std::vector<Bullet*> bullets;
        
        
        
    };
    
}
