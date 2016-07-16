#include "MapGenerator.h"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <limits>
#include <cmath>

MapGenerator::MapGenerator(Map* map, unsigned int seed) : m_MGUtil(map->GetWidth(), map->GetHeight())
{
    //ctor
    m_width = map->GetWidth();
    m_height = map->GetHeight();
    m_map = map;

    if(seed == 0)
        std::srand(std::time(0));
    else
        std::srand(seed);
}

MapGenerator::~MapGenerator()
{
    //dtor
}

void MapGenerator::CellularAutomata(float startPercent)
{
    std::cout << "Starting Generation" << std::endl;
    CellularAutomataStart(startPercent);
    for(int i = 0; i < 5; i++)
    {
        CellularAutomataStep(5, 1, 0.67f);
    }
    std::cout << "Connecting Rooms" << std::endl;
    ConnectAllRooms(true);
    for(int i = 0; i < 3; i++)
    {
        std::cout << "Finishing Up " << (i + 1) << " of 3" <<std::endl;
        CellularAutomataStep(5);
        ConnectAllRooms(false);
    }


          //AlternativeImplementation
/*            generator.CellularAutomataStart(0.45f);
            for(int i = 0; i < 5; i++)
            {
                generator.CellularAutomataStep(5,1,0.67f);
            }
            for(int i = 0; i < 3; i++)
            {
                generator.CellularAutomataStep(5);
            }

            generator.ConnectTwoPoints(5,5,m_width - 5,m_height - 5);

            generator.RemoveUnconnectedRooms();*/
}

void MapGenerator::CellularAutomataStart(float startPercent)
{
    for(int i = 0; i < m_width; i++)
    {
        for(int j = 0; j < m_height; j++)
        {
            if(std::rand()/((float) RAND_MAX) < startPercent)
                m_map->SetTileToWall(i,j);
            else
                m_map->SetTileToSpace(i,j);
        }
    }
}

void MapGenerator::CellularAutomataStep(int minWallTiles, int orMaxWallTiles, float chanceAtThreshhold, bool onlyChangeToWall)
{
    //new Array for the new map

    int** newTiles = new int*[m_width];
    for(int i = 0; i < m_width; i++)
        newTiles[i] = new int[m_height];


    bool setWall;
    int newNrWall=0;
    int newNrSpace=0;
    int nrWall;
    for(int i = 0; i < m_width; i++)
    {
        for(int j = 0; j < m_height; j++)
        {
            nrWall = 0;
            for(int x = i - 1; x <= i + 1; x ++)
            {
                for(int y = j - 1; y <= j + 1; y++)
                {
                    if(x < 0 || y < 0 || x >= m_width || y >= m_height)
                    {
                        nrWall++;
                    }
                    else if(m_map->IsTileWall(x,y))
                    {
                        nrWall++;
                    }
                }
            }

            if((onlyChangeToWall && m_map->IsTileWall(i,j)) || nrWall > minWallTiles || nrWall < orMaxWallTiles)
            {
                setWall = true;
            }
            else if(nrWall == minWallTiles || nrWall == orMaxWallTiles)
            {
                if(chanceAtThreshhold >= 1.0f)
                {
                    setWall = true;
                }
                else if(chanceAtThreshhold <= 0.0f)
                {
                    setWall = false;
                }
                else
                {
                    setWall = std::rand()/((float) RAND_MAX) < chanceAtThreshhold;
                }
            }
            else
            {
                setWall = false;
            }
            if(setWall)
            {
                newTiles[i][j] = 0;
                newNrWall++;
            }
            else
            {
                newTiles[i][j] = 1;
                newNrSpace++;
            }
        }
    }
    for(int i = 0; i < m_width; i++)
        for(int j = 0; j < m_height; j++)
        {
            if(newTiles[i][j] == 0)
                m_map->SetTileToWall(i,j);
            else
                m_map->SetTileToSpace(i,j);
        }
}


void MapGenerator::ConnectAllRooms(bool straight, int maxRemovedTiles)
{
    //flags for every Tile: 0 = not checked; 1 = checked; 2 = wall
    int** checkedTiles = new int*[m_width];
    for(int i = 0; i < m_width; i++)
    {
        checkedTiles[i] = new int[m_height];
        for(int j = 0; j < m_height; j++)
        {
            if(m_map->IsTileWall(i,j))
                checkedTiles[i][j] = 2;
            else
                checkedTiles[i][j] = 0;
        }
    }
    bool finished = false;
    //To have most of the Rooms in the starting list: Start with at least 1/4 of all Tiles must be checked
    int mod = 4;
    do
    {
        int checkX = std::rand() % m_width;
        int checkY = std::rand() % m_height;

        if(checkedTiles[checkX][checkY] == 0)
        {
            if(m_MGUtil.GetNumberOfConnected(checkedTiles, checkX, checkY, 0) < m_width * m_height / mod)
            {
                mod++;
            }
            else
            {
                m_MGUtil.SetTilesToChecked(checkedTiles, checkX, checkY);
                finished = true;
            }
        }

    }
    while(!finished);


    int remainingTiles;

    do
    {
        int checkX = std::rand() % m_width;
        int checkY = std::rand() % m_height;

        if(checkedTiles[checkX][checkY] == 0)
        {
            CheckTiles(checkedTiles, checkX, checkY, straight);
        }

        finished = true;
        remainingTiles = 0;
        for(int i = 0; i < m_width; i++)
        {
            for(int j = 0; j < m_height; j++)
            {
                if(checkedTiles[i][j] == 0)
                    remainingTiles++;
                if(remainingTiles > maxRemovedTiles)
                    finished = false;
            }
        }
    }
    while(!finished);

    for(int i = 0; i < m_width; i++)
    {
        for(int j = 0; j < m_height; j++)
        {
            if(checkedTiles[i][j] == 0)
                m_map->SetTileToWall(i,j);
        }
    }


    for(int i = 0; i < m_width; i++)
        delete[] checkedTiles[i];
    delete[] checkedTiles;
}
void MapGenerator::RemoveUnconnectedRooms()
{

    int** checkedTiles = new int*[m_width];
    for(int i = 0; i < m_width; i++)
    {
        checkedTiles[i] = new int[m_height];
        for(int j = 0; j < m_height; j++)
        {
            if(m_map->IsTileWall(i,j))
                checkedTiles[i][j] = 2;
            else
                checkedTiles[i][j] = 0;
        }
    }
    bool finished = false;
    //To have most of the Rooms in the starting list: Start with at least 1/4 of all Tiles must be checked
    int mod = 4;
    do
    {
        int checkX = std::rand() % m_width;
        int checkY = std::rand() % m_height;

        if(checkedTiles[checkX][checkY] == 0)
        {
            if(m_MGUtil.SetTilesToChecked(checkedTiles, checkX, checkY) < m_width * m_height / mod)
            {
                for(int i = 0; i < m_width; i++)
                {
                    for(int j = 0; j < m_height; j++)
                    {
                        if(m_map->IsTileWall(i,j))
                            checkedTiles[i][j] = 2;
                        else
                            checkedTiles[i][j] = 0;
                    }
                }
                mod++;
            }
            else
            {
                finished = true;
            }
        }

    }
    while(!finished);

    for(int i = 0; i < m_width; i++)
        for(int j = 0; j < m_height; j++)
        {
            if(checkedTiles[i][j] == 0)
                m_map->SetTileToWall(i,j);
        }


    for(int i = 0; i < m_width; i++)
        delete[] checkedTiles[i];
    delete[] checkedTiles;
}


void MapGenerator::ConnectTwoPoints(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2)
{
    m_map->SetTileToSpace(x1,y1);
    m_map->SetTileToSpace(x2,y2);
    //flags for every Tile: 0 = not checked; 1 = checkedStartPoint; 2 = wall; 3 = checkedEndPoint
    int** checkedTiles = new int*[m_width];
    for(int i = 0; i < m_width; i++)
    {
        checkedTiles[i] = new int[m_height];
        for(int j = 0; j < m_height; j++)
        {
            if(m_map->IsTileWall(i,j))
                checkedTiles[i][j] = 2;
            else
                checkedTiles[i][j] = 0;
        }
    }

    m_MGUtil.SetTilesToChecked(checkedTiles, x1, y1);
    //Check if already connected
    if(checkedTiles[x2][y2] == 0)
    {
        m_MGUtil.SetTilesToChecked(checkedTiles, x2, y2, 0, 3);

        bool finished = false;
        do
        {
            sf::Vector2u closestFrom1 = m_MGUtil.GetClosestToPoint(checkedTiles,3, x1,y1);
            sf::Vector2u closestFrom2 = m_MGUtil.GetClosestToPoint(checkedTiles,1, closestFrom1.x, closestFrom1.y);
            sf::Vector2u newMidpoint = m_MGUtil.GetClosestToPoint(checkedTiles, 0, closestFrom1.x, closestFrom1.y);

            float distance = sqrtf((closestFrom1.x - closestFrom2.x) * (closestFrom1.x - closestFrom2.x) + (closestFrom1.y - closestFrom2.y) * (closestFrom1.y - closestFrom2.y));
            float distance2 = sqrtf((closestFrom1.x - newMidpoint.x) * (closestFrom1.x - newMidpoint.x) + (closestFrom1.y - newMidpoint.y) * (closestFrom1.y - newMidpoint.y));
            std::cout << distance << " vs. " << distance2 << std::endl;

            if((newMidpoint.x == 0 && newMidpoint.y == 0) || distance < distance2)
            {
                DigTunnel(closestFrom1.x, closestFrom1.y, closestFrom2.x, closestFrom2.y);
                finished = true;
            }
            else
            {
                DigTunnel(closestFrom1.x, closestFrom1.y, newMidpoint.x, newMidpoint.y);


                for(int i = 0; i < m_width; i++)
                {
                    for(int j = 0; j < m_height; j++)
                    {
                        if(m_map->IsTileWall(i,j))
                            checkedTiles[i][j] = 2;
                        else
                            checkedTiles[i][j] = 0;
                    }
                }
                m_MGUtil.SetTilesToChecked(checkedTiles, x1, y1);
                //should not happen....
                if(checkedTiles[x2][y2] == 1)
                    finished = true;
                m_MGUtil.SetTilesToChecked(checkedTiles, x2, y2, 0, 3);
            }
        }
        while (!finished);
    }


    for(int i = 0; i < m_width; i++)
        delete[] checkedTiles[i];
    delete[] checkedTiles;
}
void MapGenerator::NumberRooms()
{
    //flags for every Tile: 0 = not checked; 1 = wall; 2 = outer line of Room; 3 or greater Room Nr
    int** checkedTiles = new int*[m_width];
    for(int i = 0; i < m_width; i++)
    {
        checkedTiles[i] = new int[m_height];
        for(int j = 0; j < m_height; j++)
        {
            if(m_map->IsTileWall(i,j))
                checkedTiles[i][j] = 1;
            else
                checkedTiles[i][j] = 0;
        }
    }

    std::vector<sf::Vector2u> rooms;
    int nrWall;
    int roomId = 3;
    for(int d = 5; d >= 0; d--)
    {
        for(int i = 0; i < m_width; i++)
        {
            for(int j = 0; j < m_height; j++)
            {
                if(!m_map->IsTileWall(i,j))
                {
                    nrWall = 0;
                    for(int x = i - d; x <= i + d; x ++)
                    {
                        for(int y = j - d; y <= j + d; y++)
                        {
                            if(x < 0 || y < 0 || x >= m_width || y >= m_height)
                            {
                                nrWall++;
                            }
                            else if(m_map->IsTileWall(x,y))
                            {
                                nrWall++;
                            }
                        }
                    }
                    if(nrWall >= 1)
                    {
                        checkedTiles[i][j] = 2;
                    }
                }
            }
        }


        int** lastTiles = new int*[m_width];
        for(int i = 0; i < m_width; i++)
        {
            lastTiles[i] = new int[m_height];
        }
        bool finished = false;
        while(!finished)
        {
            finished = true;
            for(int i = 0; i < m_width; i++)
            {
                for(int j = 0; j < m_height; j++)
                {
                    lastTiles[i][j] = checkedTiles[i][j];
                }
            }
            for(int i = 0; i < m_width; i++)
            {
                for(int j = 0; j < m_height; j++)
                {
                    if(checkedTiles[i][j] == 0)
                    {
                        int room = 0;
                        int room1 = 0;
                        int room1nr = 0;
                        int room2 = 0;
                        int room2nr = 0;
                        for(int x = i - 1; x <= i + 1; x ++)
                        {
                            for(int y = j - 1; y <= j + 1; y++)
                            {
                                if(x >= 0 && y >= 0 && x < m_width && y < m_height)
                                {
                                    room = lastTiles[x][y];
                                    if(room > 2)
                                    {
                                        if(room1 == 0 || room1 == room)
                                        {
                                            room1 = room;
                                            room1nr++;
                                        }
                                        else if(room2 == 0 || room2 == room)
                                        {
                                            room2 = room;
                                            room2nr++;
                                        }
                                    }
                                }
                            }
                        }
                        if(room1 != 0)
                        {
                            finished = false;
                            if(room1nr > room2nr)
                            {
                                checkedTiles[i][j] = room1;
                            }
                            else
                            {
                                checkedTiles[i][j] = room2;
                            }
                        }
                    }
                }
            }
        }
        for(int i = 0; i < m_width; i++)
            delete[] lastTiles[i];
        delete[] lastTiles;




        finished = false;
        do
        {
            int checkX = std::rand() % m_width;
            int checkY = std::rand() % m_height;

            if(checkedTiles[checkX][checkY] == 0)
            {
                int room = 0;
                int room1 = 0;
                int room1nr = 0;
                int room2 = 0;
                int room2nr = 0;
                for(int x = checkX - 1; x <= checkX + 1; x ++)
                {
                    for(int y = checkY - 1; y <= checkY + 1; y++)
                    {
                        if(x >= 0 && y >= 0 && x < m_width && y < m_height)
                        {
                            room = checkedTiles[x][y];
                            if(room > 2)
                            {
                                if(room1 == 0 || room1 == room)
                                {
                                    room1 = room;
                                    room1nr++;
                                }
                                else if(room2 == 0 || room2 == room)
                                {
                                    room2 = room;
                                    room2nr++;
                                }
                            }
                        }
                    }
                }
                if(room1 != 0)
                {
                    finished = false;
                    if(room1nr > room2nr)
                    {
                        checkedTiles[checkX][checkY] = room1;
                    }
                    else
                    {
                        checkedTiles[checkX][checkY] = room2;
                    }
                }
                else
                {
                    m_MGUtil.SetTilesToChecked(checkedTiles, checkX, checkY, 0, roomId);
                    rooms.push_back(sf::Vector2u(checkX, checkY));
                    roomId++;
                }
            }
            finished = true;
            for(int i = 0; i < m_width && finished; i++)
            {
                for(int j = 0; j < m_height && finished; j++)
                {
                    if(checkedTiles[i][j] == 0)
                    {
                        finished = false;
                    }
                }
            }

        }
        while(!finished);




        for(int i = 0; i < m_width && finished; i++)
        {
            for(int j = 0; j < m_height && finished; j++)
            {
                if(checkedTiles[i][j] == 2)
                {
                    checkedTiles[i][j] = 0;
                }
            }
        }




    }


    for(int i = 0; i < m_width; i++)
        for(int j = 0; j < m_height; j++)
        {
            if(checkedTiles[i][j] > 2)
                m_map->SetRoomNr(i,j, checkedTiles[i][j] - 2);
            else
                m_map->SetRoomNr(i,j,0);
        }


    for(int i = 0; i < m_width; i++)
        delete[] checkedTiles[i];
    delete[] checkedTiles;
}

void MapGenerator::DigTunnel(int fromX, int fromY, int toX, int toY)
{
    if(abs(fromX - toX) > abs(fromY - toY))
    {
        if(fromX > toX)
        {
            int x = toX;
            int y = toY;
            toX = fromX;
            toY = fromY;
            fromX = x;
            fromY = y;
        }

        int yStep = 1;
        if(fromY > toY)
            yStep = -1;

        int dX = abs(toX - fromX);
        int dY = abs(toY - fromY);
        int fehler = dX / 2;
        int y = fromY;
        for(int x = fromX; x <= toX; x++)
        {
            m_map->SetTileToSpace(x,y);
            fehler -= dY;
            if(fehler < 0)
            {
                fehler += dX;
                y += yStep;
                m_map->SetTileToSpace(x,y);
            }
        }
    }
    else
    {
        if(fromY > toY)
        {
            int x = toX;
            int y = toY;
            toX = fromX;
            toY = fromY;
            fromX = x;
            fromY = y;
        }

        int xStep = 1;
        if(fromX > toX)
            xStep = -1;

        int dX = abs(toX - fromX);
        int dY = abs(toY - fromY);
        int fehler = dY / 2;
        int x = fromX;
        for(int y = fromY; y <= toY; y++)
        {
            m_map->SetTileToSpace(x,y);
            fehler -= dX;
            if(fehler < 0)
            {
                fehler += dY;
                x += xStep;
                m_map->SetTileToSpace(x,y);
            }
        }
    }
}


void MapGenerator::CheckTiles(int** checkArray, int x, int y, bool straight)
{
    int direction = std::rand() % 4;

    int xChange = 0;
    int yChange = 0;
    if(direction == 0)
    {
        yChange = -1;
    }
    else if(direction == 1)
    {
        yChange = 1;
    }
    else if(direction == 2)
    {
        xChange = -1;
    }
    else
    {
        xChange = 1;
    }

    //go as long as unchecked Space
    while(x > 0 && y > 0 && x < m_width - 1 && y < m_height - 1 && checkArray[x][y] == 0)
    {
        x += xChange;
        y += yChange;
    }
    if(checkArray[x][y] != 0)
    {
        if(straight)
        {
            //Go as long as there is a Wall
            while(x > 0 && y > 0 && x < m_width - 1 && y < m_height - 1 && checkArray[x][y] == 2)
            {
                x += xChange;
                y += yChange;
            }
            //if after Wall is checked Space
            if(checkArray[x][y] == 1)
            {
                do
                {
                    x -= xChange;
                    y -= yChange;
                    checkArray[x][y] = 0;
                    m_map->SetTileToSpace(x,y);
                }
                while(x > 0 && y > 0 && x < m_width - 1 && y < m_height - 1 && checkArray[x - xChange][y - yChange] != 0);
                m_MGUtil.SetTilesToChecked(checkArray,x,y);
            }
        }
        else
        {
            checkArray[x][y] = 0;
            m_map->SetTileToSpace(x,y);
            if(x > 0 && y > 0 && x < m_width - 1 && y < m_height - 1 )
                if(checkArray[x-1][y] == 1 || checkArray[x+1][y] == 1 || checkArray[x][y-1] == 1 || checkArray[x][y+1] == 1)
                    m_MGUtil.SetTilesToChecked(checkArray,x,y);
        }
    }
}


