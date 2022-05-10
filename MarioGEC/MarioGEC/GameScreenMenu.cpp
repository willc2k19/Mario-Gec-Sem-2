#include "GameScreenMenu.h"
#include <iostream>

GameScreenMenu::GameScreenMenu(SDL_Renderer* renderer) : GameScreen(renderer)
{
	MenuSetUp();
}

GameScreenMenu::~GameScreenMenu()
{
	delete m_background;
	m_background = nullptr;

	delete m_logo;
	m_logo = nullptr;
}

void GameScreenMenu::Render()
{
	m_background->Render(Vector2D(), SDL_FLIP_NONE);
	m_logo->Render(Vector2D(((SCREEN_WIDTH / 2) - (m_logo->GetWidth() / 2)), 50), SDL_FLIP_NONE);

}

void GameScreenMenu::Update(float deltaTime, SDL_Event e)
{

}

bool GameScreenMenu::MenuSetUp()
{
	m_background = new Texture2D(m_renderer);
	if (!m_background->LoadFromFile("Images/Background.png"))
	{
		cout<<"background texture failed to load! Error: " << SDL_GetError();
		return false;
	}
	
	m_logo = new Texture2D(m_renderer);
	if (!m_logo->LoadFromFile("Images / Logo.png"))
	{
		cout<<"logo texture failed to load! Error: " << SDL_GetError();
		return false;
	}
	return true;
}