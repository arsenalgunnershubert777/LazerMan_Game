
#include "GameWinState.hpp"
#include <sstream>
#include "DEFINITIONS.hpp"
#include <iostream>
#include "MainMenuState.hpp"

namespace g35 //processes screen after you beat final boss
{
    GameWinState::GameWinState(GameDataRef data) : _data(data)
    {
        
    }
    void GameWinState::Init()
    {
        
        _data->assets.LoadTexture("Game Win Background", GAME_WIN_BACKGROUND_FILEPATH);
        _background.setTexture(this->_data->assets.GetTexture("Game Win Background"));
        _background.scale(2.22,2);
        
    }
    void GameWinState::HandleInput(){
        sf::Event event;
        while (_data->window.pollEvent(event)) {
            if (sf::Event::Closed == event.type) {
                _data->window.close();
            }
        }
    }
    void GameWinState::Update(float dt)
    {
        if (_clock.getElapsedTime().asSeconds()>GAME_WIN_STATE_SHOW_TIME)
        {
            _data->machine.RemoveState();
        }
    }
    void GameWinState::Draw(float dt) {
        _data->window.clear();
        _data->window.draw(_background);
        _data->window.display();
    }
    
    
}
