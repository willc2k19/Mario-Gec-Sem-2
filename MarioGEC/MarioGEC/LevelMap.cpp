#include "LevelMap.h"

//0 = empty space & 1 = occupied space in maps

LevelMap::LevelMap(int map[MAP_HEIGHT][MAP_WIDTH])
{
	//allocate memory for level map
	m_map = new int* [MAP_HEIGHT];
	for (unsigned int i = 0; i < MAP_HEIGHT; i++)
	{
		m_map[i] = new int[MAP_WIDTH];
	}

	//populate array
	for (unsigned int i = 0; i < MAP_HEIGHT;i++)
	{
		for (unsigned int j = 0; j < MAP_HEIGHT; j++)
		{
			m_map[i][j] = map[i][j];
		}
	}
}

LevelMap::~LevelMap()
{
	//delete array elements
	for (unsigned int i = 0; i < MAP_HEIGHT;i++)
	{
		delete[] m_map[i];
	}
	delete[] m_map;
}

int LevelMap::GetTileAt(unsigned int h, unsigned int w)
{
	if (h < MAP_HEIGHT && w < MAP_WIDTH)
	{
		return m_map[h][w];
	}
	return 0;
}

void LevelMap::ChangeTileAt(unsigned int row, unsigned int column, unsigned int new_value)
{
	if (row < MAP_HEIGHT && column < MAP_WIDTH)
	{
		m_map[row][column] = new_value;
	}
}