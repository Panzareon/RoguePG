#ifndef MAPFILLDUNGEON2_H
#define MAPFILLDUNGEON2_H

#include "MapFillDungeon.h"

#include <cereal/types/base_class.hpp>

class MapFillDungeon2 : public MapFillDungeon
{
    public:
        MapFillDungeon2();
        virtual ~MapFillDungeon2();

        virtual void FillLayer(ToFillLayer type, int LayerId, int LayerAboveHeroId = -1, int LayerWallDecoration = -1);
        virtual void InitItemChances();

        template<class Archive>
        void serialize(Archive & archive, std::uint32_t const version)
        {
            archive(cereal::base_class<MapFillDungeon>( this ));
        }
    protected:
        virtual void FillBaseLayer(int LayerId);

    private:
};

#endif // MAPFILLDUNGEON2_H
