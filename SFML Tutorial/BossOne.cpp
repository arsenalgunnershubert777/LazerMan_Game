#include "BossOne.hpp"
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <set>
#include <time.h>

/**
 
 BossOne.cpp
 Purpose: to be in charge of BossOne Health, attack, position and location
 */
//boss one tries to hit and run on the player
namespace g35 {
    BossOne::~BossOne(){
        
    }
    BossOne::BossOne(GameDataRef data):_data(data),_canFreeze(false)
    {
        
        
        _BossOneSprite.setTexture(_data->assets.GetTexture("BossOne"));
        _BossOneSprite.setPosition(3*SCREEN_WIDTH/4 - _BossOneSprite.getGlobalBounds().width/2,SCREEN_HEIGHT/2 - _BossOneSprite.getGlobalBounds().width/2);
        _isChasing = false;
        _health = BOSS_ONE_STARTING_HEALTH;
    }
    
    
    void BossOne::Draw()
    {
        _data->window.draw(_BossOneSprite);
        
    }
    /**
     In charge of moving BossOne.
     
     @param the directon
     
     */
    void BossOne::Move(int direction) {
        switch (direction) {
            case 0:
                break;
            case 1:
                this->_BossOneSprite.move(0,-BOSS_ONE_MOVEMENT_SPEED);
                break;
            case 2:
                this->_BossOneSprite.move(BOSS_ONE_MOVEMENT_SPEED,0);
                break;
            case 3:
                this->_BossOneSprite.move(0,BOSS_ONE_MOVEMENT_SPEED);
                break;
            case 4:
                this->_BossOneSprite.move(-BOSS_ONE_MOVEMENT_SPEED,0);
                break;
            case 5:
                this->_BossOneSprite.move(BOSS_ONE_MOVEMENT_SPEED/sqrt(2),-BOSS_ONE_MOVEMENT_SPEED/sqrt(2));
                break;
            case 6:
                this->_BossOneSprite.move(BOSS_ONE_MOVEMENT_SPEED/sqrt(2),BOSS_ONE_MOVEMENT_SPEED/sqrt(2));
                break;
            case 7:
                this->_BossOneSprite.move(-BOSS_ONE_MOVEMENT_SPEED/sqrt(2),BOSS_ONE_MOVEMENT_SPEED/sqrt(2));
                break;
            case 8:
                this->_BossOneSprite.move(-BOSS_ONE_MOVEMENT_SPEED/sqrt(2),-BOSS_ONE_MOVEMENT_SPEED/sqrt(2));
                break;
        }
    }
    /**
     Returns the Sprite of BossOne
     
     @return BossOneSprite.
     */
    
    sf::Sprite &BossOne::GetSprite()
    {
        return _BossOneSprite;
    }
    /**
     Returns the position of BossOne
     
     
     @return The position in array form .
     */
    
    float* BossOne::getPosition() {
        float* returnData = new float[2];
        returnData[0] = _BossOneSprite.getGlobalBounds().left + (_BossOneSprite.getGlobalBounds().width)/2;
        returnData[1] = _BossOneSprite.getGlobalBounds().top + (_BossOneSprite.getGlobalBounds().height)/2;
        return returnData;
        
    }
    /**
     Returns the health specified for BossOne.
     
     @return health.
     */
    float BossOne::getHealth() {
        return this->_health;
    }
    /**
     sets the health of BossOne to the specified health
     
     @param the specified Health.
     
     */
    void BossOne::setHealth(float health) {
        this->_health = health;
    }
    
    /**
     Updated the state of BossOne and check for impossible moves
     
     @param float dt, and the main character position
     */
    void BossOne::Update(float dt, float * mainCharacterPosition, sf::FloatRect mainCharacterRect) {
        if (getHealth() > 0) {
            if (_isChasing) {
                if (!this->GetSprite().getGlobalBounds().intersects(mainCharacterRect)) {
                    //move towards spongebob and avoid being along diagonols
                    float * target = new float[2];
                    target[0] = mainCharacterPosition[0];
                    target[1] = mainCharacterPosition[1];
                    
                    //check for impossible moves
                    std::set<int> impossibleMoves = getImpossibleMoves();
                    //check if BossOne is in line with SpongeBob at any level
                    float distanceToTarget = getDistance(this->getPosition(), mainCharacterPosition);
                    if (distanceToTarget > 200) {
                        if (abs(mainCharacterPosition[0] - this->getPosition()[0]) < GetSprite().getGlobalBounds().height/2 + MAIN_CHARACTER_BEAM_RADIUS) {
                            impossibleMoves.insert(0);
                            impossibleMoves.insert(1);
                            impossibleMoves.insert(3);
                            if (mainCharacterPosition[0] > this->getPosition()[0]) {
                                impossibleMoves.insert(5);
                                impossibleMoves.insert(6);
                            }
                            else {
                                impossibleMoves.insert(7);
                                impossibleMoves.insert(8);
                                
                            }
                            
                        }
                        if (abs(mainCharacterPosition[1] - this->getPosition()[1]) < GetSprite().getGlobalBounds().width/2 + MAIN_CHARACTER_BEAM_RADIUS) {
                            impossibleMoves.insert(0);
                            impossibleMoves.insert(2);
                            impossibleMoves.insert(4);
                            if (mainCharacterPosition[1] > this->getPosition()[1]) {
                                impossibleMoves.insert(7);
                                impossibleMoves.insert(6);
                            }
                            else {
                                impossibleMoves.insert(5);
                                impossibleMoves.insert(8);
                                
                            }
                            
                            
                        }
                        
                        if (abs(abs(mainCharacterPosition[0] - this->getPosition()[0]) - abs(mainCharacterPosition[1] - this->getPosition()[1])) < sqrt(2)*(MAIN_CHARACTER_BEAM_RADIUS + _BossOneSprite.getGlobalBounds().height/sqrt(2))) {
                            if ((mainCharacterPosition[0] - this->getPosition()[0])*(mainCharacterPosition[1] - this->getPosition()[1]) > 0) {
                                impossibleMoves.insert(0);
                                impossibleMoves.insert(6);
                                impossibleMoves.insert(8);
                                if (abs(mainCharacterPosition[1]-this->getPosition()[1]) > abs(mainCharacterPosition[0] - this->getPosition()[0])) {
                                    impossibleMoves.insert(1);
                                    impossibleMoves.insert(3);
                                }
                                else {
                                    impossibleMoves.insert(2);
                                    impossibleMoves.insert(4);
                                }
                                
                            }
                            else {
                                impossibleMoves.insert(0);
                                impossibleMoves.insert(5);
                                impossibleMoves.insert(7);
                                if (abs(mainCharacterPosition[1]-this->getPosition()[1]) > abs(mainCharacterPosition[0] - this->getPosition()[0])) {
                                    impossibleMoves.insert(1);
                                    impossibleMoves.insert(4);
                                }
                                else {
                                    impossibleMoves.insert(2);
                                    impossibleMoves.insert(3);
                                }
                                
                            }
                        }
                       
                        
                    }
                    
                    int direction = findMoveToTarget(this->getPosition(), mainCharacterPosition, impossibleMoves);
                    this->Move(direction);
                }
                else {
                    
                    _isChasing = false;
                    _clock.restart();
                }
             
                
            }
            else {
                if (_clock.getElapsedTime().asSeconds() < 5) {
                    std::srand(time(NULL));
                    std::set<int> impossibleMoves = getImpossibleMoves();
                    float * targetPosition = new float [2];
                    bool isFarEnough = false;
                    while (!isFarEnough) {
                        float x = (float)(rand()%(int)(SCREEN_WIDTH-(_BossOneSprite.getGlobalBounds().width*2+1)) + _BossOneSprite.getGlobalBounds().width);
                        float y = (float)(rand()%(int)(SCREEN_HEIGHT-(_BossOneSprite.getGlobalBounds().height*2+1)) + _BossOneSprite.getGlobalBounds().height);
                        targetPosition[0] = x;
                        targetPosition[1] = y;
                        if (getDistance(mainCharacterPosition, targetPosition) > SCREEN_HEIGHT/3) {
                            isFarEnough = true;
                        }
                    }
                    
                    int direction =findMoveToTarget(this->getPosition(), targetPosition, impossibleMoves);
                    
                    
                    this->Move(direction);
                }
                else {
                    _isChasing = true;
                    
                }
                
            }
        }
        else {
            setHealth(0);
        }
    }
    float BossOne::getDistance(float* BossOneMovePosition, float* targetPosition) {
        float distance = sqrt(abs(pow(BossOneMovePosition[0]- targetPosition[0],2) + pow(BossOneMovePosition[1]-targetPosition[1],2)));
        return distance;
    }
    std::set<int> BossOne::getImpossibleMoves() {
        std::set<int> impossibleMoves;
        //check for impossible moves
        for (int j = 0; j <= 8; j++) {
            
            switch (j) {
                case 0:
                    break;
                case 1:
                    if (_BossOneSprite.getPosition().y - BOSS_ONE_MOVEMENT_SPEED < 0 ) {
                        impossibleMoves.insert(j);
                        
                    }
                    
                    
                    break;
                case 2:
                    if (_BossOneSprite.getPosition().x + _BossOneSprite.getGlobalBounds().width + BOSS_ONE_MOVEMENT_SPEED  > SCREEN_WIDTH) {
                        
                        impossibleMoves.insert(j);
                    }
                   
                    
                    break;
                case 3:
                    if (_BossOneSprite.getPosition().y + _BossOneSprite.getGlobalBounds().height  + BOSS_ONE_MOVEMENT_SPEED  > SCREEN_HEIGHT) {
                        
                        impossibleMoves.insert(j);
                        
                    }
                    
                   
                    break;
                case 4:
                    if (_BossOneSprite.getPosition().x - BOSS_ONE_MOVEMENT_SPEED  < 0) {
                        
                        impossibleMoves.insert(j);
                    }
                    
                    
                    break;
                case 5:
                    if (_BossOneSprite.getPosition().y - (BOSS_ONE_MOVEMENT_SPEED/sqrt(2))  < 0  || _BossOneSprite.getPosition().x + _BossOneSprite.getGlobalBounds().width + (BOSS_ONE_MOVEMENT_SPEED/sqrt(2))  > SCREEN_WIDTH) {
                        
                        
                        impossibleMoves.insert(j);
                    }
                    
                    
                    break;
                case 6:
                    if (_BossOneSprite.getPosition().y + _BossOneSprite.getGlobalBounds().height  + (BOSS_ONE_MOVEMENT_SPEED/sqrt(2))  > SCREEN_HEIGHT  || _BossOneSprite.getPosition().x + _BossOneSprite.getGlobalBounds().width + (BOSS_ONE_MOVEMENT_SPEED/sqrt(2))  > SCREEN_WIDTH) {
                        impossibleMoves.insert(j);
                        
                        
                        
                    }
                    
                    
                    break;
                case 7:
                    if (_BossOneSprite.getPosition().y + _BossOneSprite.getGlobalBounds().height  + (BOSS_ONE_MOVEMENT_SPEED/sqrt(2))  > SCREEN_HEIGHT  || _BossOneSprite.getPosition().x - (BOSS_ONE_MOVEMENT_SPEED/sqrt(2))  < 0) {
                        impossibleMoves.insert(j);
                        
                        
                    }
                    
                    
                    
                    break;
                case 8:
                    if (_BossOneSprite.getPosition().y - (BOSS_ONE_MOVEMENT_SPEED/sqrt(2))  < 0  || _BossOneSprite.getPosition().x - (BOSS_ONE_MOVEMENT_SPEED/sqrt(2))  < 0) {
                        impossibleMoves.insert(j);
                        
                        
                    }
                    
                    
                    break;
            }
            
            
            
        }
        return impossibleMoves;
    }
    int BossOne::findMoveToTarget(float * BossOnePosition, float * targetPosition, std::set<int> impossibleMoves) {
        int direction = 0;
        float distance = 0;
        float minDist = -1;
        float * BossOneMovePosition = new float[2];
        for (int j = 1; j <= 8; j++) {
            if (std::find(impossibleMoves.begin(), impossibleMoves.end(), j) == impossibleMoves.end()) {
                switch (j) {
                    case 0:
                        
                        BossOneMovePosition[0] = BossOnePosition[0];
                        BossOneMovePosition[1] = BossOnePosition[1];
                        break;
                    case 1:
                        BossOneMovePosition[0] = BossOnePosition[0];
                        BossOneMovePosition[1] = BossOnePosition[1]-BOSS_ONE_MOVEMENT_SPEED;
                        
                        
                        break;
                    case 2:
                        BossOneMovePosition[0] = BossOnePosition[0]+BOSS_ONE_MOVEMENT_SPEED;
                        BossOneMovePosition[1] = BossOnePosition[1];
                        
                        break;
                    case 3:
                        BossOneMovePosition[0] = BossOnePosition[0];
                        BossOneMovePosition[1] = BossOnePosition[1]+BOSS_ONE_MOVEMENT_SPEED;
                        
                        
                        break;
                    case 4:
                        BossOneMovePosition[0] = BossOnePosition[0]-BOSS_ONE_MOVEMENT_SPEED;
                        BossOneMovePosition[1] = BossOnePosition[1];
                        
                        
                        break;
                    case 5:
                        BossOneMovePosition[0] = BossOnePosition[0] + BOSS_ONE_MOVEMENT_SPEED/sqrt(2);
                        BossOneMovePosition[1] = BossOnePosition[1]-BOSS_ONE_MOVEMENT_SPEED/sqrt(2);
                        
                        break;
                    case 6:
                        BossOneMovePosition[0] = BossOnePosition[0] + BOSS_ONE_MOVEMENT_SPEED/sqrt(2);
                        BossOneMovePosition[1] = BossOnePosition[1]+BOSS_ONE_MOVEMENT_SPEED/sqrt(2);
                        
                        break;
                    case 7:
                        BossOneMovePosition[0] = BossOnePosition[0] -BOSS_ONE_MOVEMENT_SPEED/sqrt(2);
                        BossOneMovePosition[1] = BossOnePosition[1]+BOSS_ONE_MOVEMENT_SPEED/sqrt(2);
                        break;
                    case 8:
                        BossOneMovePosition[0] = BossOnePosition[0] - BOSS_ONE_MOVEMENT_SPEED/sqrt(2);
                        BossOneMovePosition[1] = BossOnePosition[1]-BOSS_ONE_MOVEMENT_SPEED/sqrt(2);
                        break;
                        
                }
                distance = getDistance(BossOneMovePosition, targetPosition);
                
                
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
    
    
}
