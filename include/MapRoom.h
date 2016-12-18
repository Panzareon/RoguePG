#ifndef MAPROOM_H
#define MAPROOM_H

#include <vector>

class MapRoom
{
    public:
        MapRoom(int roomId);
        virtual ~MapRoom();

        int GetNumberOfAdjacentRooms();

        void AddPosition(int x, int y);
        std::pair<int,int>* GetRandomPosition();

    protected:
        std::vector<MapRoom*> m_adjacentRooms;

        std::vector<std::pair<int,int>> m_positions;

        int m_roomId;

    private:
};

#endif // MAPROOM_H
