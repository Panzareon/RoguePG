#ifndef MAPEVENTSTAIRS_H
#define MAPEVENTSTAIRS_H

#include "MapEventTile.h"


class MapEventStairs : public MapEventTile
{
    public:
        MapEventStairs();
        MapEventStairs(bool next, int x, int y);
        virtual ~MapEventStairs();
        virtual void Activate();

        template<class Archive>
        void save(Archive & archive, std::uint32_t const version) const
        {
            archive(cereal::base_class<MapEventTile>( this ), m_next);
        }


        template<class Archive>
        void load(Archive & archive, std::uint32_t const version)
        {
            archive(cereal::base_class<MapEventTile>( this ), m_next);
        }

    protected:

    private:
        bool m_next;
};

#endif // MAPEVENTSTAIRS_H
