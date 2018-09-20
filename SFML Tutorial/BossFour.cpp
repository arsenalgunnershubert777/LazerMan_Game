#include "BossFour.hpp"
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <set>
#include <time.h>
/**
 BossFour.cpp
 Purpose: to update and control BossFour in regards to location , attacks, health
 */
//boss four shoots guided beams quickly toward player

namespace g35 {
    BossFour::~BossFour() {
        
    }
    /**
     Sets the sprites, health and initial position that will be used for BossFour
     
     @param data that will be used to access the texture files
     */
    BossFour::BossFour(GameDataRef data):_data(data)
    {
        
        
        _BossFourSprite.setTexture(_data->assets.GetTexture("BossFourStage1"));
        _BossFourSprite.setPosition(3*SCREEN_WIDTH/4 - _BossFourSprite.getGlobalBounds().width/2,SCREEN_HEIGHT/2 - _BossFourSprite.getGlobalBounds().width/2);
        _health = BOSS_FOUR_STARTING_HEALTH;
        rageMode = false; //two modes, one normal mode and one hard mode when its health is low
        pastMainCharacterLocation = new float[2];
        pastMainCharacterLocation[0] = -1;
        pastMainCharacterLocation[1] = -1;
    }
    
    /**
     Draws BossFour into the window
     */
    void BossFour::Draw()
    {
    
        _data->window.draw(_BossFourSprite);
        
        for (int i = 0; i < bullets.size(); i++) {
            _data->window.draw(bullets[i]->shape);
        }
    }
    /**
     moves BossFour in specificied direction
     
     @param the direction
     */
    void BossFour::Move(int direction) {
        float speed;
        if (rageMode) {
            speed = BOSS_FOUR_MOVEMENT_RAGE_SPEED;
            
        }
        else {
            speed = BOSS_FOUR_MOVEMENT_SPEED;
        }
        switch (direction) {
                
            case 0:
                break;
            case 1:
                this->_BossFourSprite.move(0,-speed);
                break;
            case 2:
                this->_BossFourSprite.move(speed,0);
                break;
            case 3:
                this->_BossFourSprite.move(0,speed);
                break;
            case 4:
                this->_BossFourSprite.move(-speed,0);
                break;
            case 5:
                this->_BossFourSprite.move(speed/sqrt(2),-speed/sqrt(2));
                break;
            case 6:
                this->_BossFourSprite.move(speed/sqrt(2),speed/sqrt(2));
                break;
            case 7:
                this->_BossFourSprite.move(-speed/sqrt(2),speed/sqrt(2));
                break;
            case 8:
                this->_BossFourSprite.move(-speed/sqrt(2),-speed/sqrt(2));
                break;
        }
    }
    
    /**
     Returns the sprite for BossFour
     */
    sf::Sprite &BossFour::GetSprite()
    {
        return _BossFourSprite;
    }
    
    /**
     Returns the position of BossFour.
     */
    float* BossFour::getPosition() {
        float* returnData = new float[2];
        returnData[0] = _BossFourSprite.getGlobalBounds().left + (_BossFourSprite.getGlobalBounds().width)/2;
        returnData[1] = _BossFourSprite.getGlobalBounds().top + (_BossFourSprite.getGlobalBounds().height)/2;
        return returnData;
        
    }
    
    float BossFour::getHealth() {
        return this->_health;
    }
    /**
     Sets the specified health for BossFour
     
     @param the specified Health
     */
    
    void BossFour::setHealth(float health) {
        this->_health = health;
    }
    
    /**
     Updates BossFour health, attacks and position
     
     @param dt, and the position of the player
     */
    
    
    void BossFour::Update(float dt, float * mainCharacterPosition, sf::FloatRect mainCharacterRect) {
        if (_health <= BOSS_FOUR_STARTING_HEALTH/3 && !rageMode) {
            rageMode = true;
            _BossFourSprite.setTexture(_data->assets.GetTexture("BossFourStage2"), true);
            
            
        }
        if (_health > 0) {
            if (pastMainCharacterLocation[0] == -1) {
                pastMainCharacterLocation = mainCharacterPosition;
            }
            float * newLocationExpected = new float[2];
            newLocationExpected[0] = (mainCharacterPosition[0] - pastMainCharacterLocation[0]) + mainCharacterPosition[0];
            newLocationExpected[1] = (mainCharacterPosition[1] - pastMainCharacterLocation[1]) + mainCharacterPosition[1];
            
            shootBeam(newLocationExpected);
            std::set<int> impossibleMoves = getImpossibleMoves();
            int direction = findMoveToTarget(getPosition(), newLocationExpected, impossibleMoves);
            Move(direction);
            pastMainCharacterLocation = mainCharacterPosition;
            
        }
        else {
            _health = 0;
        }
        
        for (int i = 0; i < bullets.size();i++) {
            
            bullets[i]->currVelocity.x *= 1.001;
            bullets[i]->currVelocity.y *= 1.001;
            bullets[i]->shape.move(bullets[i]->currVelocity);
            if (bullets[i]->shape.getPosition().x < 0 || bullets[i]->shape.getPosition().x > SCREEN_WIDTH || bullets[i]->shape.getPosition().y < 0 || bullets[i]->shape.getPosition().y > SCREEN_HEIGHT) {
                bullets.erase(bullets.begin() + i);
                
                
            }
            
        }
    }
    /**
     Returns the distance between two points
     
     @param the position of bossFour and the target position which in this case is the player.
     @return the distance.
     */
    float BossFour::getDistance(float* BossFourMovePosition, float* targetPosition) {
        float distance = sqrt(abs(pow(BossFourMovePosition[0]- targetPosition[0],2) + pow(BossFourMovePosition[1]-targetPosition[1],2)));
        return distance;
    }
    /**
     to check for impossible Moves
     */
    std::set<int> BossFour::getImpossibleMoves() {
        std::set<int> impossibleMoves;
        //check for impossible moves
        for (int j = 0; j <= 8; j++) {
            
            switch (j) {
                case 0:
                    break;
                case 1:
                    if (_BossFourSprite.getPosition().y - BOSS_FOUR_MOVEMENT_SPEED < 0 ) {
                        impossibleMoves.insert(j);
                        
                    }
                    
                   
                    break;
                case 2:
                    if (_BossFourSprite.getPosition().x + _BossFourSprite.getGlobalBounds().width + BOSS_FOUR_MOVEMENT_SPEED  > SCREEN_WIDTH) {
                        
                        impossibleMoves.insert(j);
                    }
                  
                    
                    break;
                case 3:
                    if (_BossFourSprite.getPosition().y + _BossFourSprite.getGlobalBounds().height  + BOSS_FOUR_MOVEMENT_SPEED  > SCREEN_HEIGHT) {
                        
                        impossibleMoves.insert(j);
                        
                    }
                    
                   
                    break;
                case 4:
                    if (_BossFourSprite.getPosition().x - BOSS_FOUR_MOVEMENT_SPEED  < 0) {
                        
                        impossibleMoves.insert(j);
                    }
                    
                    
                  
                    break;
                case 5:
                    if (_BossFourSprite.getPosition().y - (BOSS_FOUR_MOVEMENT_SPEED/sqrt(2))  < 0  || _BossFourSprite.getPosition().x + _BossFourSprite.getGlobalBounds().width + (BOSS_FOUR_MOVEMENT_SPEED/sqrt(2))  > SCREEN_WIDTH) {
                        
                        
                        impossibleMoves.insert(j);
                    }
                    
                    
                    break;
                case 6:
                    if (_BossFourSprite.getPosition().y + _BossFourSprite.getGlobalBounds().height  + (BOSS_FOUR_MOVEMENT_SPEED/sqrt(2))  > SCREEN_HEIGHT  || _BossFourSprite.getPosition().x + _BossFourSprite.getGlobalBounds().width + (BOSS_FOUR_MOVEMENT_SPEED/sqrt(2))  > SCREEN_WIDTH) {
                        impossibleMoves.insert(j);
                        
                        
                        
                    }
                    
                    
                    break;
                case 7:
                    if (_BossFourSprite.getPosition().y + _BossFourSprite.getGlobalBounds().height  + (BOSS_FOUR_MOVEMENT_SPEED/sqrt(2))  > SCREEN_HEIGHT  || _BossFourSprite.getPosition().x - (BOSS_FOUR_MOVEMENT_SPEED/sqrt(2))  < 0) {
                        impossibleMoves.insert(j);
                        
                        
                    }
                    
                    
                    
                    break;
                case 8:
                    if (_BossFourSprite.getPosition().y - (BOSS_FOUR_MOVEMENT_SPEED/sqrt(2))  < 0  || _BossFourSprite.getPosition().x - (BOSS_FOUR_MOVEMENT_SPEED/sqrt(2))  < 0) {
                        impossibleMoves.insert(j);
                        
                        
                    }
                    
                    
                    break;
            }
            
            
            
        }
        return impossibleMoves;
    }
    /**
     finds the right direction to move to get to target
     
     @param the position of BossFour and the Position of the target which in this case is the player
     @return the direction to move
     */
    int BossFour::findMoveToTarget(float * BossFourPosition, float * targetPosition, std::set<int> impossibleMoves) {
        int direction = 0;
        float distance = 0;
        float minDist = -1;
        float * BossFourMovePosition = new float[2];
        for (int j = 1; j <= 8; j++) {
            if (std::find(impossibleMoves.begin(), impossibleMoves.end(), j) == impossibleMoves.end()) {
                switch (j) {
                    case 0:
                        
                        BossFourMovePosition[0] = BossFourPosition[0];
                        BossFourMovePosition[1] = BossFourPosition[1];
                        break;
                    case 1:
                        BossFourMovePosition[0] = BossFourPosition[0];
                        BossFourMovePosition[1] = BossFourPosition[1]-BOSS_FOUR_MOVEMENT_SPEED;
                        
                        
                        break;
                    case 2:
                        BossFourMovePosition[0] = BossFourPosition[0]+BOSS_FOUR_MOVEMENT_SPEED;
                        BossFourMovePosition[1] = BossFourPosition[1];
                        
                        break;
                    case 3:
                        BossFourMovePosition[0] = BossFourPosition[0];
                        BossFourMovePosition[1] = BossFourPosition[1]+BOSS_FOUR_MOVEMENT_SPEED;
                        
                        
                        break;
                    case 4:
                        BossFourMovePosition[0] = BossFourPosition[0]-BOSS_FOUR_MOVEMENT_SPEED;
                        BossFourMovePosition[1] = BossFourPosition[1];
                        
                        
                        break;
                    case 5:
                        BossFourMovePosition[0] = BossFourPosition[0] + BOSS_FOUR_MOVEMENT_SPEED/sqrt(2);
                        BossFourMovePosition[1] = BossFourPosition[1]-BOSS_FOUR_MOVEMENT_SPEED/sqrt(2);
                        
                        break;
                    case 6:
                        BossFourMovePosition[0] = BossFourPosition[0] + BOSS_FOUR_MOVEMENT_SPEED/sqrt(2);
                        BossFourMovePosition[1] = BossFourPosition[1]+BOSS_FOUR_MOVEMENT_SPEED/sqrt(2);
                        
                        break;
                    case 7:
                        BossFourMovePosition[0] = BossFourPosition[0] -BOSS_FOUR_MOVEMENT_SPEED/sqrt(2);
                        BossFourMovePosition[1] = BossFourPosition[1]+BOSS_FOUR_MOVEMENT_SPEED/sqrt(2);
                        break;
                    case 8:
                        BossFourMovePosition[0] = BossFourPosition[0] - BOSS_FOUR_MOVEMENT_SPEED/sqrt(2);
                        BossFourMovePosition[1] = BossFourPosition[1]-BOSS_FOUR_MOVEMENT_SPEED/sqrt(2);
                        break;
                        
                }
                distance = getDistance(BossFourMovePosition, targetPosition);
                
                
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
     boss Four's beam attacks
     */
    void BossFour::shootBeam(float * mainCharacterPosition) {
        if (!rageMode) {
            if (_clock.getElapsedTime().asSeconds() > 1) {
                
                Bullet * b1 = new Bullet(BOSS_FOUR_BEAM_RADIUS_STAGE1, sf::Color::Green);
                b1->shape.setOrigin(BOSS_FOUR_BEAM_RADIUS_STAGE1, BOSS_FOUR_BEAM_RADIUS_STAGE1);
                b1->shape.setPosition(this->getPosition()[0],this->getPosition()[1]);
                sf::Vector2f directionVector;
                directionVector.x = mainCharacterPosition[0] - getPosition()[0];
                directionVector.y = mainCharacterPosition[1] - getPosition()[1];
                float speedAdjuster = BOSS_FOUR_BEAM_SPEED_STAGE1_SET/sqrt(pow(directionVector.x,2) + pow(directionVector.y,2));
                
                b1->currVelocity = speedAdjuster * directionVector * b1->maxSpeed;
                
                bullets.push_back(b1);
                _clock.restart();
                
                
                    
                
            }
           
        }
        else {
            Bullet * b1  = new Bullet(BOSS_FOUR_BEAM_RADIUS_STAGE2, sf::Color(255,150,50,240));
            b1->shape.setOrigin(BOSS_FOUR_BEAM_RADIUS_STAGE2, BOSS_FOUR_BEAM_RADIUS_STAGE2);
          
            b1->shape.setPosition(this->getPosition()[0],this->getPosition()[1]);
            sf::Vector2f directionVector;
            directionVector.x = mainCharacterPosition[0] - getPosition()[0];
            directionVector.y = mainCharacterPosition[1] - getPosition()[1];
            float speedAdjuster = BOSS_FOUR_BEAM_SPEED_STAGE2_SET/sqrt(pow(directionVector.x,2) + pow(directionVector.y,2));
            
            b1->currVelocity = speedAdjuster * directionVector * b1->maxSpeed;
            
            bullets.push_back(b1);
           
        
        }
            
        
        
        
        
    }
    std::vector<Bullet*>* BossFour::getBulletVector() {
        return &this->bullets;
    }
    
}
