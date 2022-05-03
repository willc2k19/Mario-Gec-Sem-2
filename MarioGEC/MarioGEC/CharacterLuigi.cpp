#include "CharacterLuigi.h"
#include "Texture2D.h"

CharacterLuigi::CharacterLuigi(SDL_Renderer* renderer, string imagePath, Vector2D start_position) : Character(renderer, imagePath, start_position)
{
	//m_renderer = renderer;

	//m_position = start_position;

	//m_texture = new Texture2D(renderer);
	//m_texture->LoadFromFile(imagePath);

	m_facing_direction = FACING_RIGHT;
	m_moving_left = false;
	m_moving_right = false;

}

CharacterLuigi::~CharacterLuigi()
{
	//m_renderer = nullptr;

}

void CharacterLuigi::Render()
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

void CharacterLuigi::Update(float deltaTime, SDL_Event e)
{

	if (m_jumping)
	{
		m_position.y -= m_jump_force * deltaTime;

		m_jump_force -= JUMP_FORCE_DECREMENT * deltaTime;

		if (m_jump_force <= 0.0f)
			m_jumping = false;
	}

	if (m_moving_left)
	{
		MoveLeft(deltaTime);
	}
	else if (m_moving_right)
	{
		MoveRight(deltaTime);
	}

	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_a:
			m_moving_left = true;
			m_facing_direction = FACING_RIGHT;
			break;

		case SDLK_d:
			m_moving_right = true;
			m_facing_direction = FACING_LEFT;
			break;

		case SDLK_w:
			Jump();
			break;
		}
		break;
		case SDL_KEYUP:
			switch (e.key.keysym.sym)
			{
			case SDLK_a:
				m_moving_left = false;
				//m_position.x -= 1;
				m_facing_direction = FACING_RIGHT;
				break;
			case SDLK_d:
				m_moving_right = false;
				//m_position.x += 1;				
				m_facing_direction = FACING_LEFT;
				break;
			}
			break;

	}

	if (m_position.y <= -1000)
	{
		AddGravity(deltaTime);
	}

}
