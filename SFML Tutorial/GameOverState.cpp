#include "GameOverState.hpp"
#include <sstream>
#include "DEFINITIONS.hpp"
#include <iostream>
#include "MainMenuState.hpp"

namespace g35
{
    GameOverState::GameOverState(GameDataRef data) : _data(data) //game over state
    {
        
    }
    void GameOverState::Init()
    {
        
        _data->assets.LoadTexture("Game Over Background", GAME_OVER_BACKGROUND_FILEPATH);
        _background.setTexture(this->_data->assets.GetTexture("Game Over Background"));
        _background.scale(2.25,2);
        
    }
    void GameOverState::HandleInput(){
        sf::Event event;
        while (_data->window.pollEvent(event)) {
            if (sf::Event::Closed == event.type) {
                _data->window.close();
            }
        }
    }
    void GameOverState::Update(float dt)
    {
        if (_clock.getElapsedTime().asSeconds()>GAME_OVER_STATE_SHOW_TIME)
        {
            _data->machine.RemoveState();
        }
    }
    void GameOverState::Draw(float dt) {
        _data->window.clear();
        _data->window.draw(_background);
        _data->window.display();
    }
    
    
}
