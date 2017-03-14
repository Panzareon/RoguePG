#include "MapFill.h"

#include <cstdlib>

MapFill::MapFill()
{
    //ctor

    m_maxTries = 50;

}

MapFill::~MapFill()
{
    //dtor
}

void MapFill::SetMap(Map* map)
{
    m_map = map;
    m_width = m_map->GetWidth();
    m_height = m_map->GetHeight();
    m_MGUtil.SetSize(m_width, m_height);
}

void MapFill::FillLayerByTiles(Map::TileType checkTile, int LayerId, int TileId, FillType fillType)
{
    for(int i = 0; i < m_width; i++)
    {
        for(int j = 0; j < m_height; j++)
        {
            if(m_map->GetTileType(i,j) == checkTile)
            {
                if(fillType == Simple)
                {
                    m_map->SetTileId(i,j,TileId,LayerId);
                }
                else if(fillType == WithAdjacent)
                {
                    int newTileIdTL = TileId;
                    if((i <= 0 && m_defaultType != checkTile) || (i > 0 && m_map->GetTileType(i-1,j) != checkTile))
                        newTileIdTL += 2;
                    if((j <= 0 && m_defaultType != checkTile) || (j > 0 && m_map->GetTileType(i,j-1) != checkTile))
                        newTileIdTL += 1;
                    if(newTileIdTL == TileId && i > 0 && j > 0)
                        if(m_map->GetTileType(i-1,j-1) != checkTile)
                            newTileIdTL +=4;

                    int newTileIdTR = TileId;
                    if((i >= m_width - 1 && m_defaultType != checkTile) || (i < m_width - 1 && m_map->GetTileType(i+1,j) != checkTile))
                        newTileIdTR += 2;
                    if((j <= 0 && m_defaultType != checkTile) || (j > 0 && m_map->GetTileType(i,j-1) != checkTile))
                        newTileIdTR += 1;
                    if(newTileIdTR == TileId && i < m_width - 1 && j > 0)
                        if(m_map->GetTileType(i+1,j-1) != checkTile)
                            newTileIdTR +=4;


                    int newTileIdBL = TileId;
                    if((i <= 0 && m_defaultType != checkTile) ||  (i > 0 && m_map->GetTileType(i-1,j) != checkTile))
                        newTileIdBL += 2;
                    if((j >= m_height - 1 && m_defaultType != checkTile) || (j < m_height - 1 && m_map->GetTileType(i,j+1) != checkTile))
                        newTileIdBL += 1;
                    if(newTileIdBL == TileId && i > 0 && j < m_height - 1)
                        if(m_map->GetTileType(i-1,j+1) != checkTile)
                            newTileIdBL +=4;

                    int newTileIdBR = TileId;
                    if((i >= m_width - 1 && m_defaultType != checkTile) || (i < m_width - 1 && m_map->GetTileType(i+1,j) != checkTile))
                        newTileIdBR += 2;
                    if((j >= m_height - 1 && m_defaultType != checkTile) || (j < m_height - 1 && m_map->GetTileType(i,j+1) != checkTile))
                        newTileIdBR += 1;
                    if(newTileIdBR == TileId && i < m_width - 1 && j < m_height - 1)
                        if(m_map->GetTileType(i+1,j+1) != checkTile)
                            newTileIdBR +=4;




                    m_map->SetTileId(i,j,newTileIdTL,newTileIdTR,newTileIdBL,newTileIdBR,LayerId);
                }
            }
        }
    }
}
void MapFill::FillLayerWallByTiles(Map::TileType checkTile, int LayerId, int LayerAboveHeroId, int TileId, int wallHeight, int yDelta)
{
    for(int i = 0; i < m_width; i++)
    {
        for(int j = 0; j < m_height; j++)
        {
            if(m_map->GetTileType(i,j) == checkTile && m_map->GetTileType(i,j-1) != checkTile)
            {
                int left = 0;
                int right = 0;
                if(m_map->GetTileType(i-1,j) != checkTile || m_map->GetTileType(i-1,j-1) == checkTile)
                    left = 1;
                if(m_map->GetTileType(i+1,j) != checkTile || m_map->GetTileType(i+1,j-1) == checkTile)
                    right = 1;

                int id = TileId;
                for(int k = yDelta; k < wallHeight + yDelta; k++)
                {
                    if(k == yDelta)
                    {
                        m_map->SetTileId(i, j-k,id + left, id + right, id + left, id + right, LayerId);
                        id += 2;
                    }
                    else
                        m_map->SetTileId(i, j-k,id + left, id + right, id + left, id + right, LayerAboveHeroId);
                }

            }
        }
    }
}
void MapFill::FillLayerWallAbove(Map::TileType checkTile, int LayerId, int TileId, int wallHeight)
{
    for(int i = 0; i < m_width; i++)
    {
        for(int j = wallHeight; j < m_height + wallHeight; j++)
        {
            if(m_map->GetTileType(i,j) == Map::Wall)
            {
                int newTileIdTL = TileId;
                if(m_map->GetTileType(i-1,j) == checkTile)
                    newTileIdTL += 2;
                if(m_map->GetTileType(i,j-1) == checkTile)
                    newTileIdTL += 1;
                if(newTileIdTL == TileId && i > 0 && j > 0)
                    if(m_map->GetTileType(i-1,j-1) == checkTile)
                        newTileIdTL +=4;

                int newTileIdTR = TileId;
                if(m_map->GetTileType(i+1,j) == checkTile)
                    newTileIdTR += 2;
                if(m_map->GetTileType(i,j-1) == checkTile)
                    newTileIdTR += 1;
                if(newTileIdTR == TileId && i < m_width - 1 && j > 0)
                    if(m_map->GetTileType(i+1,j-1) == checkTile)
                        newTileIdTR +=4;


                int newTileIdBL = TileId;
                if(m_map->GetTileType(i-1,j) == checkTile)
                    newTileIdBL += 2;
                if(m_map->GetTileType(i,j+1) == checkTile)
                    newTileIdBL += 1;
                if(newTileIdBL == TileId && i > 0 && j < m_height - 1)
                    if(m_map->GetTileType(i-1,j+1) == checkTile)
                        newTileIdBL +=4;

                int newTileIdBR = TileId;
                if(m_map->GetTileType(i+1,j) == checkTile)
                    newTileIdBR += 2;
                if(m_map->GetTileType(i,j+1) == checkTile)
                    newTileIdBR += 1;
                if(newTileIdBR == TileId && i < m_width - 1 && j < m_height - 1)
                    if(m_map->GetTileType(i+1,j+1) == checkTile)
                        newTileIdBR +=4;



                if(m_map->GetTileType(i,j-wallHeight) != Map::Wall || newTileIdBL != TileId || newTileIdBR != TileId || newTileIdTL != TileId || newTileIdTR != TileId)
                    m_map->SetTileId(i,j-wallHeight,newTileIdTL,newTileIdTR,newTileIdBL,newTileIdBR,LayerId);
            }
        }
    }
}


bool MapFill::CanBlockBeFilled(int x, int y)
{
    Map::TileType** toCheck = new Map::TileType*[3];
    int nrWall = 0;
    for(int i = 0; i < 3; i++)
    {
        toCheck[i] = new Map::TileType[3];
        for(int j = 0; j < 3; j++)
        {
            int x2 = x - 1 + i;
            int y2 = y - 1 + j;
            toCheck[i][j] = m_map->GetTileType(x2,y2);
            if(toCheck[i][j] != Map::Space)
            {
                nrWall++;
            }
        }
    }
    //Check Blockable States
    if(nrWall <= 1)
        return true;
    //Check if it would Block a Corner
    if(toCheck[0][1] != Map::Wall && toCheck[1][0] != Map::Wall)
        if(toCheck[0][0] != Map::Space)
            return false;
    if(toCheck[2][1] != Map::Wall && toCheck[1][0] != Map::Wall)
        if(toCheck[2][0] != Map::Space)
            return false;
    if(toCheck[0][1] != Map::Wall && toCheck[1][2] != Map::Wall)
        if(toCheck[0][2] != Map::Space)
            return false;
    if(toCheck[2][1] != Map::Wall && toCheck[1][2] != Map::Wall)
        if(toCheck[2][2] != Map::Space)
            return false;

    //Check direct path
    if(toCheck[0][1] != Map::Wall && toCheck[2][1] != Map::Wall)
    {
        bool ok = false;
        for(int i = 0; i < 3; i++)
        {
            int freeSpaces = 0;
            for(int j = 0; j < 3; j += 2)
            {
                if(toCheck[i][j] == Map::Space)
                    freeSpaces++;
            }
            if(freeSpaces >= 3)
                ok = true;
        }
        if(!ok)
            return false;

    }
    if(toCheck[1][0] != Map::Wall && toCheck[1][2] != Map::Wall)
    {
        bool ok = false;
        for(int i = 0; i < 3; i += 2)
        {
            int freeSpaces = 0;
            for(int j = 0; j < 3; j++)
            {
                if(toCheck[i][j] == Map::Space)
                    freeSpaces++;
            }
            if(freeSpaces >= 3)
                ok = true;
        }
        if(!ok)
            return false;

    }
    return true;

}

void MapFill::FillWithItems(int LayerId, int LayerAboveHeroId, int LayerWallDecoration, TileIndex index, int NrItems)
{
    int maxChance = 0.0f;
    for(unsigned int i = 0; i < m_chanceForTile[index].size(); i++)
    {
        maxChance += m_chanceForTile[index][i].GetChance();
    }

    for(int times = 0; times < NrItems; times++)
    {
        int i = 0;
        int newRand = rand() % maxChance;
        do
        {
            newRand -= m_chanceForTile[index][i].GetChance();
            i++;
        }
        while(newRand > 0);
        i--;
        FillItem* newItem = &(m_chanceForTile[index][i]);

        int x,y;
        int tryNr = 0;
        do
        {
            x = rand() % m_width;
            y = rand() % m_height;
            tryNr++;
        }
        while(!newItem->CanInsertAt(m_map, x, y, LayerId, LayerAboveHeroId) && tryNr < m_maxTries);

        if(tryNr < m_maxTries)
        {
            if(newItem->GetType() == FillItem::Blocking)
            {
                if(!CanBlockBeFilled(x,y))
                    continue;
            }
            newItem->Insert(m_map,x,y,LayerId, LayerAboveHeroId, LayerWallDecoration);
        }
    }
}

bool MapFill::PlaceItemAt(int LayerId, int LayerAboveHeroId, int LayerWallDecoration, TileIndex index, int x, int y, bool checkPlacement)
{
    int maxChance = 0.0f;
    for(unsigned int i = 0; i < m_chanceForTile[index].size(); i++)
    {
        maxChance += m_chanceForTile[index][i].GetChance();
    }

    int i = 0;
    int newRand = rand() % maxChance;
    do
    {
        newRand -= m_chanceForTile[index][i].GetChance();
        i++;
    }
    while(newRand > 0);
    i--;
    FillItem* newItem = &(m_chanceForTile[index][i]);

    if(checkPlacement && !newItem->CanInsertAt(m_map, x, y, LayerId, LayerAboveHeroId))
    {
        return false;
    }

    if(checkPlacement && newItem->GetType() == FillItem::Blocking)
    {
        if(!CanBlockBeFilled(x,y))
            return false;
    }
    newItem->Insert(m_map,x,y,LayerId, LayerAboveHeroId, LayerWallDecoration);
    return true;
}
