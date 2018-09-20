#pragma once

#include <SFML/Graphics.hpp>
#include "DEFINITIONS.hpp"
#include "Game.hpp"
#include <vector>
#include "Bullet.hpp"
#include <set>
#include "Enemies.hpp"



namespace g35 {
    
    class BossFour: public Enemies {
    public:
        ~BossFour();
        BossFour(GameDataRef data);
        void Draw();
        
        void Update(float dt, float * mainCharacterPosition, sf::FloatRect mainCharacterRect);
        void Move(int direction);
        sf::Sprite &GetSprite();
        
        
        float* getPosition();
        void setHealth(float health);
        float getHealth();
        float getDistance(float* BossFourMovePosition, float* targetPosition);
        std::set<int> getImpossibleMoves();
        
        int findMoveToTarget(float * BossFourPosition, float * targetPosition, std::set<int> impossibleMoves);
        void shootBeam(float * mainCharacterPosition);
        std::vector<Bullet*>* getBulletVector();
        
        
    private:
        GameDataRef _data;
        sf::Sprite _BossFourSprite;
        sf::Clock _clock;
        float _health;
        bool rageMode;
        std::vector<Bullet*> bullets;
        float * pastMainCharacterLocation;
        
        
        
    };
    
}
