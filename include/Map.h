#ifndef MAP_H
#define MAP_H

#include "TileMap.h"
#include <vector>
#include "SFML/Graphics.hpp"

class Map
{
    public:
        enum TileType {Wall, Space, InteractableWall, BlockingItem, WalkthroughItem};


        Map(int width, int height);
        virtual ~Map();
        void init(int layerNr);
        bool IsTileWall(unsigned int x, unsigned int y);
        void SetTileToWall(unsigned int x, unsigned int y);
        void SetTileToSpace(unsigned int x, unsigned int y);

        void SetTileToType(unsigned int x, unsigned int y, TileType type);
        TileType GetTileType(unsigned int x, unsigned int y);


        void SetRoomNr(unsigned int x, unsigned int y,  int roomNr);
        int GetRoomNr(unsigned int x, unsigned int y);

        void writeToTileMap(TileMap& in, int layerId, sf::Color color = sf::Color::White);

        void SetTileId(unsigned int x, unsigned int y, int TileIdTL, int TileIdTR, int TileIdBL, int TileIdBR, int layerId);
        void SetTileId(unsigned int x, unsigned int y, int TileId, int layerId);

        //Get Top Left Tile Id of given Position
        int GetTileId(unsigned int x, unsigned int y, int layerId);

        bool DoesCollide(sf::Rect<float> rect);
        bool DoesCollide(unsigned int x, unsigned int y);


        int GetWidth();
        int GetHeight();

        int m_startX;
        int m_startY;
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