#include "MapFill.h"

MapFill::MapFill(Map* map) : m_MGUtil(map->GetWidth(), map->GetHeight())
{
    //ctor
    m_map = map;

    m_width = m_map->GetWidth();
    m_height = m_map->GetHeight();
}

MapFill::~MapFill()
{
    //dtor
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
                    m_map->SetTileId(i,j,TileId,TileId,TileId,TileId,LayerId);
                }
                else if(fillType == WithAdjacent)
                {
                    int newTileIdTL = TileId;
                    if(i <= 0 || m_map->GetTileType(i-1,j) != checkTile)
                        newTileIdTL += 2;
                    if(j <= 0 || m_map->GetTileType(i,j-1) != checkTile)
                        newTileIdTL += 1;
                    if(newTileIdTL == TileId && i > 0 && j > 0)
                        if(m_map->GetTileType(i-1,j-1) != checkTile)
                            newTileIdTL +=4;

                    int newTileIdTR = TileId;
                    if(i >= m_width - 1 || m_map->GetTileType(i+1,j) != checkTile)
                        newTileIdTR += 2;
                    if(j <= 0 || m_map->GetTileType(i,j-1) != checkTile)
                        newTileIdTR += 1;
                    if(newTileIdTR == TileId && i < m_width - 1 && j > 0)
                        if(m_map->GetTileType(i+1,j-1) != checkTile)
                            newTileIdTR +=4;


                    int newTileIdBL = TileId;
                    if(i <= 0 || m_map->GetTileType(i-1,j) != checkTile)
                        newTileIdBL += 2;
                    if(j >= m_height - 1 || m_map->GetTileType(i,j+1) != checkTile)
                        newTileIdBL += 1;
                    if(newTileIdBL == TileId && i > 0 && j < m_height - 1)
                        if(m_map->GetTileType(i-1,j+1) != checkTile)
                            newTileIdBL +=4;

                    int newTileIdBR = TileId;
                    if(i >= m_width - 1 || m_map->GetTileType(i+1,j) != checkTile)
                        newTileIdBR += 2;
                    if(j >= m_height - 1 || m_map->GetTileType(i,j+1) != checkTile)
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
