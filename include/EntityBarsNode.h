#ifndef ENTITYBARSNODE_H
#define ENTITYBARSNODE_H

#include "Node.h"
#include "Party.h"

//A node to show Health and Mana Bar of an entity
class EntityBarsNode : public Node
{
    public:
        EntityBarsNode(int entityNr, Party* party);
        EntityBarsNode(Entity* entity);
        virtual ~EntityBarsNode();
        void SetDefaultSize();
        void UpdateShape();

        virtual void Tick(float seconds);

    protected:
        virtual void onDraw(sf::RenderTarget& target, const sf::Transform& transform) const;
        Entity* m_shownEntity;
        bool m_showForParty;
        Party* m_party;

        int m_entityNrInList;

        int m_width;
        int m_height;
        int m_spacing;
        sf::RectangleShape m_background;

    private:
};

#endif // ENTITYBARSNODE_H
