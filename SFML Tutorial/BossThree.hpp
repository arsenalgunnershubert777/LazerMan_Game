#pragma once

#include <SFML/Graphics.hpp>
#include "DEFINITIONS.hpp"
#include "Game.hpp"
#include <vector>
#include "Bullet.hpp"
#include <set>
#include "Enemies.hpp"
/**
 BossThree.hpp
 Purpose: To keep the declarations of variables and function and have them accessible
 */

namespace g35 {
    
    class BossThree: public Enemies {
    public:
        ~BossThree();
        BossThree(GameDataRef data);
        void Draw();
        
        void Update(float dt, float * mainCharacterPosition, sf::FloatRect mainCharacterRect);
        void Move(int direction);
        sf::Sprite &GetSprite();
        
        
        float* getPosition();
        void setHealth(float health);
        float getHealth();
        float getDistance(float* BossThreeMovePosition, float* targetPosition);
        std::set<int> getImpossibleMoves();
        
        int findMoveToTarget(float * BossThreePosition, float * targetPosition, std::set<int> impossibleMoves);
        void shootBeam(float * mainCharacterPosition);
        std::vector<Bullet*>* getBulletVector();
        
        
    private:
        GameDataRef _data;
        sf::Sprite _BossThreeSprite;
        sf::Clock _clock;
        float _health;
        std::vector<Bullet*> bullets;
        
        
        
    };
    
}
