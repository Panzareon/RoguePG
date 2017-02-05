#ifndef MAPGENERATOR_H
#define MAPGENERATOR_H

#include "TileMap.h"
#include "MapGeneratorUtil.h"
#include "Map.h"

//A class to generate Basic Layout of Maps
class MapGenerator
{
    public:
        MapGenerator(Map* map, unsigned int seed = 0);
        virtual ~MapGenerator();

        void CellularAutomata(float startPercent);
        //Faster Generation for Maps > than 200 x 200
        void FasterCellularAutomata(float startPercent);
        void CellularAutomataStart(float startPercent);
        void CellularAutomataStep(int minWallTiles, int orMaxWallTiles = -1, float chanceAtThreshhold = 1.0f, bool onlyChangeToWall = false);

        void MorphologicalCloseOperator();

        //has really bad Performance, not recommended to use with Maps larger than 200x200
        void ConnectAllRooms(bool straight, int maxRemovedTiles = 10);

        void RemoveUnconnectedRooms();

        void ConnectTwoPoints(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2);


        void DigTunnel(int fromX, int fromY, int toX, int toY);

        void NumberRooms();

        void PlaceStartingAndEndPosition();
        std::pair<int,int>* GetFreePosition();

    protected:
    private:
        int m_width;
        int m_height;

        MapGeneratorUtil m_MGUtil;
        Map* m_map;


        //Connect from given tile to already checked
        void CheckTiles(int** checkArray, int x, int y, bool straight);



};

#endif // MAPGENERATOR_H
