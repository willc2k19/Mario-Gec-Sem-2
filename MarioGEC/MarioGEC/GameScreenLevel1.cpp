#include "GameScreenLevel1.h"
#include "Texture2D.h"
#include <iostream>
#include "Collisions.h"
#include "PowBlock.h"

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	m_renderer = renderer;
	m_level_map = nullptr;
	isDead = false;
	pow_block_hit = false;
	hit_timer = 0.0f;
	SetUpLevel();
	

}


bool GameScreenLevel1::SetUpLevel()
{

	//load texture
	m_background_texture = new Texture2D(m_renderer);

	if (!m_background_texture->LoadFromFile("Images/BackgroundMB.png"))
	{
		std::cout << "Failed to load background texture!" << std::endl;
		return false;
	}

	SetLevelMap();

	//set up player character
	mario = new CharacterMario(m_renderer, "Images/Mario.png", Vector2D(64, 342),m_level_map);
	luigi = new CharacterLuigi(m_renderer, "Images/Luigi.png", Vector2D(414, 342),m_level_map);
	m_pow_block = new PowBlock(m_renderer, m_level_map);
	CreateKoopa(Vector2D(150, 32), FACING_RIGHT, KOOPA_SPEED);
	CreateKoopa(Vector2D(325, 32), FACING_LEFT, KOOPA_SPEED);


	m_screenshake = false;
	m_background_yPos = 0.0f;

}

GameScreenLevel1::~GameScreenLevel1()
{
	m_background_texture = nullptr;

	mario = nullptr;
	luigi = nullptr;
	m_pow_block = nullptr;
	
	m_enemy_koopa.clear();

}


void GameScreenLevel1::Render()
{
	//draw enemies
	for (int i = 0; i < m_enemy_koopa.size();i++)
	{
		m_enemy_koopa[i]->Render();
	}


	//draw the background
	m_background_texture->Render(Vector2D(0, m_background_yPos), SDL_FLIP_NONE);

	//render character
	mario->Render();
	luigi->Render();
	m_pow_block->Render();

}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	//do shake if needed
	if (m_screenshake)
	{
		m_shake_time -= deltaTime;
		m_wobble++;
		m_background_yPos = sin(m_wobble);
		m_background_yPos *= 3.0f;

		//end shake when time is up
		if (m_shake_time <= 0.0f)
		{
			m_shake_time = false;
			m_background_yPos = 0.0f;
		}
	}



	//update character
	mario->Update(deltaTime, e);
	luigi->Update(deltaTime, e);
	WallWrapping(mario);
	WallWrapping(luigi);
	

	UpdatePowBlock();
	UpdateEnemyKoopa(deltaTime, e);

	//if(Collisions::Instance()->Circle(mario,luigi))
	//	cout<<"Circle hit!"<<endl;

	if (Collisions::Instance()->Box(mario->GetCollisionBox(), luigi->GetCollisionBox()))
	{
		cout << "Box collision!" << endl;
	}




}

void GameScreenLevel1::SetLevelMap()
{
	int map[MAP_HEIGHT][MAP_WIDTH] = {
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0},
		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
		{1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};
	//clear old maps
	if (m_level_map != nullptr)
	{
		delete m_level_map;
	}
	//set new map
	m_level_map = new LevelMap(map);
}

void GameScreenLevel1::UpdatePowBlock()
{
	if (pow_block_hit)
	{
		hit_timer -= 1.0f;

	}

	if (hit_timer == 0.0f)
	{
		pow_block_hit = false;
	}

	if (Collisions::Instance()->Box(mario->GetCollisionBox(), m_pow_block->GetCollisionBox()))
	{
		if (m_pow_block->IsAvailable())
		{
			std::cout << "Collision with POW" << std::endl;
			//Collided whilst jumping.
			if (mario->IsJumping()&&!pow_block_hit)
			{
				DoScreenShake();
				m_pow_block->TakeHit();
				mario->CancelJump();
				pow_block_hit = true;
			}
		}
	}
	else if (Collisions::Instance()->Box(luigi->GetCollisionBox(), m_pow_block->GetCollisionBox()))
	{
		if (m_pow_block->IsAvailable() && !pow_block_hit)
		{
			std::cout << "luigi pow collide" << std::endl;
			if (luigi->IsJumping())
			{
				DoScreenShake();
				m_pow_block->TakeHit();
				luigi->CancelJump();
				pow_block_hit = true;
			}
		}
	}
}

void GameScreenLevel1::DoScreenShake()
{

	for (unsigned int i = 0; i < m_enemy_koopa.size(); i++)
	{
		m_enemy_koopa[i]->TakeDamage();
	}

	m_screenshake = true;
	m_shake_time = SHAKE_DURATION;
	m_wobble = 0.0f;
}

void GameScreenLevel1::UpdateEnemyKoopa(float deltaTime, SDL_Event e)
{

	if (!m_enemy_koopa.empty())
	{
		int enemyIndexToDelete = -1;
		for (unsigned int i = 0; i < m_enemy_koopa.size(); i++)
		{
			//check if enemy is on bottom row
			if (m_enemy_koopa[i]->GetPosition().y > 300.0f)
			{
				//is enemy off screen to left or right?
				if (m_enemy_koopa[i]->GetPosition().x<(float)(m_enemy_koopa[i]->GetCollisionBox().width * 0.5f) || m_enemy_koopa[i]->GetPosition().x>SCREEN_WIDTH - (float)(m_enemy_koopa[i]->GetCollisionBox().width * 0.55f))
					m_enemy_koopa[i]->SetAlive(false);
			}
			//now update
			m_enemy_koopa[i]->Update(deltaTime, e);

			//check if collision with player
			if ((m_enemy_koopa[i]->GetPosition().y > 300.0f || m_enemy_koopa[i]->GetPosition().y <= 64.0f) && (m_enemy_koopa[i]->GetPosition().x<64.0f || m_enemy_koopa[i]->GetPosition().x>SCREEN_WIDTH - 96.0f))
			{
				//ignore collision if behind pipe
			}
			else
			{
				if (Collisions::Instance()->Circle(m_enemy_koopa[i], mario))
				{
					if (m_enemy_koopa[i]->GetInjured())
					{
						m_enemy_koopa[i]->SetAlive(false);
					}
					else
					{
						if (Collisions::Instance()->Circle(m_enemy_koopa[i], mario))
						{
							if (m_enemy_koopa[i]->GetInjured())
							{
								m_enemy_koopa[i]->SetAlive(false);
							}
							else
							{
								mario->SetAlive(false);								
								mario->SetPosition(Vector2D(500, 500));

							}
						}
						else if (Collisions::Instance()->Circle(m_enemy_koopa[i], luigi))
						{
							if (m_enemy_koopa[i]->GetInjured())
							{
								m_enemy_koopa[i]->SetAlive(false);
							}
							else
							{
								luigi->SetAlive(false);
								luigi->SetPosition(Vector2D(500, 500));
							}

						}
					}

				}
			}
			//if enemy is not alive then schedule for deletion
			if (!m_enemy_koopa[i]->GetAlive())
			{
				enemyIndexToDelete = i;
			}
		}
		//remove dead enemies, -1 each update

		if (enemyIndexToDelete != -1)
		{
			m_enemy_koopa.erase(m_enemy_koopa.begin() + enemyIndexToDelete);
		}

	}


}

void GameScreenLevel1::CreateKoopa(Vector2D position, FACING direction, float speed)
{
	CharacterKoopa* koopaCharacter = new CharacterKoopa(m_renderer, "Images/Koopa.png", position, m_level_map, direction, speed);

	m_enemy_koopa.push_back(koopaCharacter);

}

void GameScreenLevel1::WallWrapping(Character* character)
{
	if (character->GetPosition().x >= SCREEN_WIDTH - character->GetCollisionBox().width / 3)
	{
		character->SetPosition(Vector2D(0, character->GetPosition().y));
	}

	if (character->GetPosition().x < 0)
	{
		character->SetPosition(Vector2D(SCREEN_WIDTH - character->GetCollisionBox().width / 3, character->GetPosition().y));
	}
}