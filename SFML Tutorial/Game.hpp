#pragma once
#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include "StateMachine.hpp"
#include "AssetManager.hpp"
#include "InputManager.hpp"

namespace g35{
    struct GameData //this struct will be used by other classes to access the functionality associated with its field objects
    {
        StateMachine machine;
        sf::RenderWindow window;
        AssetManager assets;
        InputManager input;
    };
    typedef std::shared_ptr<GameData> GameDataRef;
   
    class Game {
    public:
        Game(int width, int height, std::string title);
    private:
        const float dt = 1.0f/60.0f;
        sf::Clock _clock;
        GameDataRef _data = std::make_shared<GameData>();
        void Run();
        
    };
}
