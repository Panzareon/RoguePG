#include "SceneManager/AttributeNodesDisplay.h"

AttributeNodesDisplay::AttributeNodesDisplay()
{
    //ctor
    m_attributeNodePosition[BattleEnums::Attribute::MaxHp] = std::pair<int,int>(25,40);
    m_attributeNodePosition[BattleEnums::Attribute::Strength] = std::pair<int,int>(110,40);
    m_attributeNodePosition[BattleEnums::Attribute::Int] = std::pair<int,int>(190,40);
    m_attributeNodePosition[BattleEnums::Attribute::Speed] = std::pair<int,int>(263,40);
    m_attributeNodePosition[BattleEnums::Attribute::MaxMp] = std::pair<int,int>(25,75);
    m_attributeNodePosition[BattleEnums::Attribute::Defense] = std::pair<int,int>(110,75);
    m_attributeNodePosition[BattleEnums::Attribute::MagicDefense] = std::pair<int,int>(190,75);
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
    for(int j = 0; j < (int)BattleEnums::Attribute::COUNT; j++)
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
    for(int j = 0; j < (int)BattleEnums::Attribute::COUNT; j++)
    {
        if(entity != nullptr)
        {
            int attributeValue = entity->GetAttribute((BattleEnums::Attribute)j);
            m_attributeNodes[id][(BattleEnums::Attribute)j]->SetText(std::to_string(attributeValue));
        }
        else
        {
            m_attributeNodes[id][(BattleEnums::Attribute)j]->SetText("???");
        }
    }
}
