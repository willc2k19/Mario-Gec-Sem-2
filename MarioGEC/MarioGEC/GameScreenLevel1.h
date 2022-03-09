#pragma once
#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H
#include <SDL.h>
#include "Commons.h"
#include "GameScreen.h"





class GameScreenLevel1 : GameScreen
{
private:
	Texture2D* m_background_texture;

	bool SetUpLevel();


public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;

};


class Texture2D;


#endif //_GAMESCREENLEVEL1_H