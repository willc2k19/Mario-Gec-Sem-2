#include "CharacterMario.h"
#include "Texture2D.h"


CharacterMario::CharacterMario(SDL_Renderer* renderer, string imagePath, Vector2D start_position)
{
	m_renderer = renderer;

	m_position = start_position;

	m_texture = new Texture2D(renderer);
	m_texture->LoadFromFile(imagePath);

	m_facing_direction = FACING_RIGHT;
	m_moving_left = false;
	m_moving_right = false;

}

CharacterMario::~CharacterMario()
{
	m_renderer = nullptr;

}

void CharacterMario::Render()
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

void CharacterMario::Update(float deltaTime, SDL_Event e)
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
		case SDLK_LEFT:
			m_moving_left = true;
			//m_position.x -= 1;
			//m_facing_direction = FACING_LEFT;
			break;

		case SDLK_RIGHT:
			m_moving_right = true;
			//m_position.x += 1;				
			//m_facing_direction = FACING_RIGHT;
			break;

		case SDLK_UP:
			if (m_can_jump)
			{
				Jump();
			}

		}
		break;
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			m_moving_left = false;
			//m_position.x -= 1;
			//m_facing_direction = FACING_LEFT;
			break;

		case SDLK_RIGHT:
			m_moving_right = false;
			//m_position.x += 1;				
			//m_facing_direction = FACING_RIGHT;
			break;
		}
		break;

	}

}

void CharacterMario::MoveLeft(float deltaTime)
{
	m_position.x -= deltaTime * MOVEMENTSPEED;
	m_facing_direction = FACING_LEFT;
}

void CharacterMario::MoveRight(float deltaTime)
{
	m_position.x += deltaTime * MOVEMENTSPEED;
	m_facing_direction = FACING_RIGHT;
}

void CharacterMario::Jump()
{
	if (!m_jumping)
	{
		m_jump_force = INITIAL_JUMP_FORCE;
		m_jumping = true;
		m_can_jump = false;
	}
}

void CharacterMario::AddGravity(float deltaTime)
{
	m_position.y += deltaTime * GRAVITY;
	m_can_jump = false;
}
void CharacterMario::SetPosition(Vector2D new_position)
{
	m_position = new_position;


}

Vector2D CharacterMario::GetPosition()
{
	return m_position;


}
