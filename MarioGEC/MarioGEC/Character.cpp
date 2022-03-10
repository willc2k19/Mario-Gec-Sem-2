#include "Character.h"
#include "Texture2D.h"

Character::Character(SDL_Renderer* renderer, string imagePath, Vector2D start_position)
{
	m_renderer = renderer;

	m_position = start_position;
	
	m_texture = new Texture2D(renderer);
	m_texture->LoadFromFile(imagePath);
}

Character::~Character()
{
	m_renderer = nullptr;

}

void Character::Render()
{

	m_texture->Render(m_position, SDL_FLIP_NONE);

}

void Character::Update(float deltaTime, SDL_Event e)
{
	switch (e.type)
	{
		case SDL_KEYUP:
			switch (e.key.keysym.sym)
			{
			case SDLK_LEFT:
				m_position.x -= 1;

			case SDLK_RIGHT:
				m_position.x += 1;

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
