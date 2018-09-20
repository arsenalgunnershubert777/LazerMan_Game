#include "JellyFish.hpp"
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

//jellfish aka minions, are annoying nuissances that damage the player when touched
namespace g35 { //this is the minion class, which has the simple requirements for the minion behavior, but is
    JellyFish::JellyFish() { //controlled by an overarching class called JellyFishAI
        
    }
    JellyFish::JellyFish(GameDataRef data):_data(data)
    {
        
        _JellyFishSprite.setTexture(_data->assets.GetTexture("Minion"));
        _JellyFishSprite.setPosition(SCREEN_WIDTH/4,SCREEN_HEIGHT/4);
        
      
        _health = MINION_STARTING_HEALTH;
        _target = -1;
        _isTargeted = false;
        
    }
    
    float JellyFish::getTarget() { //there is a target the minions have
        return this->_target;
    }
    void JellyFish::setTarget(float target) {
        this->_target = target;
    }
    void JellyFish::Draw()
    {
        _data->window.draw(_JellyFishSprite);
        
    }
    
    void JellyFish::Move(int direction) {
        switch (direction) {
            case 0:
                break;
            case 1:
                this->_JellyFishSprite.move(0,-MINION_MOVEMENT_SPEED);
                break;
            case 2:
                this->_JellyFishSprite.move(MINION_MOVEMENT_SPEED,0);
                break;
            case 3:
                this->_JellyFishSprite.move(0,MINION_MOVEMENT_SPEED);
                break;
            case 4:
                this->_JellyFishSprite.move(-MINION_MOVEMENT_SPEED,0);
                break;
        }
    }
    
    sf::Sprite &JellyFish::GetSprite()
    {
        return _JellyFishSprite;
    }
    
    float* JellyFish::getPosition() {
        float* returnData = new float[2];
        returnData[0] = _JellyFishSprite.getGlobalBounds().left + (_JellyFishSprite.getGlobalBounds().width)/2;
        returnData[1] = _JellyFishSprite.getGlobalBounds().top + (_JellyFishSprite.getGlobalBounds().height)/2;
        return returnData;
        
    }
    float JellyFish::getHealth() {
        return this->_health;
    }
    void JellyFish::setHealth(float health) {
        this->_health = health;
    }
    
    void JellyFish::setIsTargeted(bool targeted){
        this->_isTargeted = targeted;
    }
    
    
    
    
}
