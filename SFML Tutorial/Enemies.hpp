#pragma once
#include "Bullet.hpp"
namespace g35 { //abstract class for bosses
    class Enemies {
    public:
        virtual void Draw() = 0;
        virtual void Update(float dt, float * mainCharacterPosition, sf::FloatRect mainCharacterRect) = 0;
        virtual void Move(int direction) = 0;
        virtual sf::Sprite &GetSprite() = 0;
        virtual float* getPosition() = 0;
        virtual void setHealth(float health) = 0;
        virtual float getHealth() = 0;
        virtual std::vector<Bullet*>* getBulletVector() {return new std::vector<Bullet*>;}
        virtual ~Enemies() {}
    private:
        float _health;
    };
}
