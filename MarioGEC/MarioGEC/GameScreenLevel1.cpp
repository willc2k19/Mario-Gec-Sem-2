#include "GameScreenLevel1.h"
#include "Texture2D.h"
#include <iostream>



bool GameScreenLevel1::SetUpLevel()
{
	//load texture
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/text.bmp"))
	{
		std::cout << "Failed to load background texture!" << std::endl;
		return false;
	}


}

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpLevel();

	m_background_texture = nullptr;
}

GameScreenLevel1::~GameScreenLevel1()
{

}

void GameScreenLevel1::Render()
{
	//draw the background
	m_background_texture->Render(Vector2D(), SDL_FLIP_NONE);


}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{

}
