#include "Bullet.hpp"

namespace g35 { //class for beam/laser
    Bullet::Bullet(float radius, sf::Color color):currVelocity(0.f,0.f),maxSpeed(10.f) {
        this->shape.setRadius(radius);
        this->shape.setFillColor(color);
        
        
        
    }
    
}
