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

class Texture2D;

class Character;


class GameScreenLevel1 : GameScreen
{
private:
	Texture2D* m_background_texture;

	CharacterMario* mario;
	CharacterLuigi* luigi;


	bool SetUpLevel();
	void SetLevelMap();
	LevelMap* m_level_map;

public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;

};




#endif //_GAMESCREENLEVEL1_H