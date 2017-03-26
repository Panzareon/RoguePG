#ifndef SCENEMANAGERVILLAGE_H
#define SCENEMANAGERVILLAGE_H

#include "SceneManagerMoveable.h"
#include "MapGeneration/MapFill.h"
#include "MapGeneration/MapGeneratorVillage.h"

#include <cereal/types/base_class.hpp>


class SceneManagerVillage : public SceneManagerMoveable
{
    public:
        SceneManagerVillage();
        SceneManagerVillage(int tileWidth, int tileHeight, unsigned int seed, MapFill* mapFill);
        virtual ~SceneManagerVillage();

        void Generate();

        virtual SceneManagerType GetType();

        template<class Archive>
        void save(Archive & archive, std::uint32_t const version) const
        {
            archive(cereal::base_class<SceneManagerMoveable>( this ), m_seed, m_mapFill);
        }


        template<class Archive>
        void load(Archive & archive, std::uint32_t const version)
        {
            archive(cereal::base_class<SceneManagerMoveable>( this ), m_seed, m_mapFill);
            Generate();
        }

    protected:
        void AddShops();
        unsigned int m_seed;

        std::unique_ptr<MapFill> m_mapFill;
        MapGeneratorVillage m_generator;

    private:
};

#endif // SCENEMANAGERVILLAGE_H
