#include "MainMenuState.hpp"
#include <sstream>
#include "DEFINITIONS.hpp"
#include <iostream>
#include "GameState.hpp"
#include "GameOverState.hpp"

namespace g35 //Main Menu page
{
    MainMenuState::MainMenuState(GameDataRef data) : _data(data)
    {
        
    }
    void MainMenuState::Init()
    {
        _data->assets.LoadTexture("Main Menu Background", MAIN_MENU_BACKGROUND_FILEPATH);
        _data->assets.LoadTexture("Play Button", PLAY_BUTTON_FILEPATH);
        
        
        _background.setTexture(this->_data->assets.GetTexture("Main Menu Background"));
        _playButton.setTexture(this->_data->assets.GetTexture("Play Button"));
        
        _background.scale(1.1,1);
        _playButton.setPosition(.425*SCREEN_WIDTH, .37*SCREEN_HEIGHT);
        _playButton.scale(3,3);
       
        
    }
    void MainMenuState::HandleInput(){
        sf::Event event;
        while (_data->window.pollEvent(event)) {
            if (sf::Event::Closed == event.type) {
                _data->window.close();
            }
            if (_data->input.IsSpriteClicked(_playButton,sf::Mouse::Left, _data->window)) //play button to click
            {
                _data->machine.AddState(StateRef(new GameState(_data)), false);
            }
        }
    }
    void MainMenuState::Update(float dt)
    {
        
    }
    void MainMenuState::Draw(float dt) {
        _data->window.clear();
        _data->window.draw(_background);
        _data->window.draw(_playButton);
        _data->window.display();
    }
    
    
}
