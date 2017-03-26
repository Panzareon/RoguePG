#ifndef SCENEMANAGERMOVEABLE_H
#define SCENEMANAGERMOVEABLE_H

#include <SceneManager/SceneManager.h>
#include "MapGeneration/Map.h"
#include "SceneGraph/AnimatedNode.h"
#include "MapGeneration/MapEvent.h"
#include <vector>

#include <cereal/types/base_class.hpp>

class SceneManagerMoveable : public SceneManager
{
    public:
        SceneManagerMoveable();
        SceneManagerMoveable(int tileWidth, int tileHeight);
        virtual ~SceneManagerMoveable();
        virtual void Tick();

        void Init();

        template<class Archive>
        void save(Archive & archive, std::uint32_t const version) const
        {
            int height = m_map.GetHeight();
            int width = m_map.GetWidth();
            float heroX = m_hero->getBoundingBox().left;
            float heroY = m_hero->getBoundingBox().top;
            archive(cereal::base_class<SceneManager>( this ), width, height, heroX, heroY);
        }


        template<class Archive>
        void load(Archive & archive, std::uint32_t const version)
        {
            int height;
            int width;
            archive(cereal::base_class<SceneManager>( this ), width, height, m_heroX, m_heroY);
            m_map.InitSize(width, height);
            Init();
            m_newHeroPos = true;
        }
    protected:
        void UpdateMinimap();
        void UpdateCamPosition();
        Map m_map;
        AnimatedNode* m_hero;
        bool m_newHeroPos;
        float m_heroX;
        float m_heroY;
        Enums::Direction m_heroDirection;
        std::vector<MapEvent*> m_events;

        int m_minViewPosX;
        int m_minViewPosY;
        int m_maxViewPosX;
        int m_maxViewPosY;

        TileMap* m_tileMap;
        TileMap* m_tileMapItems;
        TileMap* m_tileMapAboveHero;
        TileMap* m_tileMapAboveWall;
        TileMap* m_tileMapWallDecoration;

        float m_minimapScale;
        Node* m_minimapNode;
        AnimatedNode* m_minimapPlayer;
        sf::Image m_minimap;
        sf::Texture m_minimapTexture;
        float m_heroMoved;
        int m_minimapViewRange;
        std::vector<sf::Color> m_minimapColor;


        #ifdef DEBUG_FLAG
        Node* m_roomNumberNode;
        TileMap* m_tileMapRoomNumber;
        #endif // DEBUG_FLAG


        Node* m_belowHero;
        Node* m_eventLayer;
        Node* m_aboveHero;
    private:
};

#endif // SCENEMANAGERMOVEABLE_H
