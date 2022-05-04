#pragma once
#include "Commons.h"

class Character;

class Collisions
{
public:
	~Collisions();
	static Collisions* Instance();
	bool Circle(Character* mario, Character* luigi);
	bool Box(Rect2D rect1, Rect2D rect2);

private:
	Collisions();
	static Collisions* m_instance;
};

