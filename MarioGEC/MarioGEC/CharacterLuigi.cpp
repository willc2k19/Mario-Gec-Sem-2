#include "CharacterLuigi.h"
#include "Texture2D.h"

CharacterLuigi::CharacterLuigi(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map) : Character(renderer, imagePath, start_position, map)
{
	//m_renderer = renderer;

	//m_position = start_position;

	//m_texture = new Texture2D(renderer);
	//m_texture->LoadFromFile(imagePath);

	m_facing_direction = FACING_RIGHT;
	m_moving_left = false;
	m_moving_right = false;
	m_current_level_map = map;

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


	//collision variables for positioning
	int m_central_x_pos = (int)(m_position.x + (m_texture->GetWidth() * 0.5f)) / TILE_WIDTH;
	int m_foot_pos = (int)(m_position.y + m_texture->GetHeight()) / TILE_HEIGHT;

	if (m_current_level_map->GetTileAt(m_foot_pos, m_central_x_pos) == 0)
	{
		AddGravity(deltaTime);
	}
	else
	{
		m_can_jump = true;
	}

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
