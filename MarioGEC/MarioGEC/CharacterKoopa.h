#pragma once
#include "Character.h"
#include "LevelMap.h"
#include "Commons.h"
#include "Texture2D.h"
#include "constants.h"


class CharacterKoopa : public Character
{
private:
	float m_single_sprite_w;
	float m_single_sprite_h;
	bool m_injured;
	float m_injured_time;

	void FlipRightwayUp();

	FACING m_facing_direction;
	float m_movement_speed;
	bool m_moving_left;
	bool m_moving_right;

public:
	CharacterKoopa(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, LevelMap* map, FACING start_facing, float movement_speed);
	~CharacterKoopa();

	void TakeDamage();
	void Jump();
	void Render();
	void Update(float deltaTime, SDL_Event e);

	bool GetAlive();
	void SetAlive(bool isAlive);
	bool GetInjured();

protected:
	bool m_alive = true;


};

