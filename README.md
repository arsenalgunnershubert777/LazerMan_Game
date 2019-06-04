# LazerMan_Game

## Project Description and Motivation:
This repository contains code for a game created with some friends during a Programming 2 Course at the University of Florida. This was kind of a free for all project and we wanted to do something fun with what we've learned so far. 

## Gameplay:
This game involves a main character, called the Lazer Man, which shoots a lazer beam to kill opposing enemies and bosses. Every character has a health and forms of attack. There are four levels with four bosses to beat, before the game is won.

## Design Goals:
- implementing workable game loop
- using artificial intelligence to control bosses and enemies
- modular code for easy modification
- unique graphics and user interface

## Features:
### Characters:
#### LazerMan:
The main player, known as Lazer Man, (also referred to by spongnebob in the source files, since we wanted to do spongebob first lol), can move in 8 directions and shoot a lazer beam. It is controlled by computer keys up down left right and 'B' for beam.
#### Enemies:
The enemies, (also referred to as jellyfish, see above lol) are little annoying minions that seek to surround the main player and inflict damage. They will either die off or respawn according to the settings on each level.
#### Bosses:
The bosses, which there are four of, are the main antagonists that the main player has to defeat to move on to the next levels and eventually in the game. The first boss is very fast and tries to attack the player by approaching it in a direction that avoids the main player's laser beams. The second boss spawns randomly and shoots a radius of lasers. The third boss shoots freeze beams at the player and tracks toward the player. The fourth and final boss shoots deadly beams that go ahead of the player's current movement.
### Game Loop:
The game loop is a fixed time step game loop with interpolation, providing relatively good performance and integration.
### State Machine:
Uses a stack to keep track of different game states, like menu or playing, or loading screen.
### AI:
The enemies are managed by a class that implements AI methods to surround the main player from as many directions as possible, trying to trap the player without lagging behind.

## Performance:
Our group was very satisfied with the game. We had a lot of fun and learned a lot about how games work. We really liked the SFML library as it provided a lot of useful resources for user experience.

## Repository Information:
The source files are in the SFML Tutorial folder (not the .xcodeproj one). The images for the game are in the resources folder.

## Installation and Testing: 
You will need the SFML library to run the code.

## Help Received:
In terms of coding the game loop and state machine, we had help from Sonar Systems' youtube videos and resources: https://github.com/SonarSystems?tab=repositories

## Contributors:
- Hubert Zhao
- Nicolas Amaya
- Boyd Duffie
- Rahul Rudra
- Jeremy Cruz

### Individual Contribution:
My contributions included coding most of the character classes, game loop class, statemachine class, and implementing the AI algorithms.
## License:
This project is licensed under the terms of the MIT license.
