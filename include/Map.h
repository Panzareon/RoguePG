#ifndef MAP_H
#define MAP_H

#include "TileMap.h"
#include <vector>

class Map
{
    public:
        enum TileType {Wall, Space};


        Map(int width, int height, int layerNr);
        virtual ~Map();
        bool IsTileWall(unsigned int x, unsigned int y);
        void SetTileToWall(unsigned int x, unsigned int y);
        void SetTileToSpace(unsigned int x, unsigned int y);
        TileType GetTileType(unsigned int x, unsigned int y);

        void SetRoomNr(unsigned int x, unsigned int y,  int roomNr);
        int GetRoomNr(unsigned int x, unsigned int y);

        void writeToTileMap(TileMap& in, int layerId);

        void SetTileId(unsigned int x, unsigned int y, int TileIdTL, int TileIdTR, int TileIdBL, int TileIdBR, int layerId);


        int GetWidth();
        int GetHeight();
    protected:
    private:
        int** m_tiles;
        int** m_roomNr;
        std::vector<int**> m_layers;
        int m_nrLayers;
        int m_width;
        int m_height;

};

#endif // MAP_H
