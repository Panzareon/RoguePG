#ifndef MAPGENERATORUTIL_H
#define MAPGENERATORUTIL_H

#include "SFML/Graphics.hpp"

class MapGeneratorUtil
{
    public:
        MapGeneratorUtil(int width, int height);
        virtual ~MapGeneratorUtil();

        int SetTilesToChecked(int** checkArray, int x, int y, int fromId = 0, int toId = 1, bool useToId = false);
        int GetNumberOfConnected(int** checkArray, int x, int y, int checkId, int maxCount = -1);
        sf::Vector2f GetMidpointOf(int** tiles, int checkId);
        sf::Vector2u GetClosestToPoint(int** tiles, int checkId, int x, int y);

        //direction from 0 (east) to 7 (south-east)
        sf::Vector2u GetClosestInDirection(int** tiles, int checkId, int x, int y, int direction);

        bool WouldPointBlockPath(int** tiles, int x, int y, int checkId);
    protected:
    private:


        int m_width;
        int m_height;
};

#endif // MAPGENERATORUTIL_H
