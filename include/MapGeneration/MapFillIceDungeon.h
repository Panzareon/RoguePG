#ifndef MAPFILLICEDUNGEON_H
#define MAPFILLICEDUNGEON_H

#include "MapFillDungeon.h"

#include <cereal/types/base_class.hpp>

class MapFillIceDungeon : public MapFillDungeon
{
    public:
        MapFillIceDungeon();
        virtual ~MapFillIceDungeon();

        virtual void FillLayer(ToFillLayer type, int LayerId, int LayerAboveHeroId = -1, int LayerWallDecoration = -1);
        virtual void InitItemChances(bool wallAbove);

        template<class Archive>
        void serialize(Archive & archive, std::uint32_t const version)
        {
            archive(cereal::base_class<MapFillDungeon>( this ));
        }
    protected:
        virtual void FillBaseLayer(int LayerId);
        virtual void InitBaseItemChances(bool wallAbove);

    private:
};

#endif // MAPFILLICEDUNGEON_H
