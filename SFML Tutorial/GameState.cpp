
#include "GameState.hpp"
#include <sstream>
#include "DEFINITIONS.hpp"
#include <iostream>
#include <string>




namespace g35 //this is the state that runs all four levels of the game
{
    GameState::GameState(GameDataRef data) : _data(data)
    {
        gameLevel = 0;
    }
    
    void GameState::Init()
    {
        
        _data->assets.LoadTexture("Game Background", GAME_BACKGROUND_FILEPATH); //first, many textures are loaded
        _data->assets.LoadTexture("MainCharacter", MAIN_CHARACTER_FILEPATH);
        _data->assets.LoadTexture("MainCharacterFrozen", MAIN_CHARACTER_FROZEN_FILEPATH);
        _data->assets.LoadTexture("Minion", MINION_FILEPATH);
        _data->assets.LoadTexture("BossOne", BOSS_ONE_SPRITE_FILEPATH);
        _data->assets.LoadTexture("BossThree", BOSS_THREE_SPRITE_FILEPATH);
        _data->assets.LoadTexture("BossTwo", BOSS_TWO_SPRITE_FILEPATH);
        _data->assets.LoadTexture("BossFourStage1", BOSS_FOUR_SPRITE_FILEPATH);
        _data->assets.LoadTexture("BossFourStage2", BOSS_FOUR_SPRITE_RAGE_FILEPATH);
        _data->assets.LoadTexture("Round1", ROUND_1);
        _data->assets.LoadTexture("Round2", ROUND_2);
        _data->assets.LoadTexture("Round3", ROUND_3);
        _data->assets.LoadTexture("Round4", ROUND_4);
        _data->assets.LoadTexture("Health1", HEALTH_1);
        _data->assets.LoadTexture("Health2", HEALTH_2);
        _data->assets.LoadTexture("Health3", HEALTH_3);
        _data->assets.LoadTexture("Health4", HEALTH_4);
        _data->assets.LoadTexture("Health5", HEALTH_5);
        _data->assets.LoadTexture("Health6", HEALTH_6);
        _data->assets.LoadTexture("Health7", HEALTH_7);
        _data->assets.LoadTexture("Health8", HEALTH_8);
        _data->assets.LoadTexture("Health9", HEALTH_9);
        _data->assets.LoadTexture("Health10", HEALTH_10);
        _data->assets.LoadTexture("MainCharacterLabel", MAIN_CHARACTER_LABEL);
        _data->assets.LoadTexture("BossLabel", BOSS_LABEL);
        _data->assets.LoadTexture("Exit Button", EXIT_BUTTON_FILEPATH);
        _data->assets.LoadTexture("Pause Button", PAUSE_BUTTON_FILEPATH);
        
        _playButton.setTexture(_data->assets.GetTexture("Play Button"));
        _pauseButton.setTexture(_data->assets.GetTexture("Pause Button"));
        _exitButton.setTexture(_data->assets.GetTexture("Exit Button"));
        
        _playButton.scale(2,2);
        _playButton.setPosition(SCREEN_WIDTH/2 - _playButton.getGlobalBounds().width/2, SCREEN_HEIGHT/2 - _playButton.getGlobalBounds().height/2);

        _pauseButton.setPosition(SCREEN_WIDTH - _pauseButton.getGlobalBounds().width, 0);
        
        _exitButton.scale(1.5,1.5);
        _exitButton.setPosition(SCREEN_WIDTH - _exitButton.getGlobalBounds().width, SCREEN_HEIGHT - _exitButton.getGlobalBounds().height);
        
        
        
        spongebob = new SpongeBob(_data); //main player is instantiated
        jellyfishAI = new JellyFishAI(_data); //minion hoard manager is instantiated
        bossManager = new BossManager(_data); //boss manager is instantiated
        damageInteractions = new DamageInteractions(); //damageprocessing object is instantiated
        gameLevel = 0;
        
        _background.setTexture(this->_data->assets.GetTexture("Game Background"));
        _background.scale(2.1975,2);
        introTextFinished = false;
        isPaused = false;
        intoPauseState = false;
        
    }
    void GameState::HandleInput(){ //handles keyboard movements for player
        sf::Event event;
        while (_data->window.pollEvent(event)) {
            if (sf::Event::Closed == event.type) {
                _data->window.close();
            }
            
        }
        if (isPaused && _data->input.IsSpriteClicked(_playButton,sf::Mouse::Left, _data->window))
        {
            isPaused = false;
            intoPauseState = false;
        }
        
        if (!isPaused && _data->input.IsSpriteClicked(_pauseButton,sf::Mouse::Left, _data->window))
        {
            isPaused = true;
        }
        
        if (isPaused && _data->input.IsSpriteClicked(_exitButton,sf::Mouse::Left, _data->window)) {
            _data->machine.RemoveState();
        }
        
        if (introTextFinished == true && !isPaused) {
            
            
            int numEquilibriumX = 0;
            int numEquilibriumY = 0;
            if (_data->input.IsKeyClicked(sf::Keyboard::Left))
            {
                
                numEquilibriumX = numEquilibriumX - 1;
                
            }
            if (_data->input.IsKeyClicked(sf::Keyboard::Right))
            {
                numEquilibriumX = numEquilibriumX + 1;
                
            }
            if (_data->input.IsKeyClicked(sf::Keyboard::Up))
            {
                numEquilibriumY = numEquilibriumY + 1;
            }
            if (_data->input.IsKeyClicked(sf::Keyboard::Down))
            {
                numEquilibriumY  =numEquilibriumY - 1;
                
            }
            
            if (numEquilibriumX ==0 && numEquilibriumY ==0) {
                spongebob->MoveStill();
            }
            else if (numEquilibriumY == 0) {
                if (numEquilibriumX > 0) {
                    spongebob->MoveRight();
                }
                else {
                    spongebob->MoveLeft();
                }
            }
            else if (numEquilibriumX == 0) {
                if (numEquilibriumY > 0) {
                    spongebob->MoveUp();
                }
                else {
                    spongebob->MoveDown();
                }
            }
            else {
                if (numEquilibriumX > 0) {
                    if (numEquilibriumY > 0) {
                        spongebob->MoveUpRight();
                    }
                    else {
                        spongebob->MoveDownRight();
                    }
                }
                else {
                    if (numEquilibriumY > 0) {
                        spongebob->MoveUpLeft();
                    }
                    else {
                        spongebob->MoveDownLeft();
                    }
                    
                }
                
            }
           
            if (_data->input.IsKeyClicked(sf::Keyboard::B)) {
                spongebob->shootBeam();
            }
        }
        
    }
    void GameState::Update(float dt) //updates the game objects
    {
        if (!isPaused) {
            if (introTextFinished == false) {
                if (_clock.getElapsedTime().asSeconds() > 4) {
                    introTextFinished = true;
                    
                }
            }
            else {
                _clock.restart();
            
            
                if (spongebob->getHealth() <=0) { //if player is dead, game over
                    _data->machine.AddState(StateRef(new GameOverState(_data)), true);
                }
                spongebob->Update(dt); //update player
                jellyfishAI->Update(dt, spongebob->GetSprite().getGlobalBounds()); //update minions
                bossManager->Update(dt, spongebob->getPosition(), spongebob->GetSprite().getGlobalBounds()); //update boss
                damageInteractions->Update(dt, spongebob,jellyfishAI, bossManager); //update health of all
                
                
                if (bossManager->boss->getHealth() <=0) { //if boss dies, move on to next level
                    if (gameLevel < NUM_GAME_LEVELS-1) {
                        gameLevel++;
                        introTextFinished = false;
                        bossManager->setMovingStates(true);
                        jellyfishAI->setMovingStates(true);
                        spongebob->setHealth(MAIN_CHARACTER_STARTING_HEALTH);
                        spongebob->getBulletVector()->clear();
                        spongebob->setFreezeState(false);
                        spongebob->GetSprite().setPosition(SCREEN_WIDTH/4-spongebob->GetSprite().getGlobalBounds().width/2,SCREEN_HEIGHT/2 - spongebob->GetSprite().getGlobalBounds().height/2);
                        bossManager->Update(dt, spongebob->getPosition(), spongebob->GetSprite().getGlobalBounds());
                        jellyfishAI->Update(dt, spongebob->GetSprite().getGlobalBounds());
                        
                    }
                    else {
                        delete spongebob;
                        delete jellyfishAI;
                        delete bossManager;
                        delete damageInteractions;
                        _data->machine.AddState(StateRef(new GameWinState(_data)), true);
                    }
                }
            }
        }
        
        
       
    }
    void GameState::Draw(float dt) { //draws the sprites onto the window
        
        
        
        if (isPaused) {
            if (intoPauseState == false) {
                _data->window.draw(_playButton);
                _data->window.draw(_exitButton);
                _data->window.display();
                intoPauseState = true;
            }
        }
        else {
            _data->window.clear();
            _data->window.draw(_background);
            _data->window.draw(_pauseButton);
            drawHealthBars();
            bossManager->Draw(); //then boss
            spongebob->Draw(); //main player
            jellyfishAI->Draw(); //and then minion
            if (introTextFinished == false) { //drawing sprites for each new round
                drawRoundLabels();
            }
            _data->window.display();
            
        }
        
    
        
        
        
    }
    void GameState::drawHealthBars() {
        float playerHealth = MAIN_CHARACTER_STARTING_HEALTH;
        float currPlayerHealth = spongebob->getHealth();
        
        //calculations needed for health bar
        int healthNum;
        if (currPlayerHealth > playerHealth*8/9) {
            healthNum = 1;
        }
        else if (currPlayerHealth > playerHealth*7/9) {
            healthNum = 2;
        }
        else if (currPlayerHealth > playerHealth*6/9) {
            healthNum = 3;
        }
        else if (currPlayerHealth > playerHealth*5/9) {
            healthNum = 4;
        }
        else if (currPlayerHealth > playerHealth*4/9) {
            healthNum = 5;
        }
        else if (currPlayerHealth > playerHealth*3/9) {
            healthNum = 6;
        }
        else if (currPlayerHealth > playerHealth*2/9) {
            healthNum = 7;
        }
        else if (currPlayerHealth > playerHealth*1/9) {
            healthNum = 8;
        }
        else if (currPlayerHealth > 0) {
            healthNum = 9;
        }
        else {
            healthNum = 10;
        }
        sf::Sprite playerHealthSprite;
        sf::Sprite playerLabelSprite;
        playerLabelSprite.setTexture(_data->assets.GetTexture("MainCharacterLabel"));
        playerLabelSprite.scale(1.5,1.5);
        playerLabelSprite.setPosition(0, 0);
        playerHealthSprite.scale(1.5,1.5);
        playerHealthSprite.setTexture(_data->assets.GetTexture("Health" + std::to_string(healthNum)));
        playerHealthSprite.setPosition(0, playerLabelSprite.getGlobalBounds().height + 1);
        
        float currBossHealth = bossManager->boss->getHealth();
        float bossHealth;
        switch (gameLevel) {
            case 0:
                bossHealth = BOSS_ONE_STARTING_HEALTH;
                break;
            case 1:
                bossHealth = BOSS_TWO_STARTING_HEALTH;
                break;
            case 2:
                bossHealth = BOSS_THREE_STARTING_HEALTH;
                break;
            case 3:
                bossHealth = BOSS_FOUR_STARTING_HEALTH;
                break;
                
        }
        if (currBossHealth > bossHealth*8/9) {
            healthNum = 1;
        }
        else if (currBossHealth > bossHealth*7/9) {
            healthNum = 2;
        }
        else if (currBossHealth > bossHealth*6/9) {
            healthNum = 3;
        }
        else if (currBossHealth > bossHealth*5/9) {
            healthNum = 4;
        }
        else if (currBossHealth > bossHealth*4/9) {
            healthNum = 5;
        }
        else if (currBossHealth > bossHealth*3/9) {
            healthNum = 6;
        }
        else if (currBossHealth > bossHealth*2/9) {
            healthNum = 7;
        }
        else if (currBossHealth > bossHealth*1/9) {
            healthNum = 8;
        }
        else if (currBossHealth > 0) {
            healthNum = 9;
        }
        else {
            healthNum = 10;
        }
        sf::Sprite bossHealthSprite;
        sf::Sprite bossLabelSprite;
        bossLabelSprite.setTexture(_data->assets.GetTexture("BossLabel"));
        bossLabelSprite.scale(1.5,1.5);
        bossLabelSprite.setPosition(0, SCREEN_HEIGHT - bossLabelSprite.getGlobalBounds().height);
        bossHealthSprite.setTexture(_data->assets.GetTexture("Health" + std::to_string(healthNum)));
        bossHealthSprite.scale(1.5,1.5);
        bossHealthSprite.setPosition(0, SCREEN_HEIGHT - bossLabelSprite.getGlobalBounds().height - bossHealthSprite.getGlobalBounds().height -1);
        _data->window.draw(playerLabelSprite);
        _data->window.draw(playerHealthSprite);
        _data->window.draw(bossLabelSprite);
        _data->window.draw(bossHealthSprite);
    }
    
    
    void GameState::drawRoundLabels() {
        sf::Sprite round;
        switch (gameLevel) {
            case 0:
                round.setTexture(_data->assets.GetTexture("Round1"));
                break;
            case 1:
                round.setTexture(_data->assets.GetTexture("Round2"));
                break;
            case 2:
                round.setTexture(_data->assets.GetTexture("Round3"));
                break;
            case 3:
                round.setTexture(_data->assets.GetTexture("Round4"));
                break;
        }
        round.setPosition(SCREEN_WIDTH/2-round.getGlobalBounds().width*1.5, SCREEN_HEIGHT/2 - round.getGlobalBounds().height);
        round.scale(3,3);
        _data->window.draw(round);
    }
    
    
}
