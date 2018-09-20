/*This is the main class of the Game project our Group created.
 *We based our idea off of games such as "Binding Isaac" and "Boxhead"
 *In terms of coding the game loop and state machine, we had help from Sonar Systems' youtube videos and resources: https://github.com/SonarSystems?tab=repositories
 *We used SFML library and found it was very useful to display the graphics.
 *Our game takes a player controlled character and puts it against bosses in a movement based showdown.
 * Authors are: Hubert Zhao, Nicolas Amaya, Boyd Duffie, Rahul Rudra, Jeremy Cruz
 */
#include <SFML/Graphics.hpp>
#include "DEFINITIONS.hpp"
#include "Game.hpp"
#include <iostream>
#include "SplashState.hpp"


int main() {
    g35::Game(SCREEN_WIDTH,SCREEN_HEIGHT, "LazerMan");
    return EXIT_SUCCESS;
    
    //creates a game object which will run the game loop
}
