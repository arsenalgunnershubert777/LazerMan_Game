#include "InputManager.hpp"

namespace g35 //this object provides functionality for testing if there is important input
{
    bool InputManager::IsSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow &window)
    {
        if (sf::Mouse::isButtonPressed(button))
        {
            sf::IntRect tempRect(object.getPosition().x, object.getPosition().y, object.getGlobalBounds().width, object.getGlobalBounds().height);
            
            
            if (tempRect.contains(sf::Mouse::getPosition(window)))
            {
                return true;
            }
            
        }
        
        return false;
    }
    
    sf::Vector2i InputManager::GetMousePosition(sf::RenderWindow &window)
    {
        return sf::Mouse::getPosition(window);
    }
    
    bool InputManager::IsKeyClicked(sf::Keyboard::Key key)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(key)))
        {
            return true;
        }
        return false;
    }
    
}
