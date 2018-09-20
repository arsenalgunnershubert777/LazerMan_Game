#include "BossManager.hpp"
#include <iostream>
namespace g35{
    BossManager::BossManager(GameDataRef data):_data(data) { //manages the boss objects, in accordance with each level/round
        _currGameLevel =  0;
        movingStates = false;
        boss = new BossOne(_data);
        
    }
    void BossManager::Draw(){
        boss->Draw();
    }
    void BossManager::Update(float dt, float * mainCharacterPosition, sf::FloatRect mainCharacterRect){
       
        if (!movingStates) { //if boss is not dead yet (checked by GameState)
            boss->Update(dt, mainCharacterPosition, mainCharacterRect);
        }
        else { //otherwise
            delete boss;
            _currGameLevel +=1;
            Init();
            movingStates = false;
            
        }
        
    }
    
    void BossManager::Init() {
        switch (_currGameLevel) { //init new bosses
            case 1:
                boss = new BossTwo(_data);
                break;
            case 2:
                boss = new BossThree(_data);
                break;
            case 3:
                boss = new BossFour(_data);
                break;
            
        }
    }
    int BossManager::getCurrentGameLevel() {
        return _currGameLevel;
    }
    void BossManager::setMovingStates(bool movingStates) {
        this->movingStates = movingStates;
    }
    
}
