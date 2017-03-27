#ifndef MAPEVENTCHEST_H
#define MAPEVENTCHEST_H

#include "MapEventTile.h"


class MapEventChest : public MapEventTile
{
    public:
        MapEventChest();
        MapEventChest(int x, int y);
        virtual ~MapEventChest();
        virtual void Activate();

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

#endif // MAPEVENTCHEST_H
