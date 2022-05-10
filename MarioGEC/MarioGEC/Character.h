#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>
#include "Commons.h"
#include "constants.h"
#include "LevelMap.h"
#include "Texture2D.h"
using namespace std;

class Texture2D;


class Character
{

protected:
	SDL_Renderer* m_renderer;
	Vector2D m_position;
	Texture2D* m_texture;
	bool m_moving_left;
	bool m_moving_right;
	bool m_jumping;
	bool m_can_jump;
	float m_jump_force;
	virtual void MoveLeft(float deltaTime);
	virtual void MoveRight(float deltaTime);
	void AddGravity(float deltaTime);
	void Jump();
	float m_collision_radius;
	bool m_alive = true;

public:
	Character(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map);
	~Character();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);
	void SetPosition(Vector2D new_position);
	Vector2D GetPosition();

	float GetCollisionRadius();
	Rect2D GetCollisionBox();

	bool IsJumping();
	void CancelJump();

	bool LoadAudio();
	Mix_Chunk* jump_sound;
	Mix_Chunk* dead_sound;


	void SetAlive(bool isAlive);
	bool GetAlive()
	{
		return m_alive;
	}

private:
	FACING m_facing_direction;
	LevelMap* m_current_level_map;
};

