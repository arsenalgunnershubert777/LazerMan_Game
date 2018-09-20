#pragma once
#include "DEFINITIONS.hpp"
#include <SFML/Graphics.hpp>
#include "SpongeBob.hpp"
#include "JellyFishAI.hpp"
#include "BossManager.hpp"


namespace g35 {
    class DamageInteractions{
    public:
        DamageInteractions();
        void Update(float dt, SpongeBob * spongebob, JellyFishAI * jellyfishAI,BossManager * bossManager);
        
    private:
        
    };
}
