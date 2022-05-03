#pragma once
#include <iostream>
#include <SDL.h>
#include "Commons.h"
#include "constants.h"
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


public:
	Character(SDL_Renderer* renderer, string imagePath, Vector2D start_position);
	~Character();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);
	void SetPosition(Vector2D new_position);
	Vector2D GetPosition();


private:
	FACING m_facing_direction;
};

