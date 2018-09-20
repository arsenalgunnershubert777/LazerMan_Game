/* We defined many important definitions here for the game.
 * This includes character properties, file paths, time properties, screen dimensions.
 */


#pragma once
#define SCREEN_WIDTH 1100
#define SCREEN_HEIGHT 800

# define pi           3.14159265358979323846

#define SPLASH_STATE_SHOW_TIME 3.0
#define GAME_OVER_STATE_SHOW_TIME 3.0
#define GAME_WIN_STATE_SHOW_TIME 3.0
#define NUM_GAME_LEVELS 4

#define SPLASH_SCENE_BACKGROUND_FILEPATH "Resources/img/loading screen.png"
#define MAIN_MENU_BACKGROUND_FILEPATH "Resources/img/title screen.png"
#define PLAY_BUTTON_FILEPATH "Resources/img/play button.png"
#define PAUSE_BUTTON_FILEPATH "Resources/img/pause button.png"
#define EXIT_BUTTON_FILEPATH "Resources/img/exit.png"


#define GAME_BACKGROUND_FILEPATH "Resources/img/game map with grid.png"
#define GAME_OVER_BACKGROUND_FILEPATH "Resources/img/game over screen.png"
#define GAME_WIN_BACKGROUND_FILEPATH "Resources/img/WinScreen.png"

#define MAIN_CHARACTER_FILEPATH "Resources/img/MainCharacter.png" //file path to main character
#define MAIN_CHARACTER_FROZEN_FILEPATH "Resources/img/MainCharacterFrozen.png"

#define ROUND_1 "Resources/img/round counter-1.png"//file paths to game round labels
#define ROUND_2 "Resources/img/round counter-2.png"
#define ROUND_3 "Resources/img/round counter-3.png"
#define ROUND_4 "Resources/img/round counter-4.png"

#define HEALTH_1 "Resources/img/health-1.png"//file path to sprites for health bar
#define HEALTH_2 "Resources/img/health-2.png"
#define HEALTH_3 "Resources/img/health-3.png"
#define HEALTH_4 "Resources/img/health-4.png"
#define HEALTH_5 "Resources/img/health-5.png"
#define HEALTH_6 "Resources/img/health-6.png"
#define HEALTH_7 "Resources/img/health-7.png"
#define HEALTH_8 "Resources/img/health-8.png"
#define HEALTH_9 "Resources/img/health-9.png"
#define HEALTH_10 "Resources/img/health-10.png"

#define MAIN_CHARACTER_LABEL "Resources/img/lazerman label.png"
#define BOSS_LABEL "Resources/img/boss label.png"

#define SPONGEBOB_STATE_STILL 0 //in this case SPONGEBOB is synonymous with MAIN_CHARACTER, since we originally
#define SPONGEBOB_STATE_N 1 //wanted to do spongebob but then thought that since it was copyrighted,
#define SPONGEBOB_STATE_E 2 //we could make our own characters instead. We did not have enough time to convert all
#define SPONGEBOB_STATE_S 3 //of the names back to MAIN_CHARACTER
#define SPONGEBOB_STATE_W 4 //SpongeBob/MainCharacter is controlled by the Player
#define SPONGEBOB_STATE_NE 5
#define SPONGEBOB_STATE_SE 6
#define SPONGEBOB_STATE_SW 7
#define SPONGEBOB_STATE_NW 8

#define SPONGEBOB_MOVEMENT_DURATION .10
#define MAIN_CHARACTER_MOVEMENT_SPEED 2

#define MAIN_CHARACTER_BEAM_DAMAGE 50 
#define MAIN_CHARACTER_REGENERATION_HEALTH 0.5
#define MAIN_CHARACTER_REGENERATION_BEAM_HEALTH 5
#define MAIN_CHARACTER_BEAM_STARTING_HEALTH 10000
#define MAIN_CHARACTER_BEAM_RADIUS 5
#define MAIN_CHARACTER_BEAM_SPEED_MULTIPLIER 10.0
#define MAIN_CHARACTER_STARTING_HEALTH 15000

#define MINION_FILEPATH "Resources/img/Minion.png" //similarly, JELLYFISH is synonymous with MINION
#define JELLYFISH_STATE_STILL 0 //These creatures are a nuisance and do damage to the MAIN_CHARACTER
#define JELLYFISH_STATE_N 1
#define JELLYFISH_STATE_E 2
#define JELLYFISH_STATE_S 3
#define JELLYFISH_STATE_W 4
#define MINION_MOVEMENT_SPEED 1
#define MINION_STARTING_HEALTH 7000
#define JELLYFISH_MOVEMENT_DURATION .10
#define JELLYFISH_DAMAGE 5

#define BOSS_ONE_SPRITE_FILEPATH "Resources/img/Boss1.png" //these are the definitions for boss One and so on
#define BOSS_ONE_MOVEMENT_SPEED 3.25
#define BOSS_ONE_STATE_CHASING 0
#define BOSS_ONE_STATE_RUNNING 1
#define BOSS_ONE_DAMAGE 80
#define BOSS_ONE_STARTING_HEALTH 50000


#define BOSS_TWO_SPRITE_FILEPATH "Resources/img/Boss2.png"
#define BOSS_TWO_MOVEMENT_SPEED 1
#define BOSS_TWO_DAMAGE 80
#define BOSS_TWO_STARTING_HEALTH 100000
#define BOSS_TWO_BEAM_RADIUS 7.5
#define BOSS_TWO_BEAM_SPEED_MULTIPLIER 1.0

#define BOSS_THREE_SPRITE_FILEPATH "Resources/img/Boss3.png"
#define BOSS_THREE_MOVEMENT_SPEED 0.325
#define BOSS_THREE_DAMAGE 60
#define BOSS_THREE_STARTING_HEALTH 150000
#define BOSS_THREE_BEAM_RADIUS_BEGIN 10
#define BOSS_THREE_BEAM_SPEED_SET 0.5


#define BOSS_FOUR_SPRITE_FILEPATH "Resources/img/Boss4 stage1.png"
#define BOSS_FOUR_SPRITE_RAGE_FILEPATH "Resources/img/Boss4 stage2.png"
#define BOSS_FOUR_MOVEMENT_SPEED 0.20
#define BOSS_FOUR_MOVEMENT_RAGE_SPEED 0.40
#define BOSS_FOUR_STAGE_1_DAMAGE 100
#define BOSS_FOUR_STAGE_2_DAMAGE 75
#define BOSS_FOUR_STARTING_HEALTH 200000
#define BOSS_FOUR_BEAM_RADIUS_STAGE1 7.5
#define BOSS_FOUR_BEAM_RADIUS_STAGE2 12.5
#define BOSS_FOUR_BEAM_SPEED_STAGE1_SET 1.0
#define BOSS_FOUR_BEAM_SPEED_STAGE2_SET 0.5
