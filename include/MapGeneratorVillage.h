#ifndef MAPGENERATORVILLAGE_H
#define MAPGENERATORVILLAGE_H

#include "Map.h"
#include "Enums.h"
#include "MapGeneratorUtil.h"
#include "MapFillVillage.h"

class MapGeneratorVillage
{
    public:
        MapGeneratorVillage(Map* map, unsigned int seed, MapFillVillage* mapFill);
        virtual ~MapGeneratorVillage();

        void PlaceHouses(int houseWidth, int houseHeight, int nrHouses);
        void AddHouse(int x, int y, int width, int height);
        bool IsRoomFree(int x, int y, int width, int height);

        void PlaceStreets();

        int StartStreet(int xStart, int yStart, Enums::Direction, bool placeStreet = true);

        std::pair<int,int> PopDoor();

    protected:

    private:
        int m_width;
        int m_height;

        std::vector<std::pair<int,int> > m_doors;

        int m_spaceBetweenHouses;

        MapGeneratorUtil m_MGUtil;
        Map* m_map;
        MapFillVillage* m_mapFill;
};

#endif // MAPGENERATORVILLAGE_H
