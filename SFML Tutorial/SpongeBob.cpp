#include "SpongeBob.hpp"
#include <iostream>
#include <array>
#include <cmath>

namespace g35 {
    SpongeBob::SpongeBob(GameDataRef data):_data(data) //class for the main player object,  which isn't really spongebob
    {
        
        _SpongeBobSprite.setTexture(_data->assets.GetTexture("MainCharacter"));
        _SpongeBobSprite.setPosition(SCREEN_WIDTH/4-_SpongeBobSprite.getGlobalBounds().width/2,SCREEN_HEIGHT/2 - _SpongeBobSprite.getGlobalBounds().height/2);
        _SpongeBobState = 0;
        _direction = 0;
        _health = MAIN_CHARACTER_STARTING_HEALTH;
        _beamHealth = 10000;
        directionVector.x = 1;
        directionVector.y = 0;
        _beamDamage = MAIN_CHARACTER_BEAM_DAMAGE;
        _isFrozen = false;
        
        
        
    }
    
    void SpongeBob::Draw() //draws the player, either in normal or frozen state
    {
        if (!_isFrozen) {
        _data->window.draw(_SpongeBobSprite);
        }
        else {
            _SpongeBobSprite.setTexture(_data->assets.GetTexture("MainCharacterFrozen"));
            _data->window.draw(_SpongeBobSprite);
            
        }
        for (int i = 0; i < bullets.size(); i++) {
            _data->window.draw(bullets[i]->shape);
        }
        
        
    }
    
    void SpongeBob::Update(float dt) //updates movement according to keys pressed, which can be seen further down
    {
       
        
        if (!_isFrozen) {
            _freezeClock.restart();
            switch (_SpongeBobState){
                case 0:
                    _direction = 0;
                    break;
                case 1:
                    if (_SpongeBobSprite.getPosition().y - MAIN_CHARACTER_MOVEMENT_SPEED >= 0 ) {
                        _SpongeBobSprite.move(0,-MAIN_CHARACTER_MOVEMENT_SPEED);
                    
                        
                    }
                    
                    _direction = 1;
                    directionVector.x = 0;
                    directionVector.y = -MAIN_CHARACTER_MOVEMENT_SPEED;
                
                    
                    break;
                case 2:
                    if (_SpongeBobSprite.getPosition().x + _SpongeBobSprite.getGlobalBounds().width + MAIN_CHARACTER_MOVEMENT_SPEED  <= SCREEN_WIDTH) {
                       _SpongeBobSprite.move(MAIN_CHARACTER_MOVEMENT_SPEED,0);
                      
                    
                    }
                   
                    directionVector.x = MAIN_CHARACTER_MOVEMENT_SPEED;
                    directionVector.y = 0;
                    _direction = 2;
                    break;
                case 3:
                    if (_SpongeBobSprite.getPosition().y + _SpongeBobSprite.getGlobalBounds().height  + MAIN_CHARACTER_MOVEMENT_SPEED  <= SCREEN_HEIGHT) {
                        _SpongeBobSprite.move(0,MAIN_CHARACTER_MOVEMENT_SPEED);
                        
                    
                    }
                    directionVector.x = 0;
                    directionVector.y = MAIN_CHARACTER_MOVEMENT_SPEED;
                    _direction = 3;

                    
                    break;
                case 4:
                    if (_SpongeBobSprite.getPosition().x - MAIN_CHARACTER_MOVEMENT_SPEED  >= 0) {
                        _SpongeBobSprite.move(-MAIN_CHARACTER_MOVEMENT_SPEED,0);
                       
                    }
                    directionVector.x = -MAIN_CHARACTER_MOVEMENT_SPEED;
                    directionVector.y = 0;
                    _direction = 4;
                    
                    break;
                case 5: //the sqrt(2) is used to preserve the same distance traveled, whether at 90 degrees or 45
                    if (_SpongeBobSprite.getPosition().y - (MAIN_CHARACTER_MOVEMENT_SPEED/sqrt(2))  >= 0  && _SpongeBobSprite.getPosition().x + _SpongeBobSprite.getGlobalBounds().width + (MAIN_CHARACTER_MOVEMENT_SPEED/sqrt(2))  <= SCREEN_WIDTH) {
                        _SpongeBobSprite.move((MAIN_CHARACTER_MOVEMENT_SPEED/sqrt(2)),(MAIN_CHARACTER_MOVEMENT_SPEED/-sqrt(2)));
                        
                        
                    }
                    directionVector.x = MAIN_CHARACTER_MOVEMENT_SPEED/sqrt(2);
                    directionVector.y = MAIN_CHARACTER_MOVEMENT_SPEED/-sqrt(2);
                    _direction = 5;
                    break;
                case 6:
                    if (_SpongeBobSprite.getPosition().y + _SpongeBobSprite.getGlobalBounds().height  + (MAIN_CHARACTER_MOVEMENT_SPEED/sqrt(2))  <= SCREEN_HEIGHT  && _SpongeBobSprite.getPosition().x + _SpongeBobSprite.getGlobalBounds().width + (MAIN_CHARACTER_MOVEMENT_SPEED/sqrt(2))  <= SCREEN_WIDTH) {
                        _SpongeBobSprite.move((MAIN_CHARACTER_MOVEMENT_SPEED/sqrt(2)),(MAIN_CHARACTER_MOVEMENT_SPEED/sqrt(2)));
                        
                        
                        
                    }
                    directionVector.x = MAIN_CHARACTER_MOVEMENT_SPEED/sqrt(2);
                    directionVector.y = MAIN_CHARACTER_MOVEMENT_SPEED/sqrt(2);
                    _direction = 6;
                    break;
                case 7:
                    if (_SpongeBobSprite.getPosition().y + _SpongeBobSprite.getGlobalBounds().height  + (MAIN_CHARACTER_MOVEMENT_SPEED/sqrt(2))  <= SCREEN_HEIGHT  && _SpongeBobSprite.getPosition().x - (MAIN_CHARACTER_MOVEMENT_SPEED/sqrt(2))  >= 0) {
                        _SpongeBobSprite.move((MAIN_CHARACTER_MOVEMENT_SPEED/-sqrt(2)),(MAIN_CHARACTER_MOVEMENT_SPEED/sqrt(2)));
                        
                        
                    }
                    directionVector.x = MAIN_CHARACTER_MOVEMENT_SPEED/-sqrt(2);
                    directionVector.y = MAIN_CHARACTER_MOVEMENT_SPEED/sqrt(2);
                    _direction = 7;
                    break;
                case 8:
                    if (_SpongeBobSprite.getPosition().y - (MAIN_CHARACTER_MOVEMENT_SPEED/sqrt(2))  >= 0  && _SpongeBobSprite.getPosition().x - (MAIN_CHARACTER_MOVEMENT_SPEED/sqrt(2))  >= 0) {
                        _SpongeBobSprite.move((MAIN_CHARACTER_MOVEMENT_SPEED/-sqrt(2)),(MAIN_CHARACTER_MOVEMENT_SPEED/-sqrt(2)));
                        
                        
                    }
                    directionVector.x = (MAIN_CHARACTER_MOVEMENT_SPEED/-sqrt(2));
                    directionVector.y = (MAIN_CHARACTER_MOVEMENT_SPEED/-sqrt(2));
                    _direction = 8;
                    break;
                    
            }
            if (_movementClock.getElapsedTime().asSeconds() > SPONGEBOB_MOVEMENT_DURATION)
            {
                _movementClock.restart();
                _SpongeBobState = SPONGEBOB_STATE_STILL;
                
            }
            
            if (this->_health > 0) { //health regenerates slowly
                if (this->_health < MAIN_CHARACTER_STARTING_HEALTH) {
                    this->_health += MAIN_CHARACTER_REGENERATION_HEALTH;
                }
                else {
                    this->_health = MAIN_CHARACTER_STARTING_HEALTH;
                }
            }
            else {
                this->_health = 0;
            }
            
            if (this->_beamHealth > MAIN_CHARACTER_BEAM_STARTING_HEALTH) { //beam ammo regenerates as well
                this->_beamHealth =  MAIN_CHARACTER_BEAM_STARTING_HEALTH;
            }
            else {
                this->_beamHealth += MAIN_CHARACTER_REGENERATION_BEAM_HEALTH;
            }
            
            
        }
        else { //if player is frozen, it will break free after 5 seconds
            if (_freezeClock.getElapsedTime().asSeconds()>5) {
                _isFrozen = false;
                _SpongeBobSprite.setTexture(_data->assets.GetTexture("MainCharacter"));
            }
        }
        for (int i = 0; i < bullets.size();i++) { //moves the beam bullets if there are any
            bullets[i]->shape.move(bullets[i]->currVelocity);
            if (bullets[i]->shape.getPosition().x < 0 || bullets[i]->shape.getPosition().x > SCREEN_WIDTH || bullets[i]->shape.getPosition().y < 0 || bullets[i]->shape.getPosition().y > SCREEN_HEIGHT) {
                bullets.erase(bullets.begin() + i);
                
                
            }
            
        }
        
        
    }
    void SpongeBob::MoveUp() //move methods called by GameState class, which handles input from keyboard
    {
        _movementClock.restart();
        _SpongeBobState = SPONGEBOB_STATE_N;
       
    }
    void SpongeBob::MoveRight()
    {
       
        _movementClock.restart();
        _SpongeBobState = SPONGEBOB_STATE_E;
      
    }
    
    void SpongeBob::MoveDown()
    {
        _movementClock.restart();
        _SpongeBobState = SPONGEBOB_STATE_S;
        
    }
    
    void SpongeBob::MoveLeft()
    {
        _movementClock.restart();
        _SpongeBobState = SPONGEBOB_STATE_W;
        
    }
    void SpongeBob::MoveStill(){
        _movementClock.restart();
        _SpongeBobState = SPONGEBOB_STATE_STILL;
    }
    void SpongeBob::MoveUpRight() {
        _movementClock.restart();
        _SpongeBobState = SPONGEBOB_STATE_NE;
        
    }
    void SpongeBob::MoveDownRight(){
        _movementClock.restart();
        _SpongeBobState = SPONGEBOB_STATE_SE;
        
    }
    void SpongeBob::MoveDownLeft(){
        _movementClock.restart();
        _SpongeBobState = SPONGEBOB_STATE_SW;
    }
    void SpongeBob::MoveUpLeft(){
        _movementClock.restart();
        _SpongeBobState = SPONGEBOB_STATE_NW;
    }
    
    void SpongeBob::shootBeam() { //shoots attack beam
        if (this->_beamHealth >= 10 && !_isFrozen) {
            for (int i = 1; i <= 10; i++) {
                Bullet *b1 = new Bullet(MAIN_CHARACTER_BEAM_RADIUS, sf::Color::Red);
                b1->shape.setOrigin(MAIN_CHARACTER_BEAM_RADIUS, MAIN_CHARACTER_BEAM_RADIUS);
                //b1->shape.setPosition(this->getPosition()[0] -MAIN_CHARACTER_BEAM_RADIUS,this->getPosition()[1] -MAIN_CHARACTER_BEAM_RADIUS);
                b1->shape.setPosition(this->getPosition()[0],this->getPosition()[1]);
                float speed = ((float)i/10) * MAIN_CHARACTER_BEAM_SPEED_MULTIPLIER;
                b1->currVelocity = directionVector * b1->maxSpeed * speed;
                
                bullets.push_back(b1);
            }
            this->_beamHealth -=10;
           
        }
        
    }
    
   sf::Sprite &SpongeBob::GetSprite()
    {
        return _SpongeBobSprite;
    }
    
    float* SpongeBob::getPosition() { //returns float array at center of sprite
        float* returnData = new float[2];
        returnData[0] = _SpongeBobSprite.getGlobalBounds().left + (_SpongeBobSprite.getGlobalBounds().width)/2;
        returnData[1] = _SpongeBobSprite.getGlobalBounds().top + (_SpongeBobSprite.getGlobalBounds().height)/2;
        return returnData;
        
    }
    float SpongeBob::getHealth() {
        return this->_health;
    }
    void SpongeBob::setHealth(float health) {
        this->_health = health;
    }
    std::vector<Bullet*>* SpongeBob::getBulletVector(){
        return &this->bullets;
    }
    float SpongeBob::getBeamDamage(){
        return this->_beamDamage;
    }
    void SpongeBob::setBeamDamage(float newBeamDamage) {
        this->_beamDamage = newBeamDamage;
    }
    
    bool SpongeBob::getFreezeState() {
        return _isFrozen;
    }
    void SpongeBob::setFreezeState(bool isFrozen) {
        this->_isFrozen = isFrozen;
    }
    
    
}
