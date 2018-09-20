#pragma once

#include <SFML/Graphics.hpp>
#include "DEFINITIONS.hpp"
#include "Game.hpp"
#include <vector>
#include "Bullet.hpp"

namespace g35 {
    
    class SpongeBob{
    public:
        SpongeBob(GameDataRef data);
        void Draw();
       
        void Update(float dt);
        void MoveUp();
        void MoveRight();
        void MoveDown();
        void MoveLeft();
        void MoveStill();
        void MoveUpRight();
        void MoveDownRight();
        void MoveDownLeft();
        void MoveUpLeft();
        sf::Sprite &GetSprite();
        float* getPosition();
        void setHealth(float health);
        float getHealth();
        void shootBeam();
        std::vector<Bullet*>* getBulletVector();
        float getBeamDamage();
        void setBeamDamage(float newBeamDamage);
        bool getFreezeState();
        void setFreezeState(bool isFrozen);
        
        
        
        
        
    private:
        GameDataRef _data;
        sf::Sprite _SpongeBobSprite;
        
        sf::Clock _movementClock;
        sf::Clock _freezeClock;
        int _SpongeBobState;
        int _direction;
        float _health;
        int _beamHealth;
        sf::Vector2f directionVector;
        std::vector<Bullet*> bullets;
        float _beamDamage;
        bool _isFrozen;
        
        
        
    };
    
}
