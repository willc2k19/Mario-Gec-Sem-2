#pragma once
#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H
#include <SDL.h>
#include "Commons.h"
#include "GameScreen.h"
#include "Character.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"
#include "LevelMap.h"
#include "CharacterKoopa.h"
//#include "CharacterGoomba.h"
//#include "CharacterCoin.h"
#include <vector>

class Texture2D;

class Character;

class PowBlock;

class GameScreenLevel1 : GameScreen
{
private:
	Texture2D* m_background_texture;
	Texture2D* m_transparency;
	Texture2D* m_level_texture;




	CharacterMario* mario;
	CharacterLuigi* luigi;


	bool SetUpLevel();
	void SetLevelMap();
	LevelMap* m_level_map;
	PowBlock* m_pow_block;
	bool m_screenshake;
	float m_shake_time;
	float m_wobble;
	float m_background_yPos;
	bool isDead;
	bool pow_block_hit;
	float hit_timer;
	float enemy_timer;
	void DoScreenShake();


	vector<CharacterKoopa*> m_enemy_koopa;
	//vector<CharacterGoomba*> m_enemy_goomba;
	//vector<CharacterCoin*> m_coins;

public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;
	void UpdatePowBlock();
	void UpdateEnemyKoopa(float deltaTime, SDL_Event e);
	void CreateKoopa(Vector2D position, FACING direction, float speed);
	void WallWrapping(Character* character);


};




#endif //_GAMESCREENLEVEL1_H