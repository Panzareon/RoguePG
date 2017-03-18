#ifndef MAP_H
#define MAP_H

#include "TileMap.h"
#include <vector>
#include <map>
#include "SFML/Graphics.hpp"
#include "MapRoom.h"

class Map
{
    public:


        Map(int width, int height);
        virtual ~Map();
        void init(unsigned int layerNr);

        void SetTileToType(unsigned int x, unsigned int y, int type);
        int GetTileType(unsigned int x, unsigned int y);
        void AddCollidingType(int type);


        void SetRoomNr(unsigned int x, unsigned int y,  int roomNr);
        int GetRoomNr(unsigned int x, unsigned int y);
        void RoomsAreAdjacent(int roomNr1, int roomNr2);
        std::map<int, MapRoom>* GetAllRooms();

        void writeToTileMap(TileMap& in, int layerId, sf::Color color = sf::Color::White);

        void SetTileId(unsigned int x, unsigned int y, int TileIdTL, int TileIdTR, int TileIdBL, int TileIdBR, int layerId);
        void SetTileId(unsigned int x, unsigned int y, int TileId, int layerId);

        //Get Top Left Tile Id of given Position
        int GetTileId(unsigned int x, unsigned int y, int layerId);

        bool DoesCollide(sf::Rect<float> rect);
        bool DoesCollide(unsigned int x, unsigned int y);
        //Check if a Line collides
        bool DoesCollide(unsigned int fromX, unsigned int fromY, unsigned int toX, unsigned int toY);


        int GetWidth();
        int GetHeight();

        int m_startX;
        int m_startY;
        int m_startRoomNr;

        int m_endX;
        int m_endY;
        int m_endRoomNr;
    protected:
    private:
        int** m_tiles;
        std::vector<int> m_collidingTiles;
        int** m_roomNr;
        int m_maxRoomNr;
        std::vector<int**> m_layers;
        std::map<int, MapRoom> m_rooms;
        unsigned int m_nrLayers;
        unsigned int m_width;
        unsigned int m_height;

};

#endif // MAP_H
