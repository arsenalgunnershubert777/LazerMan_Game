#include "DamageInteractions.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
namespace g35 {
    DamageInteractions::DamageInteractions() { //takes in player, minion, boss manager objects and calculates damage interactions
        
    }
    void DamageInteractions::Update(float dt, SpongeBob * spongebob, JellyFishAI * jellyfishAI, BossManager * bossManager) {
        sf::FloatRect spongebobRect = spongebob->GetSprite().getGlobalBounds();
        for (int i = 0; i  < jellyfishAI->getJellyfishvector()->size(); i++) {//player (spongebob) hurt by minions
            sf::Sprite jellyfishSprite = jellyfishAI->getJellyfishvector()->at(i)->GetSprite();
            
            bool takesDamage = false;
            
            if (spongebobRect.intersects(jellyfishSprite.getGlobalBounds())){
                takesDamage = true;
            }
            
            if (takesDamage) {
                float spongebobhealth = spongebob->getHealth();
                float newSpongebobHealth = spongebobhealth - JELLYFISH_DAMAGE;
                spongebob->setHealth(newSpongebobHealth);
                
            }
            
            
            
        }
        for (int i = 0; i  < jellyfishAI->getJellyFishUntargetedVector()->size(); i++) {
            sf::Sprite jellyfishSprite = jellyfishAI->getJellyFishUntargetedVector()->at(i)->GetSprite();
            bool takesDamage = false;
            if (spongebobRect.intersects(jellyfishSprite.getGlobalBounds())){
                takesDamage = true;
            }
            
            if (takesDamage) {
                float spongebobhealth = spongebob->getHealth();
                float newSpongebobHealth = spongebobhealth - JELLYFISH_DAMAGE;
                spongebob->setHealth(newSpongebobHealth);
                
            }
            
            
        }
        
        
        
        
        switch (bossManager->getCurrentGameLevel()) { //player hurt by bosses
            case 0:
                if (spongebob->GetSprite().getGlobalBounds().intersects(bossManager->boss->GetSprite().getGlobalBounds())) {
                    float spongebobhealth = spongebob->getHealth();
                    float newSpongebobHealth = spongebobhealth - BOSS_ONE_DAMAGE;
                    spongebob->setHealth(newSpongebobHealth);
                }
                break;
            case 1:
                for (int k = 0; k < bossManager->boss->getBulletVector()->size(); k++) {
                    
                    if (bossManager->boss->getBulletVector()->at(k)->shape.getGlobalBounds().intersects(spongebob->GetSprite().getGlobalBounds())) {
                        spongebob->setHealth(spongebob->getHealth() - BOSS_TWO_DAMAGE);
                        bossManager->boss->getBulletVector()->erase(bossManager->boss->getBulletVector()->begin() + k);
                        
                    }
                    
                    
                }
                break;
            case 2:
                for (int k = 0; k < bossManager->boss->getBulletVector()->size(); k++) {
                    if (bossManager->boss->getBulletVector()->at(k)->shape.getGlobalBounds().intersects(spongebob->GetSprite().getGlobalBounds())) {
                        spongebob->setHealth(spongebob->getHealth() - BOSS_THREE_DAMAGE);
                        spongebob->setFreezeState(true);
                        bossManager->boss->getBulletVector()->erase(bossManager->boss->getBulletVector()->begin() + k);
                    }
                }
                break;
            case 3:
                float Damage;
                if (bossManager->boss->getHealth() > BOSS_FOUR_STARTING_HEALTH/3) {
                    Damage = BOSS_FOUR_STAGE_1_DAMAGE;
                }
                else {
                    Damage = BOSS_FOUR_STAGE_2_DAMAGE;
                }
                for (int k = 0; k < bossManager->boss->getBulletVector()->size(); k++) {
                    if (bossManager->boss->getBulletVector()->at(k)->shape.getGlobalBounds().intersects(spongebob->GetSprite().getGlobalBounds())) {
                        spongebob->setHealth(spongebob->getHealth() - Damage);
                        bossManager->boss->getBulletVector()->erase(bossManager->boss->getBulletVector()->begin() + k);
                    }
                }
                
                break;
        }
        
        
        
        
        
        
        for (int k = 0; k < spongebob->getBulletVector()->size(); k++) { //player hurting bosses
            
            if (spongebob->getBulletVector()->at(k)->shape.getGlobalBounds().intersects(bossManager->boss->GetSprite().getGlobalBounds())) {
                bossManager->boss->setHealth(bossManager->boss->getHealth()- MAIN_CHARACTER_BEAM_DAMAGE);
                spongebob->getBulletVector()->erase(spongebob->getBulletVector()->begin() + k);
            }
            
        }
       
        for (int k = 0; k < spongebob->getBulletVector()->size(); k++) { //player hurting minions
            
            for (int j = 0; j < jellyfishAI->getJellyfishvector()->size(); j++) {
                
                if (spongebob->getBulletVector()->at(k)->shape.getGlobalBounds().intersects(jellyfishAI->getJellyfishvector()->at(j)->GetSprite().getGlobalBounds()))
                {
                    
                    jellyfishAI->getJellyfishvector()->at(j)->setHealth(jellyfishAI->getJellyfishvector()->at(j)->getHealth() - MAIN_CHARACTER_BEAM_DAMAGE);
                    
                    spongebob->getBulletVector()->erase(spongebob->getBulletVector()->begin() + k);
                    break;
                    
                }
            }
            
        }
        for (int k = 0; k <spongebob->getBulletVector()->size(); k++) {
            
            for (int j = 0; j < jellyfishAI->getJellyFishUntargetedVector()->size(); j++) {
                
                if (spongebob->getBulletVector()->at(k)->shape.getGlobalBounds().intersects(jellyfishAI->getJellyFishUntargetedVector()->at(j)->GetSprite().getGlobalBounds()))
                {
                    
                    jellyfishAI->getJellyFishUntargetedVector()->at(j)->setHealth(jellyfishAI->getJellyFishUntargetedVector()->at(j)->getHealth() - spongebob->getBeamDamage());
                    
                    spongebob->getBulletVector()->erase(spongebob->getBulletVector()->begin() + k);
                    
                    break;
                }
            }
        }
        
    
    
    }
}
