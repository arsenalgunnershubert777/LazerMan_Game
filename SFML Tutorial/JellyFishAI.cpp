#include "JellyFishAI.hpp"
#include <set>
#include <cmath>
#include <iostream>
#include <time.h>
#include <stdlib.h>



namespace g35{
    JellyFishAI::JellyFishAI() { //class which controls and processes minion behavior
        
    }
    JellyFishAI::JellyFishAI(GameDataRef data):_data(data)
    {
        
        _currGameLevel = 0;
        std::vector<int> _gameLevelOne; //these blocks of codes are just hard coding the number of minions and their types
        _gameLevelOne.push_back(1); //this is the number of minions that fly randomly for level 1
        _gameLevelOne.push_back(1); //this is the number of minions that target player for level 1
        _gameLevelOne.push_back(2); //this is the number of minions that spawn automatically for level 1
        _gameLevelOne.push_back(0); //this is 1 if minions regenerate
        _gameLevelOne.push_back(0); //this is 1 if targeting minions regenerate
        
        _gameLevelStates.push_back(_gameLevelOne);
        std::vector<int> _gameLevelTwo;//this is all the same for level 2 and beyond
        _gameLevelTwo.push_back(2);
        _gameLevelTwo.push_back(2);
        _gameLevelTwo.push_back(4);
        _gameLevelTwo.push_back(1);
        _gameLevelTwo.push_back(0);
        _gameLevelStates.push_back(_gameLevelTwo);
        
        std::vector<int> _gameLevelThree;
        _gameLevelThree.push_back(5);
        _gameLevelThree.push_back(3);
        _gameLevelThree.push_back(4);
        _gameLevelThree.push_back(1);
        _gameLevelThree.push_back(1);
        _gameLevelStates.push_back(_gameLevelThree);
        
        std::vector<int> _gameLevelFour;
        _gameLevelFour.push_back(12);
        _gameLevelFour.push_back(4);
        _gameLevelFour.push_back(8);
        _gameLevelFour.push_back(1);
        _gameLevelFour.push_back(1);
        _gameLevelStates.push_back(_gameLevelFour);
        
        
        
        
        //initalize stage one
        int currNumJellies = _gameLevelStates.at(_currGameLevel).at(0) + _gameLevelStates.at(_currGameLevel).at(1); //initializes first level of minions
        int numTargetedJellies = _gameLevelStates.at(_currGameLevel).at(1);
        int numUntargetedJellies = _gameLevelStates.at(_currGameLevel).at(0);
        int numInstantJellies = _gameLevelStates.at(_currGameLevel).at(2);
        
        
        if (numInstantJellies < numUntargetedJellies + numTargetedJellies) {
            numUntargetedJellies = numInstantJellies - numTargetedJellies;
        }
        
        Init(numTargetedJellies,numTargetedJellies);
        justInit = true;
        _numJellies = jellyfishvector.size() + jellyFishUntargetedVector.size();
        movingStates = false;
        
    }
    void JellyFishAI::Draw() {
        for (int i = 0; i < jellyfishvector.size();i++) {
            
            
            jellyfishvector.at(i)->Draw();
            
        }
        for (int i = 0; i <jellyFishUntargetedVector.size();i++) {
            jellyFishUntargetedVector.at(i)->Draw();
        }
        
    }
    void JellyFishAI::Update(float dt, sf::FloatRect spongebobrect) {
        std::srand(time(NULL));
        justInit = false;
        
        if (movingStates == true) {
            
            
            _currGameLevel+=1;
            int numJelliesThisLevel = _gameLevelStates.at(_currGameLevel).at(0) + _gameLevelStates.at(_currGameLevel).at(1);
            int numTargetedJellies = _gameLevelStates.at(_currGameLevel).at(1);
            int numUntargetedJellies = _gameLevelStates.at(_currGameLevel).at(0);
            int numInstantJellies = _gameLevelStates.at(_currGameLevel).at(2);
            
            if (numInstantJellies < numUntargetedJellies + numTargetedJellies) {
                numUntargetedJellies = numInstantJellies- numTargetedJellies;
                
            }
            Init(numTargetedJellies,numTargetedJellies);
            
            
        
            justInit = true;
            movingStates = false;
        }
        
        _numJellies = jellyfishvector.size() + jellyFishUntargetedVector.size();
    
        ProcessUntargetedJellies(); //untargeted Minions always move towards a random location, need to be updated
        
        bool targetedJellyFishDied = ProcessJellyFishDeaths();
        bool newTargetedJelly = ProcessJellyRevival();
        
        if (justInit || targetedJellyFishDied || newTargetedJelly) {
            ProcessTargetedJellies(true, spongebobrect);
            
        }
        else {
            ProcessTargetedJellies(false,spongebobrect); //targeted Minions always move towards a certain spot on the main player, do not need to be updated unless they die or more are born to help
        }
        
        
    }
    
        
    std::vector<sf::FloatRect> JellyFishAI::getRectVector(){
        
        std::vector<sf::FloatRect> rectVector;
        for (int i = 0; i < jellyfishvector.size();i++) {
            rectVector.push_back(jellyfishvector.at(i)->GetSprite().getGlobalBounds());
            
            
        }
        return rectVector;
    }
    
    void JellyFishAI::Init(int numTargeted, int numUntargeted) { //initializes vectors
        jellyfishvector.clear(); //this is for targeted minions
        jellyFishUntargetedVector.clear(); //this is for untargeted/random minions
        srand(time(NULL));
        std::vector<JellyFish *> * jellyvector;
        int sizeToAdd;
        bool isTargeted;
        for (int j = 0; j < 2; j++) {
            if (j ==0){
                jellyvector =&jellyfishvector;
                sizeToAdd = numTargeted;
                isTargeted = true;
            }
            else if (j == 1) {
                jellyvector = &jellyFishUntargetedVector;
                sizeToAdd = numUntargeted;
                isTargeted = false;
            }
            for (int i = 0; i < sizeToAdd; i++) {
                jellyvector->push_back(new JellyFish(_data));
                float x = (float)(rand()%(int)(SCREEN_WIDTH-(jellyvector->at(i)->GetSprite().getGlobalBounds().width*2+1)) + jellyvector->at(i)->GetSprite().getGlobalBounds().width);
                float y = (float)(rand()%(int)(SCREEN_HEIGHT-(jellyvector->at(i)->GetSprite().getGlobalBounds().height*2+1)) + jellyvector->at(i)->GetSprite().getGlobalBounds().height);
                jellyvector->at(i)->GetSprite().setPosition( x, y);
                jellyvector->at(i)->setIsTargeted(isTargeted);
                
            }
        }
        
    }
    
    
    bool JellyFishAI::ProcessJellyFishDeaths() { //processes minion deaths and deletes them
        bool targetedJellyDies = false;
        for (int i = 0; i < jellyfishvector.size(); i++) {//targeted Jelly dies
            if (jellyfishvector.at(i)->getHealth() <= 0) {
                
                jellyfishvector.erase(jellyfishvector.begin() + i);
                targetedJellyDies = true;
                
            }
            
        }
        
        for (int i = 0; i < jellyFishUntargetedVector.size(); i++) {
            if (jellyFishUntargetedVector.at(i)->getHealth() <= 0) {
                
                jellyFishUntargetedVector.erase(jellyFishUntargetedVector.begin() + i);
            }
            
        }
        return targetedJellyDies;
    }
    
    
    
    bool JellyFishAI::ProcessJellyRevival() { //processes minion regeneration if applicable
        bool isRegeneratingUntargetedJellies = false;
        bool isRegeneratingTargetedJellies = false;
        switch(_gameLevelStates.at(_currGameLevel).at(3) + _gameLevelStates.at(_currGameLevel).at(4)) {
            case 0:
                return false;
                break;
            case 1:
                isRegeneratingUntargetedJellies = true;
                break;
            case 2:
                isRegeneratingTargetedJellies = true;
                
                
        }
        int numMaxJellies = _gameLevelStates.at(_currGameLevel).at(0) + _gameLevelStates.at(_currGameLevel).at(1);
        
        int numTargetedJellies = jellyfishvector.size();
        int numMaxTargetedJellies = _gameLevelStates.at(_currGameLevel).at(1);
        
        if(isRegeneratingTargetedJellies && numTargetedJellies < numMaxTargetedJellies && _clock.getElapsedTime().asSeconds() > 5.0) {
            regenJelly(&jellyfishvector, true);
            
            return true;
        }
        else if (((isRegeneratingUntargetedJellies  && numMaxJellies == numMaxTargetedJellies) || (isRegeneratingTargetedJellies && _numJellies < numMaxJellies)) && _clock.getElapsedTime().asSeconds() > 5.0) {
            regenJelly(&jellyFishUntargetedVector, false);
           
            return false;
            
        }
        return false;
    }
    
    void JellyFishAI::regenJelly(std::vector<JellyFish *>  *jellyvector, bool isTargeted) {
        jellyvector->push_back(new JellyFish(_data));
        float x = (float)(rand()%(int)(SCREEN_WIDTH-(jellyvector->at(0)->GetSprite().getGlobalBounds().width)) + jellyvector->at(0)->GetSprite().getGlobalBounds().width);
        float y = (float)(rand()%(int)(SCREEN_HEIGHT-(jellyvector->at(0)->GetSprite().getGlobalBounds().height*2+1)) + jellyvector->at(0)->GetSprite().getGlobalBounds().height);
        jellyvector->at(jellyvector->size() -1)->GetSprite().setPosition( x, y);
        jellyvector->at(jellyvector->size() -1)->setIsTargeted(isTargeted);
        _clock.restart();
    }
    
    
    
    void JellyFishAI::ProcessUntargetedJellies() { //untargeted minions move randomly
        srand(time(NULL));
        for (int i = 0; i < jellyFishUntargetedVector.size(); i++) {
            
            std::set<int> impossibleMoves;
            impossibleMoves = getImpossibleMoves(jellyFishUntargetedVector.at(i));
        
            float * targetSpecific = new float[2];
            float x = rand()%10000 - 5000 + (int)SCREEN_WIDTH*0.5;
            float y = rand()%10000 - 5000 + (int)SCREEN_HEIGHT*0.5;
            targetSpecific[0] = x;
            targetSpecific[1] = y;
            
            int direction = findMoveToTarget(jellyFishUntargetedVector.at(i)->getPosition(), targetSpecific, impossibleMoves);
            jellyFishUntargetedVector.at(i)->Move(direction);
            
            
            
                
            
            
            
            
        }
    }
    void JellyFishAI::ProcessTargetedJellies(bool changeTargets, sf::FloatRect spongebobrect) { //targeted minions each target a piece of the border of the main player sprite, spread out evenly
        
        if (changeTargets) {
            float targetDistance = (spongebobrect.height + spongebobrect.width)*2;
            float interval = targetDistance/jellyfishvector.size();
            float tracker = 0;
            for (int i = 0; i < jellyfishvector.size(); i++) {
                if (tracker > targetDistance) {
                    tracker = targetDistance;
                }
                else {
                    jellyfishvector.at(i)->setTarget(tracker);
                    tracker += interval;
                }
            }
        }
        
        for (int i = 0; i < jellyfishvector.size(); i++) {
            
                
                
                
            std::set<int> impossibleMoves;
            impossibleMoves = getImpossibleMoves(jellyfishvector.at(i));
            
        
            float* targetGeneral = new float[2];
            targetGeneral[0] = spongebobrect.left + spongebobrect.width/2;
            targetGeneral[1] = spongebobrect.top + spongebobrect.height/2;
            float totaldistance = sqrt(abs(pow(jellyfishvector.at(i)->getPosition()[0]- targetGeneral[0],2) + pow(jellyfishvector.at(i)->getPosition()[1]-targetGeneral[1],2)));
            
            float* targetSpecific = new float[2];
            
            
            
            if (jellyfishvector.at(i)->getTarget() < spongebobrect.width) { //two options, if the minion is far away, it should try to surround from afar and not get too close
                //if the minion is close enough, it can go right towards target
                if (totaldistance <= 120 + (spongebobrect.height+jellyfishvector.at(i)->GetSprite().getGlobalBounds().height)*0.5 + (sqrt(2)*spongebobrect.height*0.5 - spongebobrect.height*0.5) + 1) {
                    targetSpecific[0] = spongebobrect.left + jellyfishvector.at(i)->getTarget();
                    targetSpecific[1] = spongebobrect.top;
                }
                else {
                    targetSpecific[0] = spongebobrect.left + jellyfishvector.at(i)->getTarget();
                    targetSpecific[1] = spongebobrect.top - (120 + jellyfishvector.at(i)->GetSprite().getGlobalBounds().height*0.5);
                }
                
            }
            else if (jellyfishvector.at(i)->getTarget() < spongebobrect.width + spongebobrect.height)
            {
                if (totaldistance <= 120 + (spongebobrect.width+jellyfishvector.at(i)->GetSprite().getGlobalBounds().width)*0.5 + (sqrt(2)*spongebobrect.width*0.5 - spongebobrect.width*0.5) + 1) {
                    targetSpecific[0] = spongebobrect.left + spongebobrect.width;
                    targetSpecific[1] = spongebobrect.top + (jellyfishvector.at(i)->getTarget() - spongebobrect.width);
                }
                else {
                    targetSpecific[0] = spongebobrect.left + spongebobrect.width + (120 + jellyfishvector.at(i)->GetSprite().getGlobalBounds().width*0.5);
                    targetSpecific[1] = spongebobrect.top + (jellyfishvector.at(i)->getTarget() - spongebobrect.width);
                }
                
                
            }
            else if (jellyfishvector.at(i)->getTarget() < spongebobrect.width*2 + spongebobrect.height) {
                
                if (totaldistance <= 120 + (spongebobrect.height+jellyfishvector.at(i)->GetSprite().getGlobalBounds().height)*0.5 + (sqrt(2)*spongebobrect.height*0.5 - spongebobrect.height*0.5) + 1) {
                    targetSpecific[0] = spongebobrect.left + spongebobrect.width - (jellyfishvector.at(i)->getTarget() - (spongebobrect.width + spongebobrect.height));
                    targetSpecific[1] = spongebobrect.top + spongebobrect.height;
                }
                else {
                    targetSpecific[0] = spongebobrect.left + spongebobrect.width - (jellyfishvector.at(i)->getTarget() - (spongebobrect.width + spongebobrect.height));
                    targetSpecific[1] = spongebobrect.top + spongebobrect.height + (120 + jellyfishvector.at(i)->GetSprite().getGlobalBounds().height*0.5);
                }
            }
            else {
                if (totaldistance <= 120 + (spongebobrect.width+jellyfishvector.at(i)->GetSprite().getGlobalBounds().width)*0.5 + (sqrt(2)*spongebobrect.width*0.5 - spongebobrect.width*0.5) + 1) {
                    targetSpecific[0] = spongebobrect.left;
                    targetSpecific[1] = spongebobrect.top  + spongebobrect.height - (jellyfishvector.at(i)->getTarget() - (spongebobrect.width*2 + spongebobrect.height));
                }
                else {
                    targetSpecific[0] = spongebobrect.left - (120 + jellyfishvector.at(i)->GetSprite().getGlobalBounds().width*0.5);
                    targetSpecific[1] = spongebobrect.top  + spongebobrect.height - (jellyfishvector.at(i)->getTarget() - (spongebobrect.width*2 + spongebobrect.height));
                }
            }
            
            
            
            
            
            int direction = findMoveToTarget(jellyfishvector.at(i)->getPosition(), targetSpecific, impossibleMoves);
            jellyfishvector.at(i)->Move(direction);
            
            
        }
            
        
        
        
    }
    float JellyFishAI::getDistance(float *jellyMovePosition, float *targetPosition) { //distance formula
        float distance = sqrt(abs(pow(jellyMovePosition[0]- targetPosition[0],2) + pow(jellyMovePosition[1]-targetPosition[1],2)));
        return distance;
    }
    int JellyFishAI::findMoveToTarget(float * jellyPosition, float * targetPosition, std::set<int> impossibleMoves) {
        int direction = 0;//method finds shortest distances and best routes
        float distance = 0;
        float minDist = -1;
        float * jellyMovePosition = new float[2];
        for (int j = 0; j <= 4; j++) {
            if (std::find(impossibleMoves.begin(), impossibleMoves.end(), j) == impossibleMoves.end()) {
                switch (j) {
                    case 0:
                        distance = getDistance(jellyPosition,targetPosition);
                        break;
                    case 1:
                        jellyMovePosition[0] = jellyPosition[0];
                        jellyMovePosition[1] = jellyPosition[1]-MINION_MOVEMENT_SPEED;
                        distance = getDistance(jellyMovePosition, targetPosition);
                      
                        break;
                    case 2:
                        jellyMovePosition[0] = jellyPosition[0]+MINION_MOVEMENT_SPEED;
                        jellyMovePosition[1] = jellyPosition[1];
                        distance = getDistance(jellyMovePosition, targetPosition);
                        break;
                    case 3:
                        jellyMovePosition[0] = jellyPosition[0];
                        jellyMovePosition[1] = jellyPosition[1]+MINION_MOVEMENT_SPEED;
                        distance = getDistance(jellyMovePosition, targetPosition);
                        
                        break;
                    case 4:
                        jellyMovePosition[0] = jellyPosition[0]-MINION_MOVEMENT_SPEED;
                        jellyMovePosition[1] = jellyPosition[1];
                        distance = getDistance(jellyMovePosition, targetPosition);
                        
                        break;
                        
                }
                
                
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
    
    std::vector<JellyFish*>* JellyFishAI::getJellyfishvector() {
        return &this->jellyfishvector;
        
    }
    std::vector<JellyFish*>* JellyFishAI::getJellyFishUntargetedVector(){
        return &this->jellyFishUntargetedVector;
    }
    
    std::set<int> JellyFishAI::getImpossibleMoves(JellyFish * jellyfish) { //will get Impossible moves (off screen)
        std::set<int> impossibleMoves;
        
        for (int j = 1; j <= 4; j++) {
            
            switch (j) {
                case 1:
                    
                    
                    
                    if (jellyfish->GetSprite().getPosition().y  - MINION_MOVEMENT_SPEED< 0) {
                        impossibleMoves.insert(j);
                    }
                    
                    break;
                case 2:
                    
                    if (jellyfish->GetSprite().getPosition().x + jellyfish->GetSprite().getGlobalBounds().width  + MINION_MOVEMENT_SPEED> SCREEN_WIDTH) {
                        impossibleMoves.insert(j);
                    }
                    
                    break;
                case 3:
                    
                    
                    if (jellyfish->GetSprite().getPosition().y + jellyfish->GetSprite().getGlobalBounds().height +MINION_MOVEMENT_SPEED> SCREEN_HEIGHT)
                    {
                        impossibleMoves.insert(j);
                    }
                    
                    break;
                case 4:
                    
                    
                    if (jellyfish->GetSprite().getPosition().x - MINION_MOVEMENT_SPEED< 0) {
                        impossibleMoves.insert(j);
                    }
                    
                    break;
            }
            
            
        }
        return impossibleMoves;
    }
    void JellyFishAI::setMovingStates(bool movingStates){
        this->movingStates = movingStates;
    }
    
    
    
    
    
}

