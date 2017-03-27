#ifndef MAPEVENTHERO_H
#define MAPEVENTHERO_H

#include "MapEventTile.h"
#include "SceneGraph/Node.h"

class MapEventHero : public MapEventTile
{
    public:
        MapEventHero();
        MapEventHero(int x, int y);
        virtual ~MapEventHero();

        void SetNode(Node* node);

        virtual void Activate();

        virtual void AfterLoad(SceneManager* sm);

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
        Node* m_node;

    private:
};

#endif // MAPEVENTHERO_H
