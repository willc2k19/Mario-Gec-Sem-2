#pragma once
#ifndef _GAMESCREEN_H
#define _GAMESCREEN_H
#include <SDL.h>
#include "Collisions.h"
#include "constants.h"
#include <fstream>
#include <string>
#include <SDL_mixer.h>

using namespace std;

class Texture2D;

class GameScreen
{

public:
	GameScreen(SDL_Renderer* renderer);
	~GameScreen();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);
	
	bool LoadAudio();
	Mix_Chunk* death_sound;
	Mix_Chunk* gameover_sound;

protected:
	SDL_Renderer* m_renderer;

};

#endif //_GAMESCREEN_H