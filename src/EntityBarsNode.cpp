#include "EntityBarsNode.h"

EntityBarsNode::EntityBarsNode(int entityNr, Party* party)
{
    //ctor
    m_entityNrInList = entityNr;
    m_party = party;
    m_showForParty = true;
    m_shownEntity = nullptr;
    SetDefaultSize();
}

EntityBarsNode::EntityBarsNode(Entity* entity)
{
    //ctor
    m_showForParty = false;
    m_shownEntity = entity;
    SetDefaultSize();
}

EntityBarsNode::~EntityBarsNode()
{
    //dtor
}

void EntityBarsNode::SetDefaultSize()
{
    m_width = 100;
    m_height = 10;
    m_spacing = 7;
    UpdateShape();
}

void EntityBarsNode::UpdateShape()
{
    m_background.setSize(sf::Vector2f(m_width, m_height));
    //TODO: maybe use Texture
    m_background.setFillColor(sf::Color(128,128,128));
    m_background.setOutlineColor(sf::Color::Black);
    m_background.setOutlineThickness(1.0f);
}

void EntityBarsNode::Tick(float seconds)
{
    if(m_showForParty)
    {
        if(m_party->GetActivePartyMembers()->size() <= m_entityNrInList)
        {
            m_shownEntity = nullptr;
        }
        else if(m_party->GetActivePartyMembers()->at(m_entityNrInList) != m_shownEntity)
        {
            m_shownEntity = m_party->GetActivePartyMembers()->at(m_entityNrInList);
        }
    }
    Node::Tick(seconds);
}

void EntityBarsNode::onDraw(sf::RenderTarget& target, const sf::Transform& transformBase) const
{
    if(m_shownEntity == nullptr)
        return;
    sf::Transform transform(transformBase);
    //Draw Hp Bar Background
    target.draw(m_background, transform);
    //Draw Mp Bar Background
    transform.translate(0.0f, m_height + m_spacing);
    target.draw(m_background, transform);
    //Draw Mp Bar
    float barWidth = m_width - 2.0f;
    barWidth *= m_shownEntity->GetMpPercent();
    sf::RectangleShape bar(sf::Vector2f(barWidth, m_height - 2.0f));
    bar.setFillColor(sf::Color::Blue);
    transform.translate(1.0f, 1.0f);
    target.draw(bar, transform);
    //Draw Hp Bar
    transform = transformBase;
    barWidth = m_width - 2.0f;
    barWidth *= m_shownEntity->GetHpPercent();
    bar.setSize(sf::Vector2f(barWidth, m_height - 2.0f));
    bar.setFillColor(sf::Color::Red);
    transform.translate(1.0f, 1.0f);
    target.draw(bar, transform);
}

