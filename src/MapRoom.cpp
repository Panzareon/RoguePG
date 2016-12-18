#include "MapRoom.h"
#include <random>

MapRoom::MapRoom(int roomId)
{
    //ctor
    m_roomId = roomId;
}

MapRoom::~MapRoom()
{
    //dtor
}

int MapRoom::GetNumberOfAdjacentRooms()
{
    return m_adjacentRooms.size();
}

void MapRoom::AddPosition(int x, int y)
{
    m_positions.push_back(std::pair<int,int>(x,y));
}

std::pair<int,int>* MapRoom::GetRandomPosition()
{
    return &m_positions[rand() % m_positions.size()];
}
