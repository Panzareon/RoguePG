#ifndef MAPGENERATORVILLAGE_H
#define MAPGENERATORVILLAGE_H

#include "Map.h"
#include "Enums.h"
#include "MapGeneratorUtil.h"

class MapGeneratorVillage
{
    public:
        MapGeneratorVillage(Map* map, unsigned int seed);
        virtual ~MapGeneratorVillage();

        void PlaceHouses(int houseWidth, int houseHeight, int nrHouses);
        void AddHouse(int x, int y, int width, int height);
        bool IsRoomFree(int x, int y, int width, int height);

        void StartStreet(int xStart, int yStart, Enums::Direction);

    protected:

    private:
        int m_width;
        int m_height;

        int m_spaceBetweenHouses;

        MapGeneratorUtil m_MGUtil;
        Map* m_map;
};

#endif // MAPGENERATORVILLAGE_H
