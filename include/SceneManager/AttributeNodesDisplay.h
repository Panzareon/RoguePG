#ifndef ATTRIBUTENODESDISPLAY_H
#define ATTRIBUTENODESDISPLAY_H

#include <map>
#include <vector>
#include "SceneGraph/TextNode.h"
#include "Controller/Enums.h"
#include "Battle/Entity.h"

class AttributeNodesDisplay
{
    public:
        AttributeNodesDisplay();
        virtual ~AttributeNodesDisplay();

        Node* GetAttributeNode(Entity* entity, int id);
        void UpdateAttributeNode(Entity* entity, int id);
    protected:
        std::vector<std::map<BattleEnums::Attribute, TextNode*>> m_attributeNodes;
        std::map<BattleEnums::Attribute, std::pair<int,int>> m_attributeNodePosition;

    private:
};

#endif // ATTRIBUTENODESDISPLAY_H
