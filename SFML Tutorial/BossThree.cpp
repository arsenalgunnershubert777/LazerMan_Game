#include "BossThree.hpp"
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <set>
#include <time.h>
/**
 BossThree.cpp
 Purpose: Controls the attacks and health of BossThree
 
 */
//boss three shoots freeze beam that grows in size
namespace g35 {
    BossThree::~BossThree() {
        
    }
    BossThree::BossThree(GameDataRef data):_data(data)
    {
        
        
        _BossThreeSprite.setTexture(_data->assets.GetTexture("BossThree"));
       _BossThreeSprite.setPosition(3*SCREEN_WIDTH/4 - _BossThreeSprite.getGlobalBounds().width/2,SCREEN_HEIGHT/2 - _BossThreeSprite.getGlobalBounds().width/2);
        _health = BOSS_THREE_STARTING_HEALTH;
    }
    
    
    void BossThree::Draw()
    {
        _data->window.draw(_BossThreeSprite);
        for (int i = 0; i < bullets.size(); i++) {
            _data->window.draw(bullets[i]->shape);
        }
    }
    /**
      Moves BossThree in specified direction
      
      @param direction in int form.
      
      */
    
    void BossThree::Move(int direction) {
        switch (direction) {
            case 0:
                break;
            case 1:
                this->_BossThreeSprite.move(0,-BOSS_THREE_MOVEMENT_SPEED);
                break;
            case 2:
                this->_BossThreeSprite.move(BOSS_THREE_MOVEMENT_SPEED,0);
                break;
            case 3:
                this->_BossThreeSprite.move(0,BOSS_THREE_MOVEMENT_SPEED);
                break;
            case 4:
                this->_BossThreeSprite.move(-BOSS_THREE_MOVEMENT_SPEED,0);
                break;
            case 5:
                this->_BossThreeSprite.move(BOSS_THREE_MOVEMENT_SPEED/sqrt(2),-BOSS_THREE_MOVEMENT_SPEED/sqrt(2));
                break;
            case 6:
                this->_BossThreeSprite.move(BOSS_THREE_MOVEMENT_SPEED/sqrt(2),BOSS_THREE_MOVEMENT_SPEED/sqrt(2));
                break;
            case 7:
                this->_BossThreeSprite.move(-BOSS_THREE_MOVEMENT_SPEED/sqrt(2),BOSS_THREE_MOVEMENT_SPEED/sqrt(2));
                break;
            case 8:
                this->_BossThreeSprite.move(-BOSS_THREE_MOVEMENT_SPEED/sqrt(2),-BOSS_THREE_MOVEMENT_SPEED/sqrt(2));
                break;
        }
    }
    /**
      Returns BossThreeSprite.
      
     
      */
    
    sf::Sprite &BossThree::GetSprite()
    {
        return _BossThreeSprite;
    }
    /**
     Returns the position of BossThree.
     
     
     @return the position in array form.
     */
    float* BossThree::getPosition() {
        float* returnData = new float[2];
        returnData[0] = _BossThreeSprite.getGlobalBounds().left + (_BossThreeSprite.getGlobalBounds().width)/2;
        returnData[1] = _BossThreeSprite.getGlobalBounds().top + (_BossThreeSprite.getGlobalBounds().height)/2;
        return returnData;
        
    }
    /**
     Returns the health of BossThree.
     
     */
    float BossThree::getHealth() {
        return this->_health;
    }
    /**
     Sets the specified health of BossThree
     
     @param health.
     */
    void BossThree::setHealth(float health) {
        this->_health = health;
    }
    /**
     Updates BossThree in regards to position and attack location
     
     @param float dt and the position of the player
     
     */
    void BossThree::Update(float dt, float * mainCharacterPosition, sf::FloatRect mainCharacterRect) {
        if (getHealth() > 0) {
            shootBeam(mainCharacterPosition);
            std::set<int> impossibleMoves = getImpossibleMoves();
            int direction = findMoveToTarget(getPosition(), mainCharacterPosition, impossibleMoves);
            Move(direction);
            
        }
        else {
            setHealth(0);
        }
        
        for (int i = 0; i < bullets.size();i++) {
            
            bullets[i]->shape.scale(1.015,1.015);
            bullets[i]->shape.move(bullets[i]->currVelocity);
            if (bullets[i]->shape.getPosition().x < 0 || bullets[i]->shape.getPosition().x > SCREEN_WIDTH || bullets[i]->shape.getPosition().y < 0 || bullets[i]->shape.getPosition().y > SCREEN_HEIGHT) {
                bullets.erase(bullets.begin() + i);
                
                
            }
            
        }
    }
    /**
     Returns the distance of two coordinates
     
     @param the position of BossThree and the target position which is usually around the player position.
     @return the distance.
     */
    float BossThree::getDistance(float* BossThreeMovePosition, float* targetPosition) {
        float distance = sqrt(abs(pow(BossThreeMovePosition[0]- targetPosition[0],2) + pow(BossThreeMovePosition[1]-targetPosition[1],2)));
        return distance;
    }
    std::set<int> BossThree::getImpossibleMoves() {
        std::set<int> impossibleMoves;
        //check for impossible moves
        for (int j = 0; j <= 8; j++) {
            
            switch (j) {
                case 0:
                    break;
                case 1:
                    if (_BossThreeSprite.getPosition().y - BOSS_THREE_MOVEMENT_SPEED < 0 ) {
                        impossibleMoves.insert(j);
                        
                    }
                    
                    
                    break;
                case 2:
                    if (_BossThreeSprite.getPosition().x + _BossThreeSprite.getGlobalBounds().width + BOSS_THREE_MOVEMENT_SPEED  > SCREEN_WIDTH) {
                        
                        impossibleMoves.insert(j);
                    }
                   
                    
                    break;
                case 3:
                    if (_BossThreeSprite.getPosition().y + _BossThreeSprite.getGlobalBounds().height  + BOSS_THREE_MOVEMENT_SPEED  > SCREEN_HEIGHT) {
                        
                        impossibleMoves.insert(j);
                        
                    }
                    
                   
                    break;
                case 4:
                    if (_BossThreeSprite.getPosition().x - BOSS_THREE_MOVEMENT_SPEED  < 0) {
                        
                        impossibleMoves.insert(j);
                    }
                    
                    
                    
                    break;
                case 5:
                    if (_BossThreeSprite.getPosition().y - (BOSS_THREE_MOVEMENT_SPEED/sqrt(2))  < 0  || _BossThreeSprite.getPosition().x + _BossThreeSprite.getGlobalBounds().width + (BOSS_THREE_MOVEMENT_SPEED/sqrt(2))  > SCREEN_WIDTH) {
                        
                        
                        impossibleMoves.insert(j);
                    }
                    
                    
                    break;
                case 6:
                    if (_BossThreeSprite.getPosition().y + _BossThreeSprite.getGlobalBounds().height  + (BOSS_THREE_MOVEMENT_SPEED/sqrt(2))  > SCREEN_HEIGHT  || _BossThreeSprite.getPosition().x + _BossThreeSprite.getGlobalBounds().width + (BOSS_THREE_MOVEMENT_SPEED/sqrt(2))  > SCREEN_WIDTH) {
                        impossibleMoves.insert(j);
                        
                        
                        
                    }
                    
                    
                    break;
                case 7:
                    if (_BossThreeSprite.getPosition().y + _BossThreeSprite.getGlobalBounds().height  + (BOSS_THREE_MOVEMENT_SPEED/sqrt(2))  > SCREEN_HEIGHT  || _BossThreeSprite.getPosition().x - (BOSS_THREE_MOVEMENT_SPEED/sqrt(2))  < 0) {
                        impossibleMoves.insert(j);
                        
                        
                    }
                    
                    
                    
                    break;
                case 8:
                    if (_BossThreeSprite.getPosition().y - (BOSS_THREE_MOVEMENT_SPEED/sqrt(2))  < 0  || _BossThreeSprite.getPosition().x - (BOSS_THREE_MOVEMENT_SPEED/sqrt(2))  < 0) {
                        impossibleMoves.insert(j);
                        
                        
                    }
                    
                    
                    break;
            }
            
            
            
        }
        return impossibleMoves;
    }
    int BossThree::findMoveToTarget(float * BossThreePosition, float * targetPosition, std::set<int> impossibleMoves) {
        int direction = 0;
        float distance = 0;
        float minDist = -1;
        float * BossThreeMovePosition = new float[2];
        for (int j = 1; j <= 8; j++) {
            if (std::find(impossibleMoves.begin(), impossibleMoves.end(), j) == impossibleMoves.end()) {
                switch (j) {
                    case 0:
                        
                        BossThreeMovePosition[0] = BossThreePosition[0];
                        BossThreeMovePosition[1] = BossThreePosition[1];
                        break;
                    case 1:
                        BossThreeMovePosition[0] = BossThreePosition[0];
                        BossThreeMovePosition[1] = BossThreePosition[1]-BOSS_THREE_MOVEMENT_SPEED;
                        
                        
                        break;
                    case 2:
                        BossThreeMovePosition[0] = BossThreePosition[0]+BOSS_THREE_MOVEMENT_SPEED;
                        BossThreeMovePosition[1] = BossThreePosition[1];
                        
                        break;
                    case 3:
                        BossThreeMovePosition[0] = BossThreePosition[0];
                        BossThreeMovePosition[1] = BossThreePosition[1]+BOSS_THREE_MOVEMENT_SPEED;
                        
                        
                        break;
                    case 4:
                        BossThreeMovePosition[0] = BossThreePosition[0]-BOSS_THREE_MOVEMENT_SPEED;
                        BossThreeMovePosition[1] = BossThreePosition[1];
                        
                        
                        break;
                    case 5:
                        BossThreeMovePosition[0] = BossThreePosition[0] + BOSS_THREE_MOVEMENT_SPEED/sqrt(2);
                        BossThreeMovePosition[1] = BossThreePosition[1]-BOSS_THREE_MOVEMENT_SPEED/sqrt(2);
                        
                        break;
                    case 6:
                        BossThreeMovePosition[0] = BossThreePosition[0] + BOSS_THREE_MOVEMENT_SPEED/sqrt(2);
                        BossThreeMovePosition[1] = BossThreePosition[1]+BOSS_THREE_MOVEMENT_SPEED/sqrt(2);
                        
                        break;
                    case 7:
                        BossThreeMovePosition[0] = BossThreePosition[0] -BOSS_THREE_MOVEMENT_SPEED/sqrt(2);
                        BossThreeMovePosition[1] = BossThreePosition[1]+BOSS_THREE_MOVEMENT_SPEED/sqrt(2);
                        break;
                    case 8:
                        BossThreeMovePosition[0] = BossThreePosition[0] - BOSS_THREE_MOVEMENT_SPEED/sqrt(2);
                        BossThreeMovePosition[1] = BossThreePosition[1]-BOSS_THREE_MOVEMENT_SPEED/sqrt(2);
                        break;
                        
                }
                distance = getDistance(BossThreeMovePosition, targetPosition);
                
                
                if (minDist < 0) {
                    minDist = distance;
                    direction = j;
                }
                else if (distance < minDist) {
                    minDist = distance;
                    direction = j;
                    
                }
            }
        }
        return direction;
    }
    /**
     Controls the bullets that are being shot
     
     @param the position of the main character
     */
    void BossThree::shootBeam(float * mainCharacterPosition) {
        if (_clock.getElapsedTime().asSeconds() > 3) {
            Bullet *b1 = new Bullet(BOSS_THREE_BEAM_RADIUS_BEGIN, sf::Color::Cyan);
            b1->shape.setOrigin(BOSS_THREE_BEAM_RADIUS_BEGIN, BOSS_THREE_BEAM_RADIUS_BEGIN);
            b1->shape.setPosition(this->getPosition()[0],this->getPosition()[1]);
            sf::Vector2f directionVector;
            directionVector.x = mainCharacterPosition[0] - getPosition()[0];
            directionVector.y = mainCharacterPosition[1] - getPosition()[1];
            float speedAdjuster = BOSS_THREE_BEAM_SPEED_SET/sqrt(pow(directionVector.x,2) + pow(directionVector.y,2));
            
            b1->currVelocity = speedAdjuster * directionVector * b1->maxSpeed;
            
            bullets.push_back(b1);
            _clock.restart();
        }
        
        
        
    }
    std::vector<Bullet*>* BossThree::getBulletVector() {
        return &this->bullets;
    }
    
}
