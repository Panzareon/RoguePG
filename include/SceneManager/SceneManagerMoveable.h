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
            sf::FloatRect rect = m_hero->getGlobalBoundingBox();
            sf::FloatRect local = m_hero->getBoundingBox();
            float heroX = rect.left - local.left;
            float heroY = rect.top - local.top;
            archive(cereal::base_class<SceneManager>( this ), width, height, heroX, heroY, m_events);
        }


        template<class Archive>
        void load(Archive & archive, std::uint32_t const version)
        {
            int height;
            int width;
            archive(cereal::base_class<SceneManager>( this ), width, height, m_heroX, m_heroY, m_events);
            m_newHeroPos = true;
            m_map.InitSize(width, height);
            Init();
        }
    protected:
        void UpdateMinimap();
        void UpdateCamPosition();
        bool m_completedMap;
        Map m_map;
        AnimatedNode* m_hero;
        bool m_newHeroPos;
        float m_heroX;
        float m_heroY;
        Enums::Direction m_heroDirection;
        std::vector<std::shared_ptr<MapEvent> > m_events;

        int m_minViewPosX;
        int m_minViewPosY;
        int m_maxViewPosX;
        int m_maxViewPosY;

        TileMap* m_tileMap;
        TileMap* m_tileMapItems;
        TileMap* m_tileMapAboveHero;
        TileMap* m_tileMapAboveWall;
        TileMap* m_tileMapWallDecoration;
        TileMap* m_tileMapBelowGround;
        TileMap* m_tileMapBelowGroundDecoration;

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
