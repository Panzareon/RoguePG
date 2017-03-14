#ifndef MAPEVENTHERO_H
#define MAPEVENTHERO_H

#include "MapEventTile.h"
#include "Node.h"

class MapEventHero : public MapEventTile
{
    public:
        MapEventHero(Node* node, int x, int y);
        virtual ~MapEventHero();

        virtual void Activate();

    protected:
        Node* m_node;

    private:
};

#endif // MAPEVENTHERO_H
