#pragma once
#include "Character.h"

class CharcterMario : public Character
{

public:
	CharacterMario(SDL_Renderer* renderer, string imagePath, Vector2D start_position);
	~CharacterMario();

	void Update(float deltaTime, SDL_Event e);
	void Render();

private:
	FACING m_facing_direction;
	bool m_moving_left;
	bool m_moving_right;









};

