#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

namespace g35{
    class Bullet {
    public:
        sf::CircleShape shape;
        sf::Vector2f currVelocity;
        float maxSpeed;
        Bullet(float radius = 5.f, sf::Color color = sf::Color::Blue);
        
        
    };
    
}
