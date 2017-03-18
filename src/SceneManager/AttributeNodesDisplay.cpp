#include "AttributeNodesDisplay.h"

AttributeNodesDisplay::AttributeNodesDisplay()
{
    //ctor
    m_attributeNodePosition[BattleEnums::AttributeMaxHp] = std::pair<int,int>(25,40);
    m_attributeNodePosition[BattleEnums::AttributeStrength] = std::pair<int,int>(110,40);
    m_attributeNodePosition[BattleEnums::AttributeInt] = std::pair<int,int>(190,40);
    m_attributeNodePosition[BattleEnums::AttributeSpeed] = std::pair<int,int>(263,40);
    m_attributeNodePosition[BattleEnums::AttributeMaxMp] = std::pair<int,int>(25,75);
    m_attributeNodePosition[BattleEnums::AttributeDefense] = std::pair<int,int>(110,75);
    m_attributeNodePosition[BattleEnums::AttributeMagicDefense] = std::pair<int,int>(190,75);
}

AttributeNodesDisplay::~AttributeNodesDisplay()
{
    //dtor
}

Node* AttributeNodesDisplay::GetAttributeNode(Entity* entity, int id)
{
    if(m_attributeNodes.size() <= id)
    {
        m_attributeNodes.resize(id + 1);
    }
    Node* nextMember = new Node();
    for(int j = 0; j < BattleEnums::ATTRIBUTE_END; j++)
    {
        TextNode* node = new TextNode(std::to_string(entity->GetAttribute((BattleEnums::Attribute)j)));
        node->SetColor(sf::Color::Black);
        node->SetFontSize(25);
        m_attributeNodes[id][(BattleEnums::Attribute)j] = node;
        nextMember->addChild(node);
        std::pair<int,int> pos = m_attributeNodePosition[(BattleEnums::Attribute)j];
        node->moveNode(pos.first,pos.second);
    }
    return nextMember;
}

void AttributeNodesDisplay::UpdateAttributeNode(Entity* entity, int id)
{
    for(int j = 0; j < BattleEnums::ATTRIBUTE_END; j++)
    {
        int attributeValue = entity->GetAttribute((BattleEnums::Attribute)j);
        m_attributeNodes[id][(BattleEnums::Attribute)j]->SetText(std::to_string(attributeValue));
    }
}
