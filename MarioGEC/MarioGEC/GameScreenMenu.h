#pragma once
#ifndef _GAMESCREENMENU_H
#define _GAMESCREENMENU_H

#include "GameScreen.h"
#include "Texture2D.h"

class Texture2D;

class GameScreenMenu : GameScreen
{
private:
	bool MenuSetUp();
	Texture2D* m_background;
	Texture2D* m_logo;

public:
	GameScreenMenu(SDL_Renderer* renderer);
	~GameScreenMenu();

	void Render();
	void Update(float deltaTime, SDL_Event e);


};

#endif // !_GAMESCREENMENU_H
