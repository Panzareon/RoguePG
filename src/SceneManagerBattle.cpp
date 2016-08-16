#include "SceneManagerBattle.h"
#include "GameController.h"
#include "SFML/Graphics.hpp"
#include "TextureList.h"

SceneManagerBattle::SceneManagerBattle(sf::RenderTarget * target, int windowWidth, int windowHeight): SceneManager(target, windowWidth, windowHeight)
{
    //ctor
    //Build Scene Graph
    m_mainNode = new Node();
    sf::Sprite* backgroundSprite = new sf::Sprite(*TextureList::getTexture(TextureList::m_dungeonBattleBackground));
    m_background = new DrawableNode(backgroundSprite);
    m_mainNode->addChild(m_background);
    m_eventLayer = new Node();
    m_mainNode->addChild(m_eventLayer);
    m_gui = new Node();
    m_mainNode->addChild(m_gui);

    m_party = GameController::getInstance()->getParty();
}

SceneManagerBattle::~SceneManagerBattle()
{
    //dtor
}
void SceneManagerBattle::Tick()
{
    //Todo: implement Battle Logic
}

void SceneManagerBattle::CalculateNext()
{
    float smallestNext;
    Entity * next = 0;
    std::vector<PartyMember*>* activeParty = m_party->GetActivePartyMembers();
    float newTime;
    for(unsigned int i = 0; i < activeParty->size(); i++)
    {
        newTime = activeParty->at(i)->GetTimeToNextAttack();
        if(next == 0 || smallestNext > newTime)
        {
            next = activeParty->at(i);
            smallestNext = newTime;
        }
    }
    for(unsigned int i = 0; i < m_enemies.size(); i++)
    {
        newTime = m_enemies.at(i)->GetTimeToNextAttack();
        if(next == 0 || smallestNext > newTime)
        {
            next = m_enemies.at(i);
            smallestNext = newTime;
        }
    }
    m_next = next;
    PassTime(smallestNext);
}


void SceneManagerBattle::PassTime(float Time)
{
    std::vector<PartyMember*>* activeParty = m_party->GetActivePartyMembers();
    for(unsigned int i = 0; i < activeParty->size(); i++)
    {
        activeParty->at(i)->PassTime(Time);
    }
    for(unsigned int i = 0; i < m_enemies.size(); i++)
    {
        m_enemies.at(i)->PassTime(Time);
    }
}
