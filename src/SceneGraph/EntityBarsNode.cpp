#include "SceneGraph/EntityBarsNode.h"
#include "Controller/Configuration.h"

EntityBarsNode::EntityBarsNode(int entityNr, Party* party)
{
    //ctor
    m_entityNrInList = entityNr;
    m_party = party;
    m_showForParty = true;
    m_shownEntity = nullptr;
    m_showHp = true;
    m_showMp = true;
    m_showNumbers = true;
    SetDefaultSize();
}

EntityBarsNode::EntityBarsNode(Entity* entity)
{
    //ctor
    m_showForParty = false;
    m_shownEntity = entity;
    m_showHp = true;
    m_showMp = true;
    m_showNumbers = true;
    SetDefaultSize();
}

EntityBarsNode::~EntityBarsNode()
{
    //dtor
}

void EntityBarsNode::SetDefaultSize()
{
    m_width = 100;
    m_height = 15;
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

void EntityBarsNode::SetEntity(Entity* entity)
{
    m_shownEntity = entity;
}

void EntityBarsNode::Tick(float seconds)
{
    if(m_showForParty)
    {
        if(m_party->GetActivePartyMembers()->size() <= m_entityNrInList)
        {
            m_shownEntity = nullptr;
        }
        else
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
    //Draw Hp Bar
    if(m_showHp)
    {
        float barWidth = m_width - 2.0f;
        barWidth *= m_shownEntity->GetHpPercent();
        std::string str;
        if(m_showNumbers)
        {
            str = std::to_string(m_shownEntity->GetHp());
            str += " / " + std::to_string(m_shownEntity->GetAttribute(BattleEnums::AttributeMaxHp));
        }

        DrawBar(target, transform, barWidth, sf::Color::Red , str);
    }
    if(m_showMp)
    {
        if(m_showHp)
        {
            transform = transformBase;
            transform.translate(0.0f, m_height + m_spacing);
        }
        float barWidth = m_width - 2.0f;
        barWidth *= m_shownEntity->GetMpPercent();
        std::string str;
        if(m_showNumbers)
        {
            str = std::to_string(m_shownEntity->GetMp());
            str += " / " + std::to_string(m_shownEntity->GetAttribute(BattleEnums::AttributeMaxMp));
        }

        DrawBar(target, transform, barWidth, sf::Color::Blue, str);
    }
}

void EntityBarsNode::DrawBar(sf::RenderTarget& target, const sf::Transform& transformBase, float barWidth, sf::Color barColor, std::string str) const
{
    sf::Transform transform(transformBase);
    target.draw(m_background, transform);
    sf::RectangleShape bar(sf::Vector2f(barWidth, m_height - 2.0f));
    bar.setFillColor(barColor);
    transform.translate(1.0f, 1.0f);
    target.draw(bar, transform);

    if(m_showNumbers)
    {
        sf::Font* font = Configuration::GetInstance()->GetFont();
        sf::Text text(str, *font, 14);
        transform.translate((m_width - text.getLocalBounds().width) / 2, -2.0f);
        target.draw(text, transform);
    }
}
