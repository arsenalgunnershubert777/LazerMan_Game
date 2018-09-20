#pragma once


#include "Game.hpp"
#include "JellyFish.hpp"
#include <SFML/Graphics.hpp>
#include "DEFINITIONS.hpp"
#include <vector>
#include <set>

namespace g35{
    class JellyFishAI{
    public:
        JellyFishAI();
        JellyFishAI(GameDataRef data);
        void Draw();
        void Update(float dt, sf::FloatRect spongebobrect);
       
        std::vector<sf::FloatRect> getRectVector();
        void Init(int numTargeted, int numUntargeted);
        bool ProcessJellyFishDeaths();
        bool ProcessJellyRevival();
        void ProcessUntargetedJellies();
        void ProcessTargetedJellies(bool changeTargets, sf::FloatRect spongebobrect);
        float getDistance(float* jellyMovePosition, float* targetPosition);
        int findMoveToTarget(float * jellyPosition, float * targetPosition, std::set<int> impossibleMoves);
        void regenJelly(std::vector<JellyFish *>* jellyvector , bool isTargeted);
        std::vector<JellyFish*>* getJellyfishvector();
        std::vector<JellyFish*>* getJellyFishUntargetedVector();
        std::set<int> getImpossibleMoves(JellyFish * jellyfish);
        void setMovingStates(bool movingStates);
        
        
        
    private:
        GameDataRef _data;
        std::vector<JellyFish*> jellyfishvector;
        std::vector<JellyFish*> jellyFishUntargetedVector;
        
        int _numJellies;
        bool justInit;
        int _currGameLevel;
        std::vector<std::vector<int>> _gameLevelStates;
        bool movingStates;
         sf::Clock _clock;
        
        
    };
    
}
