#include "Character.h"
#include "Texture2D.h"


Character::Character(SDL_Renderer* renderer, string imagePath, Vector2D start_position)
{
	m_renderer = renderer;

	m_position = start_position;
	
	m_texture = new Texture2D(renderer);
	m_texture->LoadFromFile(imagePath);

	m_facing_direction = FACING_RIGHT;
	

}

Character::~Character()
{
	m_renderer = nullptr;

}

void Character::Render()
{
	if (m_facing_direction == FACING_RIGHT)
	{
		m_texture->Render(m_position, SDL_FLIP_NONE);
	}
	else
	{
		m_texture->Render(m_position, SDL_FLIP_HORIZONTAL);
	}

}

void Character::Update(float deltaTime, SDL_Event e)
{
	switch (e.type)
	{
		case SDL_KEYDOWN:
			switch (e.key.keysym.sym)
			{
			case SDLK_LEFT:
				m_position.x -= 1;
				m_facing_direction = FACING_LEFT;
				break;

			case SDLK_RIGHT:
				m_position.x += 1;				
				m_facing_direction = FACING_RIGHT;
				break;

			case SDLK_UP:
				m_position.y -= 1;
				break;

			case SDLK_DOWN:
				m_position.y += 1;
				break;

			}
	}

}

void Character::SetPosition(Vector2D new_position)
{
	m_position = new_position;


}

Vector2D Character::GetPosition()
{
	return m_position;


}
