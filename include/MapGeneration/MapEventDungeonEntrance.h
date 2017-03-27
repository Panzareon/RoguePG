#ifndef MAPEVENTDUNGEONENTRANCE_H
#define MAPEVENTDUNGEONENTRANCE_H

#include "MapEventTile.h"

class MapEventDungeonEntrance : public MapEventTile
{
    public:
        MapEventDungeonEntrance();
        MapEventDungeonEntrance(int x, int y);
        virtual ~MapEventDungeonEntrance();

        void Activate();

        template<class Archive>
        void save(Archive & archive, std::uint32_t const version) const
        {
            archive(cereal::base_class<MapEventTile>( this ));
        }


        template<class Archive>
        void load(Archive & archive, std::uint32_t const version)
        {
            archive(cereal::base_class<MapEventTile>( this ));
        }

    protected:

    private:
};

#endif // MAPEVENTDUNGEONENTRANCE_H
