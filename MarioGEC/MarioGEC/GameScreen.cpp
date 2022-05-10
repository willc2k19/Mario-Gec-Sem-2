#include "GameScreen.h"
#include <SDL_image.h>
#include <iostream>

GameScreen::GameScreen(SDL_Renderer* renderer)
{
	m_renderer = renderer;
}

GameScreen::~GameScreen()
{
	m_renderer = nullptr;
}

void GameScreen::Render()
{

}

void GameScreen::Update(float deltaTime, SDL_Event e)
{

}


bool GameScreen::LoadAudio()
{
	death_sound = Mix_LoadWAV("Music/Death.wav");
	gameover_sound = Mix_LoadWAV("Music/GameOver.wav");

	if (gameover_sound == nullptr)
	{
		cout << "gameover sound failed to load. error: " << Mix_GetError();
		return false;

	}
	if (death_sound == nullptr)
	{
		cout << "death sound failed to load. error: " << Mix_GetError();
		return false;

	}
	return true;
}
