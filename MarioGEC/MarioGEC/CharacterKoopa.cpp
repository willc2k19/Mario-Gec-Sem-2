#include "CharacterKoopa.h"

CharacterKoopa::CharacterKoopa(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, LevelMap* map, FACING start_facing, float movement_speed) :Character(renderer, imagePath, start_position, map)
{

	m_facing_direction = start_facing;
	m_movement_speed = movement_speed;
	m_position = start_position;
	m_injured = false;

	m_single_sprite_w = m_texture->GetWidth() / 2;
	m_single_sprite_h = m_texture->GetHeight();

}

CharacterKoopa::~CharacterKoopa()
{

}

void CharacterKoopa::TakeDamage()
{
	m_injured = true;
	m_injured_time = INJURED_TIME;
	Jump();
}

void CharacterKoopa::Jump()
{
	if (!m_jumping)
	{
		m_jump_force = INITIAL_JUMP_FORCE_SMALL;
		m_jumping = true;
		m_can_jump = false;
	}
}

void CharacterKoopa::FlipRightwayUp()
{
	if (m_facing_direction == FACING_LEFT)
	{
		m_facing_direction == FACING_RIGHT;
	}
	else
	{
		m_facing_direction == FACING_LEFT;
	}
	m_injured = false;
	Jump();
}

void CharacterKoopa::Render()
{
	//variable to hold left position of sprite to draw
	int left = 0.0f;

	//if injured move position to second image on spritesheet
	if (m_injured)
		left = m_single_sprite_w;

	//get portion of spritesheet to draw
	//							  xPos, Ypos, width of sprite, height of sprite
	SDL_Rect portion_of_sprite = { left,0,m_single_sprite_w, m_single_sprite_h };

	//determine where to draw
	SDL_Rect destRect = { (int)(m_position.x),(int)(m_position.y),m_single_sprite_w, m_single_sprite_h };

	//then draw facing correct direction
	if (m_facing_direction == FACING_RIGHT)
	{
		m_texture->Render(portion_of_sprite, destRect, SDL_FLIP_NONE);
	}
	else
	{
		m_texture->Render(portion_of_sprite, destRect, SDL_FLIP_HORIZONTAL);
	}

}

void CharacterKoopa::Update(float deltaTime, SDL_Event e)
{
	//use code within base class
	Character::Update(deltaTime, e);

	if (!m_injured)
	{
		//enemy is not injured, move
		if (m_facing_direction == FACING_LEFT)
		{
			m_moving_left = true;
			m_moving_right = false;
		}
		else if (m_facing_direction == FACING_RIGHT)
		{
			m_moving_right = true;
			m_moving_left = false;
		}
	}
	else
	{
		//we should not move, injured
		m_moving_right = false;
		m_moving_left = false;

		//count down injured time
		m_injured_time -= deltaTime;

		if (m_injured_time <= 0.0)
			FlipRightwayUp();
	}
}

bool CharacterKoopa::GetInjured()
{
	return m_injured;
}

bool CharacterKoopa::GetAlive()
{
	return m_alive;
}

void CharacterKoopa::SetAlive(bool isAlive)
{
	m_alive = isAlive;
}


