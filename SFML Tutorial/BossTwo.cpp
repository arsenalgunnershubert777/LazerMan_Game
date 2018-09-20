#include "BossTwo.hpp"
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <set>
#include <time.h>
/**
 BossTwo.cpp
 Purpose: to update and control BossTwo in regards to location , attacks, health
 */
//boss two teleports around and shoots beam around itself

namespace g35 {
    BossTwo::~BossTwo() {
        
    }
    /**
     Sets the sprites, health and initial position that will be used for BossTwo
     
     @param data that will be used to access the texture files
     */
    BossTwo::BossTwo(GameDataRef data):_data(data)
    {
        
        
        _BossTwoSprite.setTexture(_data->assets.GetTexture("BossTwo"));
    
        _BossTwoSprite.setPosition(3*SCREEN_WIDTH/4 - _BossTwoSprite.getGlobalBounds().width/2,SCREEN_HEIGHT/2 - _BossTwoSprite.getGlobalBounds().width/2);
        _health = BOSS_TWO_STARTING_HEALTH;
    }
    /**
     Draws BossTwo into window
     */
    
    void BossTwo::Draw()
    {
        _data->window.draw(_BossTwoSprite);
        for (int i = 0; i < bullets.size(); i++) {
            _data->window.draw(bullets[i]->shape);
        }
    }
    /**
     moves in the direction for BossTwo
     
     @param the direction
     */
    void BossTwo::Move(int direction) {
        switch (direction) {
            case 0:
                break;
            case 1:
                this->_BossTwoSprite.move(0,-BOSS_TWO_MOVEMENT_SPEED);
                break;
            case 2:
                this->_BossTwoSprite.move(BOSS_TWO_MOVEMENT_SPEED,0);
                break;
            case 3:
                this->_BossTwoSprite.move(0,BOSS_TWO_MOVEMENT_SPEED);
                break;
            case 4:
                this->_BossTwoSprite.move(-BOSS_TWO_MOVEMENT_SPEED,0);
                break;
            case 5:
                this->_BossTwoSprite.move(BOSS_TWO_MOVEMENT_SPEED/sqrt(2),-BOSS_TWO_MOVEMENT_SPEED/sqrt(2));
                break;
            case 6:
                this->_BossTwoSprite.move(BOSS_TWO_MOVEMENT_SPEED/sqrt(2),BOSS_TWO_MOVEMENT_SPEED/sqrt(2));
                break;
            case 7:
                this->_BossTwoSprite.move(-BOSS_TWO_MOVEMENT_SPEED/sqrt(2),BOSS_TWO_MOVEMENT_SPEED/sqrt(2));
                break;
            case 8:
                this->_BossTwoSprite.move(-BOSS_TWO_MOVEMENT_SPEED/sqrt(2),-BOSS_TWO_MOVEMENT_SPEED/sqrt(2));
                break;
        }
    }
    /**
     Returns the sprite for BossTwo
     */
    sf::Sprite &BossTwo::GetSprite()
    {
        return _BossTwoSprite;
    }
    /**
     Returns the position of BossTwo.
     */
    float* BossTwo::getPosition() {
        float* returnData = new float[2];
        returnData[0] = _BossTwoSprite.getGlobalBounds().left + (_BossTwoSprite.getGlobalBounds().width)/2;
        returnData[1] = _BossTwoSprite.getGlobalBounds().top + (_BossTwoSprite.getGlobalBounds().height)/2;
        return returnData;
        
    }
    /**
     Returns the specified health for BossTwo
     */
    float BossTwo::getHealth() {
        return this->_health;
    }
    /**
     Sets the specified health for BossTwo
     
     @param the specified Health
     */
    void BossTwo::setHealth(float health) {
        this->_health = health;
    }
    /**
     Updates BossTwo health, attacks and position
     
     @param dt, and the position of the player
     */
    void BossTwo::Update(float dt, float * mainCharacterPosition, sf::FloatRect mainCharacterRect) {
        srand(time(NULL));
        if (getHealth() > 0) {
            shootBeam();
            if (_spawnClock.getElapsedTime().asSeconds() > 2) {
                float x = (float)(rand()%(int)(SCREEN_WIDTH-(_BossTwoSprite.getGlobalBounds().width*2+1)) + _BossTwoSprite.getGlobalBounds().width);
                float y = (float)(rand()%(int)(SCREEN_HEIGHT-(_BossTwoSprite.getGlobalBounds().height*2+1)) + _BossTwoSprite.getGlobalBounds().height);
                _BossTwoSprite.setPosition(x,y );
                _spawnClock.restart();
            }
            
        }
        else {
            setHealth(0);
        }
        bool restartClock = false;
        for (int i = 0; i < bullets.size();i++) {
            bullets[i]->shape.move(bullets[i]->currVelocity);
            float * bulletPosition = new float[2];
            bulletPosition[0] = bullets[i]->shape.getPosition().x;
            bulletPosition[1] = bullets[i]->shape.getPosition().y;
            
            if (getDistance(bulletPosition, getPosition()) > 200) {
                bullets.erase(bullets.begin() + i);
                restartClock = true;
    
                
            }
            
        }
        if (restartClock) {
            _clock.restart();
        }
    
    }/**
      Returns the distance between two coordinates
      
      @param the position of bosstwo and the target position which in this case is likely the player or player's neighbors
      @return the distance.
      */
    float BossTwo::getDistance(float* BossTwoMovePosition, float* targetPosition) {
        float distance = sqrt(abs(pow(BossTwoMovePosition[0]- targetPosition[0],2) + pow(BossTwoMovePosition[1]-targetPosition[1],2)));
        return distance;
    }
    std::set<int> BossTwo::getImpossibleMoves() {
        std::set<int> impossibleMoves;
        //check for impossible moves
        for (int j = 0; j <= 8; j++) {
            
            switch (j) {
                case 0:
                    break;
                case 1:
                    if (_BossTwoSprite.getPosition().y - BOSS_TWO_MOVEMENT_SPEED < 0 ) {
                        impossibleMoves.insert(j);
                        
                    }
                    
                 
                    break;
                case 2:
                    if (_BossTwoSprite.getPosition().x + _BossTwoSprite.getGlobalBounds().width + BOSS_TWO_MOVEMENT_SPEED  > SCREEN_WIDTH) {
                        
                        impossibleMoves.insert(j);
                    }
                    
                    
                    break;
                case 3:
                    if (_BossTwoSprite.getPosition().y + _BossTwoSprite.getGlobalBounds().height  + BOSS_TWO_MOVEMENT_SPEED  > SCREEN_HEIGHT) {
                        
                        impossibleMoves.insert(j);
                        
                    }
                    
                    
                    break;
                case 4:
                    if (_BossTwoSprite.getPosition().x - BOSS_TWO_MOVEMENT_SPEED  < 0) {
                        
                        impossibleMoves.insert(j);
                    }
                    
                    
                    
                    break;
                case 5:
                    if (_BossTwoSprite.getPosition().y - (BOSS_TWO_MOVEMENT_SPEED/sqrt(2))  < 0  || _BossTwoSprite.getPosition().x + _BossTwoSprite.getGlobalBounds().width + (BOSS_TWO_MOVEMENT_SPEED/sqrt(2))  > SCREEN_WIDTH) {
                        
                        
                        impossibleMoves.insert(j);
                    }
                    
                    
                    break;
                case 6:
                    if (_BossTwoSprite.getPosition().y + _BossTwoSprite.getGlobalBounds().height  + (BOSS_TWO_MOVEMENT_SPEED/sqrt(2))  > SCREEN_HEIGHT  || _BossTwoSprite.getPosition().x + _BossTwoSprite.getGlobalBounds().width + (BOSS_TWO_MOVEMENT_SPEED/sqrt(2))  > SCREEN_WIDTH) {
                        impossibleMoves.insert(j);
                        
                        
                        
                    }
                    
                    
                    break;
                case 7:
                    if (_BossTwoSprite.getPosition().y + _BossTwoSprite.getGlobalBounds().height  + (BOSS_TWO_MOVEMENT_SPEED/sqrt(2))  > SCREEN_HEIGHT  || _BossTwoSprite.getPosition().x - (BOSS_TWO_MOVEMENT_SPEED/sqrt(2))  < 0) {
                        impossibleMoves.insert(j);
                        
                        
                    }
                    
                    
                    
                    break;
                case 8:
                    if (_BossTwoSprite.getPosition().y - (BOSS_TWO_MOVEMENT_SPEED/sqrt(2))  < 0  || _BossTwoSprite.getPosition().x - (BOSS_TWO_MOVEMENT_SPEED/sqrt(2))  < 0) {
                        impossibleMoves.insert(j);
                        
                        
                    }
                    
                    
                    break;
            }
            
            
            
        }
        return impossibleMoves;
    }
    int BossTwo::findMoveToTarget(float * BossTwoPosition, float * targetPosition, std::set<int> impossibleMoves) {
        int direction = 0;
        float distance = 0;
        float minDist = -1;
        float * BossTwoMovePosition = new float[2];
        for (int j = 1; j <= 8; j++) {
            if (std::find(impossibleMoves.begin(), impossibleMoves.end(), j) == impossibleMoves.end()) {
                switch (j) {
                    case 0:
                        
                        BossTwoMovePosition[0] = BossTwoPosition[0];
                        BossTwoMovePosition[1] = BossTwoPosition[1];
                        break;
                    case 1:
                        BossTwoMovePosition[0] = BossTwoPosition[0];
                        BossTwoMovePosition[1] = BossTwoPosition[1]-BOSS_TWO_MOVEMENT_SPEED;
                        
                        
                        break;
                    case 2:
                        BossTwoMovePosition[0] = BossTwoPosition[0]+BOSS_TWO_MOVEMENT_SPEED;
                        BossTwoMovePosition[1] = BossTwoPosition[1];
                        
                        break;
                    case 3:
                        BossTwoMovePosition[0] = BossTwoPosition[0];
                        BossTwoMovePosition[1] = BossTwoPosition[1]+BOSS_TWO_MOVEMENT_SPEED;
                        
                        
                        break;
                    case 4:
                        BossTwoMovePosition[0] = BossTwoPosition[0]-BOSS_TWO_MOVEMENT_SPEED;
                        BossTwoMovePosition[1] = BossTwoPosition[1];
                        
                        
                        break;
                    case 5:
                        BossTwoMovePosition[0] = BossTwoPosition[0] + BOSS_TWO_MOVEMENT_SPEED/sqrt(2);
                        BossTwoMovePosition[1] = BossTwoPosition[1]-BOSS_TWO_MOVEMENT_SPEED/sqrt(2);
                        
                        break;
                    case 6:
                        BossTwoMovePosition[0] = BossTwoPosition[0] + BOSS_TWO_MOVEMENT_SPEED/sqrt(2);
                        BossTwoMovePosition[1] = BossTwoPosition[1]+BOSS_TWO_MOVEMENT_SPEED/sqrt(2);
                        
                        break;
                    case 7:
                        BossTwoMovePosition[0] = BossTwoPosition[0] -BOSS_TWO_MOVEMENT_SPEED/sqrt(2);
                        BossTwoMovePosition[1] = BossTwoPosition[1]+BOSS_TWO_MOVEMENT_SPEED/sqrt(2);
                        break;
                    case 8:
                        BossTwoMovePosition[0] = BossTwoPosition[0] - BOSS_TWO_MOVEMENT_SPEED/sqrt(2);
                        BossTwoMovePosition[1] = BossTwoPosition[1]-BOSS_TWO_MOVEMENT_SPEED/sqrt(2);
                        break;
                        
                }
                distance = getDistance(BossTwoMovePosition, targetPosition);
                
                
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
     method for beam attack of BossTwo
     */
    void BossTwo::shootBeam() {
        if (_clock.getElapsedTime().asSeconds() > 1) {
        sf::Vector2f directionVector;
        float theta = 0;
        for (int i = 0; i < 12; i++) {
            Bullet *b1 = new Bullet(BOSS_TWO_BEAM_RADIUS, sf::Color(255,0,255, 240));
            b1->shape.setOrigin(BOSS_TWO_BEAM_RADIUS, BOSS_TWO_BEAM_RADIUS);
            b1->shape.setPosition(this->getPosition()[0],this->getPosition()[1]);
            directionVector.x = cos(theta);
            directionVector.y = sin(theta);
            
            
            b1->currVelocity = (float)BOSS_TWO_BEAM_SPEED_MULTIPLIER * directionVector * b1->maxSpeed;
            
            bullets.push_back(b1);
            theta += pi/6;
            
            
        }
        }
        
        
        
    }
    std::vector<Bullet*>* BossTwo::getBulletVector() {
        return &this->bullets;
    }
    
}
