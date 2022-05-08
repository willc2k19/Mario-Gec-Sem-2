#pragma once
#include "Character.h"

class CharacterLuigi : public Character
{

public:
	CharacterLuigi(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map);
	~CharacterLuigi();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);


private:
	FACING m_facing_direction;
	bool mMovingLeft;
	bool mMovingRight;
	LevelMap* m_current_level_map;

};


