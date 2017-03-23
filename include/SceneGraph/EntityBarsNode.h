#ifndef ENTITYBARSNODE_H
#define ENTITYBARSNODE_H

#include "Node.h"
#include "Party/Party.h"

//A node to show Health and Mana Bar of an entity
class EntityBarsNode : public Node
{
    public:
        EntityBarsNode(int entityNr, Party* party);
        EntityBarsNode(Entity* entity);
        virtual ~EntityBarsNode();
        void SetDefaultSize();
        void UpdateShape();
        void ShowMpBar(bool show);
        void ShowNumbers(bool show);
        void SetSize(int width, int height);

        void SetEntity(Entity* entity);

        virtual void Tick(float seconds);

    protected:
        virtual void onDraw(sf::RenderTarget& target, const sf::Transform& transform) const;
        void DrawBar(sf::RenderTarget& target, const sf::Transform& transform, float barWidth, sf::Color barColor, std::string text) const;
        Entity* m_shownEntity;
        bool m_showForParty;
        Party* m_party;

        bool m_showHp;
        bool m_showMp;
        bool m_showNumbers;

        int m_entityNrInList;

        int m_width;
        int m_height;
        int m_spacing;
        sf::RectangleShape m_background;

    private:
};

#endif // ENTITYBARSNODE_H
