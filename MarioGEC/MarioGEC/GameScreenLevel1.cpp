#include "GameScreenLevel1.h"
#include "Texture2D.h"
#include <iostream>


GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpLevel();

}


bool GameScreenLevel1::SetUpLevel()
{

	//load texture
	m_background_texture = new Texture2D(m_renderer);

	if (!m_background_texture->LoadFromFile("Images/BackgroundMB.png"))
	{
		std::cout << "Failed to load background texture!" << std::endl;
		return false;
	}

	//set up player character
	mario = new CharacterMario(m_renderer, "Images/Mario.png", Vector2D(64, 330));
	luigi = new CharacterLuigi(m_renderer, "Images/Luigi.png", Vector2D(164, 330));


}

GameScreenLevel1::~GameScreenLevel1()
{
	m_background_texture = nullptr;

	mario = nullptr;
	luigi = nullptr;


}


void GameScreenLevel1::Render()
{
	//draw the background
	m_background_texture->Render(Vector2D(), SDL_FLIP_NONE);

	//render character
	mario->Render();
	luigi->Render();

}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	//update character
	mario->Update(deltaTime, e);
	luigi->Update(deltaTime, e);



}
